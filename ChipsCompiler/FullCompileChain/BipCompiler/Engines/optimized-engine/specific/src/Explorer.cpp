/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
 *  Marc Pouhliès
 *  Jacques Combaz (jacques.combaz@univ-grenoble-alpes.fr)
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

#include <Explorer.hpp>
#include <InteractionValue.hpp>
#include <Atom.hpp>
#include <AtomInternalPort.hpp>
#include <AtomExportPort.hpp>
#include <BipError.hpp>
#include <NonDeterministicPetriNetError.hpp>
#include <NonOneSafePetriNetError.hpp>
#include <CycleInPrioritiesError.hpp>
#include <CycleInAtomPrioritiesError.hpp>
#include <State.hpp>

#include <stdlib.h>
#include <engine-version.hpp>

#include <string>
#include <iostream>
#include <sstream>
#include <set>
#include <unordered_set>
#include <stack>
#include <utility>

bool isSerializeEnabled();
void serialize(char **, size_t *);
void deserialize(const char *, size_t);

Explorer::Explorer(Engine &engine, bool verbose) :
  Scheduler(engine),
  mVerbose(verbose),
  nbErrors(0) {
}

Explorer::~Explorer() {
}

/**
 * \brief Initialize the system.
 */
BipError &Explorer::initialize() {
  if (verbose()) {
    cout << "[BIP ENGINE]: BIP Engine (version " ENGINE_VERSION  " )" << endl;
    cout << "[BIP ENGINE]:" << endl;
    cout << "[BIP ENGINE]: initialize components..." << endl;
  }

  BipError &error = engine().initialize();

  if (error.type() != NO_ERROR) {
    ++nbErrors;
  }

  return BipError::NoError;
}

/**
 * \brief Compute all execution sequences and corresponding reachable states
 * of the model.
 */
BipError &Explorer::run() {
  if (verbose()) {
    cout << "[BIP ENGINE]: computing reachable states:";
  }

  if (isSerializeEnabled()) {
    if (nbErrors == 0) {
      nbErrors = dfsExplore();
    }

    if (verbose()) {
      cout << " found " << states().size() << " reachable state";
      if (states().size() > 1) cout << "s";

      cout << ", " << deadlocks().size() << " deadlock";
      if (deadlocks().size() > 1) cout << "s";

      cout << ", and " << nbErrors << " error";
      if (nbErrors > 1) cout << "s";

      cout << " in " << errors().size() << " state";
      if (errors().size() > 1) cout << "s";

      cout << endl;
    }
  }
  else {
    cout << endl;
    cout << "[BIP ENGINE]: ERROR: missing serialization functions!" << endl;
    cout << "[BIP ENGINE]: Try to recompile with option '--gencpp-enable-marshalling'" << endl;
  }

  return BipError::NoError;
}


/**
 * \brief DFS exploration of execution sequences.
 *
 * \param states is used for storing all the reachable states.
 * \param deadlocks is used for storing all the reachable states from
 * which no interaction / internal port is enabled.
 * \param errors is used for storing all the reachable states form
 * which the execution of an interaction / internal port leads to an
 * error.
 *
 * \return the total number of errors found from the error states.
 */
unsigned int Explorer::dfsExplore() {
  stack<const State *> path;
  stack<unsigned int> branch;
  stack<unsigned int> width;

  int nbErrors = 0;

  while (true) {
    if (verbose()) {
      cout << "."; cout.flush();
    }

    State state = engine().getState();

    unsigned int chosenBranch = 0;
    bool stopPath = true;

    // check for visisted states
    pair<unordered_set<State, State::Hash>::iterator,bool> ret = states().insert(state);

    if (ret.second) {
      const State *statePtr = &(*ret.first);

      unsigned int nbInteractions = engine().interactions().size();
      unsigned int nbInternals = engine().internals().size();

      // check for deadlocks
      if (nbInteractions == 0 && nbInternals == 0) {
        deadlocks().push_back(state);
      }
      else {
        stopPath = false;

        // if multiple path, put the next branch in the todo list
        if (nbInteractions + nbInternals > 1) {
          path.push(statePtr);
          branch.push(1);
          width.push(nbInteractions + nbInternals);
        }
      }
    }

    // go back to the next path to search
    if (stopPath) {
      if (!path.empty()) {
        engine().setState(*(path.top()));
        chosenBranch = branch.top();

        // keep in mind to explore next branch
        ++(branch.top());

        // chosenBranch is the last branch
        if (branch.top() >= width.top()) {
          path.pop();
          branch.pop();
          width.pop();
        }
      }
      else {
        break;
      }
    }

    BipError *error = NULL;

    // execute interaction / internal port corresponding to the chosen branch
    if (chosenBranch < engine().interactions().size()) {
      InteractionValue &chosenInteraction = *engine().interactions()[chosenBranch];
      error = &(engine().execute(chosenInteraction));
    }
    else {
      AtomInternalPort &chosenInternal = *engine().internals()[chosenBranch - engine().interactions().size()];
      error = &(engine().execute(chosenInternal));
    }

    // handle error
    if (error->type() != NO_ERROR) {
      errors().push_back(state);
      ++nbErrors;
    }
  }

  return nbErrors;
}

/**
 * \brief Handle error returned by the engine.
 * 
 * initialize() and execute() methods of the engine may return an error,
 * i.e. an instance of BipError. Such instances should be catched by
 * the scheduler in order to stop the current execution and provide
 * a useful report to the user (e.g. error message, etc.).
 *
 * \param error: the target instance of BipError.
 */
void Explorer::handleError(BipError &error) {
  if (error.type() != NO_ERROR) {

    cout << "[BIP ENGINE]: ERROR: ";

    if (error.type() == NON_DETERMINISTIC_PETRI_NET) {
      const NonDeterministicPetriNetError &errorNonDetPetriNet = dynamic_cast<const NonDeterministicPetriNetError &>(error);

      if (errorNonDetPetriNet.hasPort()) {
        cout << "non-deterministic choice between transitions labelled by" << errorNonDetPetriNet.port().name();
      }
      else {
        cout << "non-deterministic choice between internal transitions";
      }

      cout << " in " << errorNonDetPetriNet.atom().name() << "!";
    }
    else if (error.type() == CYCLE_IN_PRIORITIES) {
      cout << "cycle in priorities! (";

      const CycleInPrioritiesError &errorPriorities = dynamic_cast<const CycleInPrioritiesError &>(error);

      for (vector<const Interaction *>::const_iterator interactionIt = errorPriorities.cycle().begin() ;
           interactionIt != errorPriorities.cycle().end() ;
           ++interactionIt) {
        const Interaction &interaction = **interactionIt;

        if (interactionIt != errorPriorities.cycle().begin()) {
          cout << " < ";
        }

        cout << interaction;
      }

      cout << ")";
    }
    else if (error.type() == CYCLE_IN_ATOM_PRIORITIES) {
      cout << "cycle in priorities! (";

      const CycleInAtomPrioritiesError &errorPriorities = dynamic_cast<const CycleInAtomPrioritiesError &>(error);

      for (vector<const AtomInternalPort *>::const_iterator portIt = errorPriorities.cycle().begin() ;
           portIt != errorPriorities.cycle().end() ;
           ++portIt) {
        const AtomInternalPort &port = **portIt;

        if (portIt != errorPriorities.cycle().begin()) {
          cout << " < ";
        }

        cout << port.name();
      }

      cout << ")";
    }
    else if (error.type() == NON_ONE_SAFE_PETRI_NET) {
      const NonOneSafePetriNetError &errorNonOneSafe = dynamic_cast<const NonOneSafePetriNetError &>(error);

      cout << "the Peri net of " << errorNonOneSafe.atom().name() << " is not 1-safe! (";
      if (errorNonOneSafe.hasPort()) {        
        cout << "when executing a transition labelled by " << errorNonOneSafe.port().name();
      }
      else {
        cout << "when executing an internal transition";
      }
      cout << ")";
    }
    else {
      // unsupported type of error
      assert(false);
    }

    cout << endl;

    ErrorType returnedErrorType = error.type();

    delete &error;

    exit(returnedErrorType);
  }
}
