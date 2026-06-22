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

#include <ExecuteAtomJob.hpp>
#include "ExecuteConnectorJob.hpp"

#include "AtomInternalPort.hpp"
#include "AtomExternalPort.hpp"

#include "Connector.hpp"
#include "Compound.hpp"
#include "Atom.cpp"
#include "Logger.hpp"

#include "Executer.hpp"
#include "BipError.hpp"
#include "UnexpectedEventError.hpp"

ExecuteAtomJob::ExecuteAtomJob(Atom &atom) :
  Job(Executer::jobs, true),
  mInitialized(false),
  mAtom(atom),
  mPortValue(NULL),
  mLogger(NULL) {
}

ExecuteAtomJob::~ExecuteAtomJob() {
}

void ExecuteAtomJob::initialize() {
  const Atom &constAtom = atom();

  // pre-compute the set of non exported internal ports
  for (map<string, AtomInternalPort *>::const_iterator portIt = constAtom.internalPorts().begin() ;
       portIt != constAtom.internalPorts().end() ;
       ++portIt) {
    AtomInternalPort &port = *portIt->second;

    if (!port.isExported()) {
      mNonExportedPorts.push_back(&port);
    }
  }

  mWriter.addResource(atom().resource());
  mAllReserver.addResource(atom().resource());
  
  // add resources for exported ports
  for (map<string, AtomExportPort *>::const_iterator portIt = constAtom.ports().begin() ;
       portIt != constAtom.ports().end() ;
       ++portIt) {
    AtomExportPort &port = *portIt->second;

    if (port.hasEarlyUpdate()) {
      mWriter.addResource(port.resource());
      mAllReserver.addResource(port.resource());
      mPortsDataReserver.addResource(port.resource());
    }
  }

  // add resources for exported data
  for (map<string, AtomExportData *>::const_iterator dataIt = constAtom.data().begin() ;
       dataIt != constAtom.data().end() ;
       ++dataIt) {
    AtomExportData &data = *dataIt->second;

    if (data.hasEarlyUpdate()) {
      mWriter.addResource(data.resource());
      mAllReserver.addResource(data.resource());
      mPortsDataReserver.addResource(data.resource());
    }
  }
}

void ExecuteAtomJob::realJob() {
  BipError *error = &BipError::NoError;

  if (!hasPortValue() && mInitialized) {
    // externally restarted
    free();
  }
  else {
    if (hasPortValue()) {
      // execute w.r.t. target port value
      error = &execute(portValue());
    }
    else if (!mInitialized) {
      // initialize corresponding atom
      error = &initializeAtom();

      // initialize external ports
      initializeAllExternalPorts();

      mInitialized = true;
    }
    else {
      assert(false);
    }
  }

  // inform of readyness of the atom
  if (error->type() != NO_ERROR) {
    logger().log(*error);
  }
  else {
    // execute all external and internal ports
    BipError &error = executeAllExternalPortsAndInternalTransitions();

    if (error.type() != NO_ERROR) {
      logger().log(error);
    }
  }
}

void ExecuteAtomJob::prologue() {
  if (!hasPortValue() && mInitialized) {
    reserveAll();
  }
  
  mWriter.start();
}

void ExecuteAtomJob::epilogue() {
  atom().resource().free();
}

BipError &ExecuteAtomJob::executeAllExternalPortsAndInternalTransitions() {
  bool success = false;

  do {
    success = false;

    // update the status of external ports
    BipError &error = checkExternals();

    if (error.type() != NO_ERROR) {
      return error;
    } 

    // execute external port
    if (!mExternals.empty()) {
      success = true;

      // choose a port randomly
      unsigned int randomIndex = (unsigned int) mExternals.size() * (rand() / (RAND_MAX + 1.0));
      AtomExternalPort &chosenExternalPort = *mExternals[randomIndex];

      // execute the chosen port
      BipError &error = execute(chosenExternalPort);

      if (error.type() != NO_ERROR) {
        return error;
      }
    }
    else {
      // recompute enabled internal ports
      recomputeInternals();

      if (!mInternals.empty()) {
        success = true;

        // choose a port randomly
        unsigned int randomIndex = (unsigned int) mExternals.size() * (rand() / (RAND_MAX + 1.0));
        AtomInternalPort &chosenInternalPort = *mInternals[randomIndex];

        // execute the chosen port
        BipError &error = execute(chosenInternalPort);

        if (error.type() != NO_ERROR) {
          return error;
        }
      }
    }
  } while (success);

  return BipError::NoError;
}

void ExecuteAtomJob::recomputeInternals() {
  // recompute from scratch
  mInternals.clear();

  // loop on intenal ports
  for (vector<AtomInternalPort *>::const_iterator portIt = mNonExportedPorts.begin() ;
       portIt != mNonExportedPorts.end() ;
       ++portIt) {
    AtomInternalPort &port = **portIt;

    if (port.hasPortValue()) {
      mInternals.push_back(&port);
    }
  }
}


BipError &ExecuteAtomJob::checkExternals() {
  vector<AtomExternalPort *>::iterator portIt = mWaiting.begin();

  // check incoming events on waiting ports
  while (portIt != mWaiting.end()) {
    AtomExternalPort &port = **portIt;

    assert(port.waiting());

    // /!\ hasEvent() may change at any time
    if (port.hasEvent()) {
      // add port to the enabled external ports
      mExternals.push_back(&port);
      
      // remove port of the waiting external ports
      portIt = mWaiting.erase(portIt);

      // inform the ready queue on the number of waiting ports
      mReadyQueue.removeSporadicPush(1);
    }
    else {
      ++portIt;
    }
  }

  // check incoming events on non-waiting ports
  for (portIt = mUnexpected.begin() ;
       portIt != mUnexpected.end() ;
       ++portIt) {
    AtomExternalPort &port = **portIt;

    assert(!port.waiting());

    BipError &error = checkUnexpected(port);

    if (error.type() != NO_ERROR) {
      return error;
    }
  }

  return BipError::NoError;
}


BipError &ExecuteAtomJob::recomputeExternals() {
  const Atom &constAtom = atom();

  // inform the ready queue on the number of waiting ports
  mReadyQueue.removeSporadicPush(mWaiting.size());

  // recompute from scratch
  mExternals.clear();
  mWaiting.clear();
  mUnexpected.clear();

  // loop on external ports
  for (map<string, AtomExternalPort *>::const_iterator portIt = constAtom.externalPorts().begin() ;
       portIt != constAtom.externalPorts().end() ;
       ++portIt) {
    AtomExternalPort &port = *portIt->second;

    // /!\ hasEvent() may change at any time
    // you must ensure it is read once
    // to keep consistency!
    if (port.waiting()) {
      if (port.hasEvent()) {
        mExternals.push_back(&port);
      }
      else {
        mWaiting.push_back(&port);
      }
    }
    else {
      mUnexpected.push_back(&port);

      BipError &error = checkUnexpected(port);

      if (error.type() != NO_ERROR) {
        return error;
      }
    }
  }

  // inform the ready queue on the number of waiting ports
  mReadyQueue.addSporadicPush(mWaiting.size());

  return BipError::NoError;
}

BipError &ExecuteAtomJob::checkUnexpected(AtomExternalPort &port) {
  assert(!port.waiting());

  // /!\ hasEvent() may change at any time
  if (port.hasEvent()) {
    // unexpected event
    if (port.policy() == REMEMBER) {
      // nothing to do in this case!
    }
    else if (port.policy() == IGNORE) {
      port.purgeEvents();
    }
    else if (port.policy() == ERROR) {
      BipError &error = *new UnexpectedEventError(port.holder(), port);
      return error;
    }
    else {
      assert(false);
    }
  }
  
  return BipError::NoError;
}

void ExecuteAtomJob::initializeAllExternalPorts() {
  const Atom &constAtom = atom();

  // initialize external ports
  for (map<string, AtomExternalPort *>::const_iterator portIt = constAtom.externalPorts().begin() ;
         portIt != constAtom.externalPorts().end() ;
         ++portIt) {
    AtomExternalPort &port = *portIt->second;

    port.initialize();
  }
}

BipError &ExecuteAtomJob::initializeAtom() {
  // execute w.r.t. target port value
  atom().allNotReady();

  BipError &error = atom().initialize();

  atom().allReady();

  if (error.type() != NO_ERROR) {
    return error;
  }

  // recompute the status of external ports
  return update();
}

BipError &ExecuteAtomJob::execute(PortValue &portValue) {
  // no log (performed by the corresponding connector
  clearPortValue();

  // execute w.r.t. target port value
  atom().allNotReady();

  BipError &error = atom().execute(portValue);

  atom().allReady();

  if (error.type() != NO_ERROR) {
    return error;
  }

  // recompute the status of external ports
  return update();
}

BipError &ExecuteAtomJob::execute(AtomInternalPort &port) {
  // reserve ports and exported variables related resources
  reserve();

  // log the choice
  logger().log(port, mInternals);

  // execute the chosen port
  atom().allNotReady();

  BipError &error = atom().execute(port);

  atom().allReady();

  if (error.type() != NO_ERROR) {
    return error;
  }

  // recompute the status of external ports
  return update();
}

BipError &ExecuteAtomJob::execute(AtomExternalPort &port) {
  // reserve ports and exported variables related resources
  reserve();

  // log the choice
  logger().log(port, mExternals);

  // execute the chosen port
  atom().allNotReady();

  BipError &error = atom().execute(port);

  atom().allReady();

  if (error.type() != NO_ERROR) {
    return error;
  }

  // recompute the status of external ports
  return update();
}

BipError &ExecuteAtomJob::update() {
  // recompute the status of external ports
  return recomputeExternals();
}

void ExecuteAtomJob::reserveAll() {
  bool success = false;
  
  while (!success) {
    success = mAllReserver.tryToReserve();
  }
}

void ExecuteAtomJob::reserve() {
  bool success = false;
  
  while (!success) {
    success = mPortsDataReserver.tryToReserve();
  }
}

void ExecuteAtomJob::free() {
  for (vector<Resource *>::const_iterator resourceIt = mPortsDataReserver.resources().begin() ;
       resourceIt != mPortsDataReserver.resources().end() ;
       ++resourceIt) {
    Resource &resource = **resourceIt;

    resource.free();
  }
}
