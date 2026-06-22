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

#include <Atom.hpp>
#include <AtomExportPort.hpp>
#include <Compound.hpp>
#include <Interaction.hpp>
#include <InteractionValue.hpp>
#include <ConnectorExportPort.hpp>
#include <QuotedPortReference.hpp>
#include <Priority.hpp>
#include <BipError.hpp>
#include "ExecuteAtomJob.hpp"
#include "ExecuteConnectorJob.hpp"
#include <CycleInPriorities.hpp>
#include <CycleInPrioritiesError.hpp>

// constructors
Compound::Compound(const string &name) :
  ComponentItf(name, COMPOUND),
  Component(name, COMPOUND),
  CompoundItf(name),
  mAllCyclesInPriorities(this, &Compound::computeAllCyclesInPriorities) {
  /* implement your constructor here */
}

// destructor
Compound::~Compound() {
  // get interactions of top level non exported connectors
  for (map<string, Connector *>::const_iterator connectorIt = connectors().begin() ;
       connectorIt != connectors().end() ;
       ++connectorIt) {
    Connector &connector = *connectorIt->second;
   
    connector.release();
  }

  // delete all precomputed cycles
  for (set<CycleInPriorities *>::const_iterator cycleIt = allCyclesInPriorities().begin() ;
       cycleIt != allCyclesInPriorities().end() ;
       ++cycleIt) {
    CycleInPriorities *cycle = *cycleIt;

    delete cycle;
  }
}

/* \brief Execute a port value of a compound component.
 *
 * \param portValue is the target port value, it should be a port value
 * associated to one of the exported ports.
 *
 * \return An error if found during the execution of involved atoms or
 * during the update of port values, BipError::NoError otherwise.
 */
BipError &Compound::execute(PortValue &portValue) {
  // find the port from which comes the port value
#ifndef NDEBUG
  bool found = false;
#endif

  for (map<string, CompoundExportPort *>::const_iterator portIt = ports().begin() ;
       portIt != ports().end() ;
       ++portIt) {
    CompoundExportPort &port = *portIt->second;

    // execute
    if (port.hasPortValue(portValue)) {
      BipError &error = port.execute(portValue);

      if (error.type() != NO_ERROR) {
        return error;
      }

#ifndef NDEBUG
      found = true;
#endif
      break;
    }
  }

  // port value must belong to one of the ports
  assert(found);

  return BipError::NoError;
}

/* \brief Execute an interaction value of a connector of a compound.
 *
 * \param interactionValue is the target interaction value, it should an
 * interaction value of a top-level connector.
 *
 * \return An error if found during the execution of involved atoms or
 * during the update of port values, BipError::NoError otherwise.
 */
BipError &Compound::execute(InteractionValue &interactionValue) {
  // execute the interaction
  BipError &error = interactionValue.execute();

  if (error.type() != NO_ERROR) {
    return error;
  }

  return BipError::NoError;
}

/* \brief Initialize a compound component.
 *
 * \param Recursively calls initialize of all components, and updates
 * port values of the compound 'this'.
 *
 * \return An error if found during the initialization of the involved
 * components or during the update of port values, BipError::NoError otherwise.
 */
BipError &Compound::initialize() {
  // recursive call to sub-components
  for (map<string, Component *>::const_iterator componentIt = components().begin() ;
       componentIt != components().end() ;
       ++componentIt) {
    Component &component = *componentIt->second;

    if (component.type() == COMPOUND) {
      Compound &compound = dynamic_cast<Compound &>(component);
      compound.initialize();
    }
    else if (component.type() == ATOM) {
      Atom &atom = dynamic_cast<Atom &>(component);
      atom.executeJob().initialize();
    }
  }

  // initialize connectors
  for (map<string, Connector *>::const_iterator connectorIt = connectors().begin() ;
       connectorIt != connectors().end() ;
       ++connectorIt) {
    Connector &connector = *connectorIt->second;
    connector.initialize();
  }

  // initialize priorities
  for (vector<Priority *>::const_iterator priorityIt = priorities().begin() ;
       priorityIt != priorities().end() ;
       ++priorityIt) {
    Priority &priority = **priorityIt;

    priority.initialize();
  }

  // initialize connectors
  for (map<string, Connector *>::const_iterator connectorIt = connectors().begin() ;
       connectorIt != connectors().end() ;
       ++connectorIt) {
    Connector &connector = *connectorIt->second;

    connector.initializeAfterPriorities();
  }

  // set dependencies between initializable objects and initialize them
  for (vector<Priority* >::const_iterator priorityIt = priorities().begin() ;
       priorityIt != priorities().end() ;
       ++priorityIt) {
    Priority &priority = **priorityIt;

    mAllCyclesInPriorities.dependsOn(priority.dominatedPriorities());
  }

  mAllCyclesInPriorities.initialize();

  // initialize connector jobs dependencies
  for (map<string, Connector *>::const_iterator connectorIt = connectors().begin() ;
       connectorIt != connectors().end() ;
       ++connectorIt) {
    Connector &connector = *connectorIt->second;

    connector.executeJob().initialize();
  }

  return BipError::NoError;
}

void Compound::initializeMutexs() {
  // recursive call to sub-components
  for (map<string, Component *>::const_iterator componentIt = components().begin() ;
       componentIt != components().end() ;
       ++componentIt) {
    Component &component = *componentIt->second;

    if (component.type() == COMPOUND) {
      Compound &compound = dynamic_cast<Compound &>(component);
      
      compound.initializeMutexs();
    }
    else if (component.type() == ATOM) {
      Atom &atom = dynamic_cast<Atom &>(component);
      
      // allocate mutexs groups in fast mutex vectors
      atom.executeJob().initializeMutexs();
    }
  }
  
  // allocate mutexs groups in fast mutex vectors
  for (map<string, Connector *>::const_iterator connectorIt = connectors().begin() ;
       connectorIt != connectors().end() ;
       ++connectorIt) {
    Connector &connector = *connectorIt->second;

    connector.executeJob().initializeMutexs();
  }
}

void Compound::restartAllAtoms() {
  for (map<string, Component *>::const_iterator componentIt = components().begin() ;
       componentIt != components().end() ;
       ++componentIt) {
    Component &component = *componentIt->second;

    if (component.type() == COMPOUND) {
      Compound &compound = dynamic_cast<Compound &>(component);

      compound.restartAllAtoms();
    }
    else if (component.type() == ATOM) {
      Atom &atom = dynamic_cast<Atom &>(component);

      atom.executeJob().restart();
    }
  }
}

void Compound::configureJobs(Logger &logger) {
  // recursive call to sub-components
  for (map<string, Component *>::const_iterator componentIt = components().begin() ;
       componentIt != components().end() ;
       ++componentIt) {
    Component &component = *componentIt->second;

    if (component.type() == COMPOUND) {
      Compound &compound = dynamic_cast<Compound &>(component);
      compound.configureJobs(logger);
    }
    else if (component.type() == ATOM) {
      Atom &atom = dynamic_cast<Atom &>(component);
      atom.executeJob().setLogger(logger);
    }
  }

  // initialize connectors
  for (map<string, Connector *>::const_iterator connectorIt = connectors().begin() ;
       connectorIt != connectors().end() ;
       ++connectorIt) {
    Connector &connector = *connectorIt->second;
    
    if (!connector.hasExportedPort()) connector.executeJob().setLogger(logger);
  }

  // initialize validators
  for (set<CycleInPriorities *>::const_iterator cycleIt = allCyclesInPriorities().begin() ;
       cycleIt != allCyclesInPriorities().end() ;
       ++cycleIt) {
    CycleInPriorities &cycle = **cycleIt;

    cycle.setLogger(logger);

    if (cycle.resources().empty()) {
      // force validation of cycle in priorities
      cycle.validate();
    }
  }
}


void Compound::computeAllCyclesInPriorities(set<CycleInPriorities *> &cycles) {
  set<CycleInPriorities> allCycles;

  for (vector<Priority *>::const_iterator priorityIt = priorities().begin() ;
       priorityIt != priorities().end() ;
       ++priorityIt) {
    Priority &priority = **priorityIt;

    vector<Priority *> path;

    allCyclesFrom(priority, allCycles, path);
  }

  for (set<CycleInPriorities>::const_iterator cycleIt = allCycles.begin() ;
       cycleIt != allCycles.end() ;
       ++cycleIt) {
    const CycleInPriorities &cycle = *cycleIt;

    // allocate a cycle and update the set of cycles
    CycleInPriorities *newCycle = new CycleInPriorities(cycle.priorities());
    cycles.insert(newCycle);

    // initialize the cycle
    newCycle->initialize();
  }
}

void Compound::allCyclesFrom(Priority &priority, set<CycleInPriorities> &cycles, vector<Priority *> &path) {
  // search for a cycle
  vector<Priority *>::iterator foundIt = find(path.begin(), path.end(), &priority);

  // cycle found!
  if (foundIt != path.end()) {
    cycles.insert(CycleInPriorities(vector<Priority *>(foundIt, path.end())));
  }
  else {
    // add nextPriority to the current path
    path.push_back(&priority);

    for (vector<Priority *>::const_iterator nextPriorityIt = priority.dominatingPriorities().value().begin() ;
         nextPriorityIt != priority.dominatingPriorities().value().end() ;
         ++nextPriorityIt) {
      Priority &nextPriority = **nextPriorityIt;

      // recursive search of cycles from nextPriority
      allCyclesFrom(nextPriority, cycles, path);
    }

    // put back path to its original value
    path.pop_back();
  }
}
