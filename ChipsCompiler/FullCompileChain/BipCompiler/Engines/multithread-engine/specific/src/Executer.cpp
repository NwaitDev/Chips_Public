/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
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

#include "Executer.hpp"
#include <Compound.hpp>
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
#include <StringTree.hpp>
#include <Logger.hpp>
#include <Thread.hpp>
#include <Job.hpp>
#include <ExecuteAtomJob.hpp>

#include <stdlib.h>
#include "engine-version.hpp"

#include <string>
#include <iostream>
#include <sstream>

Executer::Executer(Compound &top, Logger &logger, unsigned int nbThreads, bool randomSeed, unsigned int seed) :
  mTop(top),
  mLogger(logger),
  mNbThreads(nbThreads),
  mRandomSeed(randomSeed),
  mSeed(seed) {
}

Executer::~Executer() {
}



/**
 * \brief Initialize the system.
 */
BipError &Executer::initialize() {
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
  
  logger().log(displayRandomSeed.str());

  // initialize threads for handling jobs
  initializeThreads();

  // intialize precomputed values
  top().initialize();
  top().initializeMutexs();
  top().configureJobs(mLogger);

  // initialize reserver
  initializeReserver(top());
  mReserver.initialize();

  // reserve all resources
#ifdef NDEBUG
  mReserver.tryToReserve();
#else
  bool success = mReserver.tryToReserve();
#endif

  assert(success);
  
  // restart all atoms
  top().restartAllAtoms();

  return BipError::NoError;
}

/**
 * \brief Execute a single execution sequence randomly.
 *
 * Interactions and internal ports are chosen randomly according to
 * a uniform repartition of the probability. It is based on rand() of
 * the standard library for computing random values. Notice that the
 * seed for rand() is currently not fixed.
 */
BipError &Executer::run() {
  // initialize threads for handling jobs
  startThreads();

  // wait for deadlock
  BipError &error = Executer::jobs.waitForNoActivity();

  // force threads to complete
  jobs.stop(BipError::NoError);

  // stop threads
  stopThreads();

  // log deadlock if the stop was not caused by an error  
  if (error.type() == NO_ERROR) {
    logger().logDeadlock();
  }

  return error;
}

void Executer::initializeReserver(const Compound &compound) {
  for (map<string, Component *>::const_iterator componentIt = compound.components().begin() ;
       componentIt != compound.components().end() ;
       ++componentIt) {
    Component &component = *componentIt->second;

    if (component.type() == COMPOUND) {
      Compound &compound = dynamic_cast<Compound &>(component);

      initializeReserver(compound);
    }
    else if (component.type() == ATOM) {
      Atom &atom = dynamic_cast<Atom &>(component);

      for (vector<Resource *>::const_iterator resourceIt = atom.executeJob().writer().resources().begin() ;
           resourceIt != atom.executeJob().writer().resources().end() ;
           ++resourceIt) {
        Resource &resource = **resourceIt;

        mReserver.addResource(resource);
      }
    }
  }
}

void Executer::initializeThreads() {
  for (unsigned int i = 0 ; i < mNbThreads ; ++i) {
    Thread *thrd = new Thread(Executer::jobs);
    mThreads.push_back(thrd);
  }
}

void Executer::startThreads() {
  for (vector<Thread *>::const_iterator thrdIt = mThreads.begin() ;
       thrdIt != mThreads.end() ;
       ++thrdIt) {
    Thread &thrd = **thrdIt;
    thrd.start();
  }
}

void Executer::stopThreads() {
  for (vector<Thread *>::const_iterator thrdIt = mThreads.begin() ;
       thrdIt != mThreads.end() ;
       ++thrdIt) {
    Thread *thrd = *thrdIt;

    thrd->join();

    delete thrd;
  }
}

/**
 * \brief Displays the current state of the system.
 *
 * Useful for debug purpose. Side effect on cout.
 */
void Executer::print() {
  StringTree debugStrTree = print(top());
  string header = "[BIP ENGINE]: ";
  string debugStr = debugStrTree.toString(header);
  cout << debugStr;
}

StringTree Executer::print(const ConnectorExportPort &port) {
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

StringTree Executer::print(const CompoundExportPort &port) {
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

StringTree Executer::print(const AtomInternalPort &port) {
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

StringTree Executer::print(const AtomExportPort &port) {
  StringTree ret(port.name());

  for (unsigned int i = 0 ; i < port.internalPorts().size() ; ++i) {
    const AtomInternalPort &internalPort = *(port.internalPorts()[i]);
    ret.addChild(print(internalPort));
  }

  return ret;
}

StringTree Executer::print(const InteractionValue &interaction) {
  ostringstream oss;

  oss << interaction;

  if (!interaction.isDominated()) oss << "*";

  return StringTree(oss.str());
}

StringTree Executer::print(const Connector &connector) {
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

StringTree Executer::print(const Atom &atom) {
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

StringTree Executer::print(const Compound &compound) {
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

StringTree Executer::print(const Component &component) {
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

// the size should be greater than the total number of jobs
ReadyQueue<Job> Executer::jobs(100000);
