/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
 *  Jacques Combaz (jacques.combaz@univ-grenoble-alpes.fr)
 *  Marc Pouhliès
 * 
 * This software is a computer program whose purpose is to generate
 * executable code from BIP models.
 * 
 * This software is governed by the CeCILL-B license under French law and
 * abiding by the rules of distribution of free software.  You can  use, 
 * modify and/ or redistribute the software under the terms of the CeCILL-B
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info".
 * 
 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited
 * liability.
 *
 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 * therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or 
 * data to be ensured and,  more generally, to use and operate it in the 
 * same conditions as regards security.
 * 
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL-B license and that you accept its terms.
 */

#include "RandomScheduler.hpp"
#include <Compound.hpp>
#include <Component.hpp>
#include <InteractionValue.hpp>
#include <Atom.hpp>
#include <AtomInternalPort.hpp>
#include <AtomExportPort.hpp>
#include <BipError.hpp>
#include <NonDeterministicPetriNetError.hpp>
#include <NonOneSafePetriNetError.hpp>
#include <CycleInPrioritiesError.hpp>
#include <CycleInAtomPrioritiesError.hpp>
#include <AtomInvariantViolationError.hpp>
#include <UnexpectedEventError.hpp>

#include <Engine.hpp>
#include <Logger.hpp>
#include <StringTree.hpp>
#include <State.hpp>

#include <stdlib.h>
#include "engine-version.hpp"

#include <string>
#include <iostream>
#include <sstream>

#include <time.h>
#include <signal.h>
#include <unistd.h>

bool isSerializeEnabled();

RandomScheduler::RandomScheduler(Engine &engine, Logger &logger, bool debug, bool interactive, bool randomSeed, unsigned int seed) :
  Scheduler(engine),
  mLogger(logger),
  mDebug(debug),
  mInteractive(interactive),
  mRandomSeed(randomSeed),
  mSeed(seed) {
  // initialize signals management
  RandomScheduler::pid = getpid();
  signal(Engine::SIGBIP, handleSignals);
}

RandomScheduler::~RandomScheduler() {
}

/**
 * \brief Initialize the system.
 */
BipError &RandomScheduler::initialize() {
  // log banner
  logger().log("BIP Engine (version " ENGINE_VERSION " )");
  logger().log("");
  logger().log("initialize components...");

  // initialize the seed for random
  ostringstream displayRandomSeed;
  displayRandomSeed << "random scheduling based on seed=";

  if (randomSeed()) {
    int random_seed = time(NULL);
    srand (random_seed);

    displayRandomSeed << random_seed;
  }
  else {
    srand(seed());

    displayRandomSeed << seed();
  }

  // log seed
  logger().log(displayRandomSeed.str());

  BipError &error = engine().initialize();
  
  logger().log(error);

  return error;
}

/**
 * \brief Execute a single execution sequence randomly.
 *
 * Interactions and internal ports are chosen randomly according to
 * a uniform repartition of the probability. It is based on rand() of
 * the standard library for computing random values. Notice that the
 * seed for rand() is currently not fixed.
 */
BipError &RandomScheduler::run() {
  map<unsigned int, State> savedStates;
  
  if (debug()) {
    print();
  }
  
  bool noDisplay = false;
    
  while ((interactive() || !deadlock()) && !logger().reachedLimit()) {
    // take a snapshot of the treated notifications
    updateTreatedNotifications();

    // /!\ order is critical: must be placed after updateTreatedNotifications()!
    // update current status of external ports w.r.t. incoming events
    BipError &error = engine().checkExternals();
    logger().log(error);

    if (error.type() != NO_ERROR) {
      return error;
    }

    // execute an enabled external port in priority
    if (!engine().externals().empty()) {
      // log enabled interaction / internal ports / external ports
      vector<InteractionValue *> emptyInteractions;
      vector<AtomInternalPort *> emptyInternals;

      // log enabled external ports
      logger().log(emptyInteractions, emptyInternals, engine().externals());

      // choose an external port randomly
      unsigned int randomIndex = (unsigned int) engine().externals().size() * (rand() / (RAND_MAX + 1.0));
      AtomExternalPort &chosenPort = *engine().externals()[randomIndex];

      // execute the chosen port
      logger().log(chosenPort, emptyInteractions, emptyInternals, engine().externals());
      BipError &error = engine().execute(chosenPort);
      logger().log(error);

      if (error.type() != NO_ERROR) {
        return error;
      }

      continue;
    }
    else {
      if (newNotifications()) {
        // if notifications have to be treated, continue
        continue;
      }
      else if (engine().interactions().empty() && engine().internals().empty() && !interactive()) {
        // wait for incoming events
        waitForNotifications();

        continue;
      }
    }
    
    // interactions and internal ports enabled at the current state
    const vector<InteractionValue *> &interactions = engine().interactions();
    const vector<AtomInternalPort *> &internals = engine().internals();
    const vector<AtomExternalPort *> &externals = engine().externals();

    // log enabled interaction / internal ports
    if (!noDisplay) {
      logger().log(interactions, internals, externals);
    }

    unsigned int nbInteractionsInternals = interactions.size() + internals.size();

    unsigned int randomIndex = (unsigned int) nbInteractionsInternals * (rand() / (RAND_MAX + 1.0));
    unsigned int chosenIndex = randomIndex;

    bool quit = false;
    bool cont = false;

    if (interactive()) {
      noDisplay = false;
      
      cout << "[BIP ENGINE]: -> enter ";

      if (nbInteractionsInternals > 0) {
        cout << "interaction / internal port number (0.." << nbInteractionsInternals - 1 << "), 'r' for a random choice, ";
      }
      
      cout << "'q' for quit, 's' for save state, 'l' <index> for load state, 'd' <index> for delete state: ";
      cout.flush();

      // retrieve user input
      string str;
      getline(cin, str);

      // check for ctrl-D
      if (cin.eof()) {
        quit = true;
        cout << endl;
        break;
      }
      
      // retrieve the first word
      size_t index = 0;
      string cmd = parse(str, index);

      if (cmd.length() == 0) {
        cout << "[BIP ENGINE]: empty choice!" << endl;
        cont = true;
        noDisplay = true;
      }
      else {
        if (cmd == "r" && nbInteractionsInternals > 0) {
          if (parse(str, index) == "") {
            chosenIndex = randomIndex;
          }
          else {
            cout << "[BIP ENGINE]: invalid parameter: no parameter expected!" << endl;
            
            noDisplay = true;
            cont = true;
          }
        }
        else if (cmd == "q") {
          if (parse(str, index) == "") {
            quit = true;
          }
          else {
            cout << "[BIP ENGINE]: invalid parameter: no parameter expected!" << endl;

            noDisplay = true;
            cont = true;
          }
        }
        else if (cmd == "s") {
          if (checkIsSerializeEnabled()) {            
            if (parse(str, index) == "") {
              if (savedStates.find(logger().state()) != savedStates.end()) {
                cout << "[BIP ENGINE]: state #" << logger().state() << " already saved!" << endl;
              }
              else {
                cout << "[BIP ENGINE]: save state #" << logger().state() << endl;
                    
                // savedStates[logger().state()] = engine().getState();
                savedStates.insert(pair<unsigned int, State>(logger().state(), engine().getState()));
              }
            }
            else {
              cout << "[BIP ENGINE]: invalid parameter: no parameter expected!" << endl;
            }
          }

          noDisplay = true;
          cont = true;
        }
        else if (cmd == "l") {
          if (checkIsSerializeEnabled()) {
            // retrieve parameter
            string parameter = parse(str, index);

            if (parameter == "" || parse(str, index) != "") {
              cout << "[BIP ENGINE]: invalid parameter: expect one parameter!" << endl;
              noDisplay = true;
            }
            else {
              // convert it to integer
              unsigned int stateIndex;
              istringstream iss(parameter);
              iss >> stateIndex;
              
              if (iss.fail()) {
                cout << "[BIP ENGINE]: invalid load parameter: expect an integer!" << endl;
                noDisplay = true;
              }
              else {
                map<unsigned int, State>::const_iterator it =
                  savedStates.find(stateIndex);
                
                if (it != savedStates.end()) {
                  cout << "[BIP ENGINE]: load state #" << stateIndex << " into the current state " << endl;

                  engine().setState(it->second);
                }
                else {
                  cout << "[BIP ENGINE]: state #" << stateIndex << " not saved!" << endl;
                  noDisplay = true;
                }
              }
            }
          }  

          cont = true;
        }
        else if (cmd == "d") {
          if (checkIsSerializeEnabled()) {
            // retrieve parameter
            string parameter = parse(str, index);

            if (parameter == "" || parse(str, index) != "") {
              cout << "[BIP ENGINE]: invalid parameter: expect one parameter!" << endl;
            }
            else {
              // convert it to integer
              unsigned int stateIndex;
              istringstream iss(parameter);
              iss >> stateIndex;
              
              if (iss.fail()) {
                cout << "[BIP ENGINE]: invalid delete parameter: expect an integer!" << endl;
              }
              else {
                map<unsigned int, State>::iterator it =
                  savedStates.find(stateIndex);
              
                if (it != savedStates.end()) {
                  cout << "[BIP ENGINE]: delete state #" << stateIndex << endl;

                  savedStates.erase(it);
                }
                else {
                  cout << "[BIP ENGINE]: state #" << stateIndex << " not found!" << endl;
                }
              }
            }
          }

          noDisplay = true;
          cont = true;
        }
        else {
          // try to convert command to integer
          istringstream iss(cmd);
          iss >> chosenIndex;

          if (nbInteractionsInternals == 0 ||
              iss.fail() ||
              chosenIndex >= nbInteractionsInternals) {
            cout << "[BIP ENGINE]: invalid choice!" << endl;
            noDisplay = true;
            cont = true;
          }
          else if (parse(str, index) != "") {
            cout << "[BIP ENGINE]: invalid parameter: no parameter expected!" << endl;
            noDisplay = true;
            cont = true;  
          }
        }
      }
    }

    if (quit) {
      break;
    }

    if (cont) {
      continue;
    }

    if (chosenIndex < interactions.size()) {
      // execute an interaction
      InteractionValue &chosenInteraction = *interactions[chosenIndex];

      logger().log(chosenInteraction, interactions, internals, externals);
      BipError &error = engine().execute(chosenInteraction);
      logger().log(error);

      if (error.type() != NO_ERROR) {
        return error;
      }
    }
    else {
      // execute an internal port
      AtomInternalPort &chosenInternal = *internals[chosenIndex - interactions.size()];

      logger().log(chosenInternal, interactions, internals, externals);
      BipError &error = engine().execute(chosenInternal);
      logger().log(error);

      if (error.type() != NO_ERROR) {
        return error;
      }
    }

    if (debug()) {
      print();
    }
  }

  // log deadlock or reached limit
  if (!interactive()) {
    logger().log(engine().interactions(), engine().internals(), engine().externals());
  }

  return BipError::NoError;
}

bool RandomScheduler::deadlock() const {
  return engine().interactions().empty() && // interaction to execute
         engine().internals().empty()    && // internal port to execute
         engine().externals().empty()    && // external port to execute
         engine().waiting().empty();        // external port waiting
}

void RandomScheduler::waitForNotifications() {
  // then wait for notifications
  sigset_t maskOld, maskSIGBIP;

  sigemptyset(&maskSIGBIP);
  sigaddset(&maskSIGBIP, Engine::SIGBIP);

  sigprocmask(SIG_BLOCK, &maskSIGBIP, &maskOld);

  if (!newNotifications()) {
    sigsuspend(&maskOld);
  }

  sigprocmask(SIG_UNBLOCK, &maskSIGBIP, NULL);
}

void RandomScheduler::notify() {
  kill(RandomScheduler::pid, Engine::SIGBIP);
}

pid_t RandomScheduler::pid(0);

volatile unsigned int RandomScheduler::nbNotifications(0);

void RandomScheduler::handleSignals(int signum) {
  nbNotifications++;
}

/**
 * \brief Displays the current state of the system.
 *
 * Useful for debug purpose. Side effect on cout.
 */
void RandomScheduler::print() {
  const Engine &constEngine = engine();
  const Compound &top = constEngine.top();

  StringTree debugStrTree = print(top);
  string header = "[BIP ENGINE]: ";
  string debugStr = debugStrTree.toString(header);
  cout << debugStr;
}

StringTree RandomScheduler::print(const ConnectorExportPort &port) {
  StringTree ret(port.name());

  for (unsigned int i = 0 ; i < port.portValues().size() ; ++i) {
    string portStr = port.portValues()[i]->toString();

    if (portStr.size() == 0) {
      string noValueStr = "<no_value>";
      ret.addChild(noValueStr);
    }
    else {
      ret.addChild(portStr);
    }
  }

  return ret;
}

StringTree RandomScheduler::print(const CompoundExportPort &port) {
  StringTree ret(port.name());

  for (unsigned int i = 0 ; i < port.portValues().size() ; ++i) {
    string portStr = port.portValues()[i]->toString();

    if (portStr.size() == 0) {
      string noValueStr = "<no_value>";
      ret.addChild(noValueStr);
    }
    else {
      ret.addChild(portStr);
    }
  }

  return ret;
}

StringTree RandomScheduler::print(const AtomInternalPort &port) {
  string ret = port.name();

  if (port.hasPortValue()) {
    string portStr = port.portValue().toString();

    if (portStr.size() > 0) {
      ret = ret + " (" + portStr + ")";
    }
    else {
      ret = ret + " (<no_value>)";
    }
  }

  return StringTree(ret);
}

StringTree RandomScheduler::print(const AtomExportPort &port) {
  StringTree ret(port.name());

  for (unsigned int i = 0 ; i < port.internalPorts().size() ; ++i) {
    const AtomInternalPort &internalPort = *(port.internalPorts()[i]);
    ret.addChild(print(internalPort));
  }

  return ret;
}

StringTree RandomScheduler::print(const InteractionValue &interaction) {
  ostringstream oss;

  oss << interaction;

  if (!interaction.isDominated()) oss << "*";

  return StringTree(oss.str());
}

StringTree RandomScheduler::print(const Connector &connector) {
  StringTree ret(connector.name());

  if (connector.hasExportedPort()) {
    StringTree portTree = print(connector.exportedPort());
    ret.addChild(portTree);
  }

  const vector<InteractionValue *> &interactions = connector.enabledInteractions();

  for (unsigned int i = 0 ; i < interactions.size() ; ++i) {
    StringTree interactionTree = print(*interactions[i]);
    ret.addChild(interactionTree);
  }
  //connector.release(interactions);

  return ret;
}

StringTree RandomScheduler::print(const Atom &atom) {
  StringTree ret(atom.name());

  for (map<string, AtomExportPort *>::const_iterator portIt = atom.ports().begin() ;
       portIt != atom.ports().end() ;
       ++portIt) {
    const AtomExportPort &port = *(portIt->second);
    StringTree portTree = print(port);
    ret.addChild(portTree);
  }

  string atomStr = atom.toString();
  string::const_iterator beginIt = atomStr.begin();
  string::const_iterator strIt = atomStr.begin() ;

  while (strIt != atomStr.end()) {
    if (*strIt == '\n') {
      string childStr = string(beginIt, strIt);
      ret.addChild(childStr);
      beginIt = strIt + 1;
    }

    ++strIt;
  }

  if (beginIt != atomStr.end()) {
    string childStr = string(beginIt, strIt);
    ret.addChild(childStr);
  }

  return ret;
}

StringTree RandomScheduler::print(const Compound &compound) {
  StringTree ret(compound.name());

  for (map<string, CompoundExportPort *>::const_iterator portIt = compound.ports().begin() ;
       portIt != compound.ports().end() ;
       ++portIt) {
    const CompoundExportPort &port = *(portIt->second);
    StringTree portTree = print(port);
    ret.addChild(portTree);
  }

  for (map<string, Connector *>::const_iterator connIt = compound.connectors().begin() ;
       connIt != compound.connectors().end() ;
       ++connIt) {
    const Connector &connector = *(connIt->second);
    StringTree connectorTree = print(connector);
    ret.addChild(connectorTree);
  }

  for (map<string, Component *>::const_iterator connIt = compound.components().begin() ;
       connIt != compound.components().end() ;
       ++connIt) {
    const Component &component = *(connIt->second);
    StringTree componentTree = print(component);
    ret.addChild(componentTree);
  }

  return ret;
}

StringTree RandomScheduler::print(const Component &component) {
  if (component.type() == COMPOUND) {
    const Compound &compound = (const Compound &) component;
    return print(compound);
  }
  else if (component.type() == ATOM) {
    const Atom &atom = (const Atom &) component;
    return print(atom);
  }
  else {
    assert(false);
  }

  return StringTree();
}

bool RandomScheduler::checkIsSerializeEnabled() {
  bool ret = true;
  
  if (!isSerializeEnabled()) {
    cout << "[BIP ENGINE]: ERROR: missing serialization functions!" << endl;
    cout << "[BIP ENGINE]: Try to recompile with option '--gencpp-enable-marshalling'";
    
    ret = false;
  }

  return ret;
}

string RandomScheduler::parse(const string &cmdline, size_t &index) {
  string ret = "";

  enum {
    STARTING_WHITE_SPACE,
    WORD,
    END
  } state;

  size_t start = 0, len = 0;

  state = STARTING_WHITE_SPACE;
  
  while (index < cmdline.length()) {
    switch (state) {
    case STARTING_WHITE_SPACE:
      if (cmdline[index] != ' ') {
        state = WORD;
        start = index;
        ++len;
      }
      break;

    case WORD:
      if (cmdline[index] == ' ') {
        state = END;
      }
      else {
        ++len;
      }
      break;

    case END:
      break;

    default:
      assert(false);
      break;      
    }

    if (state == END) {
      break;
    }
    
    ++index;
  }

  if (state == WORD || state == END) {
    ret = cmdline.substr(start, len);
  }

  return ret;
}
