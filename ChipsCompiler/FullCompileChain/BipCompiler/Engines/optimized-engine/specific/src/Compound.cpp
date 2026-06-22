/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
 *  Jacques Combaz (jacques.combaz@univ-grenoble-alpes.fr)
 *  Marc Pouhliès
 *  Anakreontas Mentis
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
#include <CycleInPriorities.hpp>
#include <CycleInPrioritiesError.hpp>

// constructors
Compound::Compound(const string &name) :
  ComponentItf(name, COMPOUND),
  Component(name, COMPOUND),
  CompoundItf(name),
  mNonExportedConnectors(this, &Compound::computeNonExportedConnectors),
  mNonExportedInternalPorts(this, &Compound::computeNonExportedInternalPorts),
  mExternalPorts(this, &Compound::computeExternalPorts),
  mAllCyclesInPriorities(this, &Compound::computeAllCyclesInPriorities) {
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

  // update the port values of the component
  return recursiveUpdate();
}


/* \brief Initialize a compound component.
 *
 * 1) Initialize recursively dependencies of resetable objects of 
 * all connectors and priorities.
 * 2) Initialize all atoms and update port values fo exported ports
 * of all compounds.
 *
 * \return An error if found during the initialization fo atoms or
 * during the update of port values, BipError::NoError otherwise.
 */
BipError &Compound::initialize() {
  // initialize all connectors and priorities
  initializeAllConnectorsPriorities();

  // initialize all atoms
  return initializeAllAtoms();
}


void Compound::initializeAllAtomExternalPorts() {
  for (vector<AtomExternalPort *>::const_iterator portIt = externalPorts().begin() ;
       portIt != externalPorts().end() ;
       ++portIt) {
    AtomExternalPort &port = **portIt;

    port.initialize();
  }
}


/* \brief Initialize all atoms.
 *
 *  Initialize recursively all atoms contains in 'this' or in
 * compounds of 'this', and update port values of exported ports of
 * compounds of 'this', as well as port values of exported ports of
 * 'this'.
 *
 * \return An error if found during the initialization of the atoms
 * or during the update of port values of compounds, BipError::NoError
 * otherwise.
 */
BipError &Compound::initializeAllAtoms() {
  for (map<string, Component *>::const_iterator componentIt = components().begin() ;
       componentIt != components().end() ;
       ++componentIt) {
    Component &component = *componentIt->second;

    if (component.type() == COMPOUND) {
      Compound &compound = dynamic_cast<Compound &>(component);

      // recursive call to sub-components
      BipError &error = compound.initializeAllAtoms();

      if (error.type() != NO_ERROR) {
        return error;
      }
    }
    else if (component.type() == ATOM) {
      Atom &atom = dynamic_cast<Atom &>(component);

      // initialize atom
      BipError &error = atom.initialize();

      if (error.type() != NO_ERROR) {
        return error;
      }

      atom.reset();
    }
  }

  // update the port values of the component
  return update();
}


/* \brief Initialize connectors and priorities.
 *
 * Initialize recursively all dependencies of all connectors and priorities
 * of 'this' and of compounds contained in 'this'.
 */
void Compound::initializeAllConnectorsPriorities() {
  // recursive call to sub-components
  for (map<string, Component *>::const_iterator componentIt = components().begin() ;
       componentIt != components().end() ;
       ++componentIt) {
    Component &component = *componentIt->second;

    if (component.type() == COMPOUND) {
      Compound &compound = dynamic_cast<Compound &>(component);
      compound.initializeAllConnectorsPriorities();
    }
  }

  // initialize connectors in an order compatible with hierarchy
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

  // set dependencies of cycles in priorities
  for (vector<Priority* >::const_iterator priorityIt = priorities().begin() ;
       priorityIt != priorities().end() ;
       ++priorityIt) {
    Priority &priority = **priorityIt;

    mAllCyclesInPriorities.dependsOn(priority.dominatedPriorities());
  }

  // set dependencies of non exported connectors / internal ports
  for (map<string, Component *>::const_iterator componentIt = components().begin() ;
       componentIt != components().end() ;
       ++componentIt) {
    Component &component = *componentIt->second;

    if (component.type() == COMPOUND) {
      Compound &compound = dynamic_cast<Compound &>(component);

      mNonExportedConnectors.dependsOn(compound.mNonExportedConnectors);
      mNonExportedInternalPorts.dependsOn(compound.mNonExportedInternalPorts);
    }
  }

  // initialize cycles and non exported connectors / internal ports
  mAllCyclesInPriorities.initialize();
  mNonExportedConnectors.initialize();
  mNonExportedInternalPorts.initialize();
  mExternalPorts.initialize();
}



/**
 * \brief Update port values of connectors, exported ports, and
 * compounds of upper levels.
 *
 * Update port values of exported ports of connectors, exported ports of compound
 * 'this', and compounds containing 'this'.
 * Requires that port values of component exported ports of 'this' are up-to-date.
 *
 * \return An instance of CycleInPrioritiesError if a cycle has been found
 * in priorities, BipError::NoError otherwise.
 */
BipError &Compound::update() {
  // recompute priorities if needed
  for (vector<Priority *>::const_iterator priorityIt = priorities().begin() ;
       priorityIt != priorities().end() ;
       ++priorityIt) {
    Priority &priority = **priorityIt;

    if (priority.changed()) {
      priority.updatePreviousGuard();
      priority.active().reset();

      BipError &error = priority.detectCycle();
      
      if (error.type() != NO_ERROR) {
        return error;
      }
    }
  }

  return BipError::NoError;
}

void Compound::allNotReady() {
  // recursive reset of compounds, and reset of atoms
  for (map<string, Component *>::const_iterator componentIt = components().begin() ;
       componentIt != components().end() ;
       ++componentIt) {
    Component &component = *componentIt->second;

    if (component.type() == COMPOUND) {
      Compound &compound = dynamic_cast<Compound &>(component);

      compound.allNotReady();

    }
    else if (component.type() == ATOM) {
      Atom &atom = dynamic_cast<Atom &>(component);

      atom.allNotReady();
    }
  }
}

void Compound::resetAll() {
  // recursive reset of compounds, and reset of atoms
  for (map<string, Component *>::const_iterator componentIt = components().begin() ;
       componentIt != components().end() ;
       ++componentIt) {
    Component &component = *componentIt->second;

    if (component.type() == COMPOUND) {
      Compound &compound = dynamic_cast<Compound &>(component);

      compound.resetAll();

    }
    else if (component.type() == ATOM) {
      Atom &atom = dynamic_cast<Atom &>(component);

      atom.reset();
    }
  }

  // reset all priorities
  for (vector<Priority *>::const_iterator priorityIt = priorities().begin() ;
       priorityIt != priorities().end() ;
       ++priorityIt) {
    Priority &priority = **priorityIt;

    priority.active().reset();
  }
}

/**
 * \brief Update port values of connectors and exported ports.
 *
 * Update recursively port values of exported ports of connectors, exported
 * ports of compound 'this'.
 *
 * \return An instance of CycleInPrioritiesError if a cycle has been found
 * in priorities, BipError::NoError otherwise.
 */
BipError &Compound::recursiveUpdate() {
  // recursive call to sub-components
  for (map<string, Component *>::const_iterator componentIt = components().begin() ;
       componentIt != components().end() ;
       ++componentIt) {
    Component &component = *componentIt->second;

    if (component.type() == COMPOUND) {
      Compound &compound = dynamic_cast<Compound &>(component);

      BipError &error = compound.recursiveUpdate();

      if (error.type() != NO_ERROR) {
        return error;
      }
    }
  }

  return update();
}


void Compound::computeNonExportedConnectors(vector<Connector *> &nonExportedConnectors) {
  // add non exported connectors of compounds of lower hierarchical levels
  for (map<string, Component *>::const_iterator componentIt = components().begin() ;
       componentIt != components().end() ;
       ++componentIt) {
    Component &component = *componentIt->second;

    if (component.type() == COMPOUND) {
      Compound &compound = dynamic_cast<Compound &>(component);

      nonExportedConnectors.insert(nonExportedConnectors.end(),
                                   compound.nonExportedConnectors().begin(),
                                   compound.nonExportedConnectors().end());
    }
  }

  // add non exported connectors of the current hierarchy level
  for (map<string, Connector *>::const_iterator connectorIt = connectors().begin() ;
       connectorIt != connectors().end() ;
       ++connectorIt) {
    Connector &connector = *connectorIt->second;

    if (!connector.hasExportedPort()) {
      nonExportedConnectors.push_back(&connector);
    }
  }
}

void Compound::computeNonExportedInternalPorts(vector<AtomInternalPort *> &ports) {
  for (map<string, Component *>::const_iterator componentIt = components().begin() ;
       componentIt != components().end() ;
       ++componentIt) {
    const Component &component = *componentIt->second;

    // add non exported internal ports of atomic components of the current hierarchy level
    if (component.type() == ATOM) {
      const Atom &atom = dynamic_cast<const Atom &>(component);

      for (map<string, AtomInternalPort *>::const_iterator portIt = atom.internalPorts().begin() ;
	   portIt != atom.internalPorts().end() ;
           ++portIt) {
        AtomInternalPort &port = *portIt->second;

        if (!port.isExported()) {
          ports.push_back(&port);
        }
      }
    }
    // add non exported internal ports of atomic components of lower hierarchy level
    else if (component.type() == COMPOUND) {
      const Compound &compound = dynamic_cast<const Compound &>(component);

      ports.insert(ports.end(),
                   compound.nonExportedInternalPorts().begin(),
                   compound.nonExportedInternalPorts().end());
    }
    else {
      assert(false);
    }
  }
}


void Compound::computeExternalPorts(vector<AtomExternalPort *> &ports) {
  for (map<string, Component *>::const_iterator componentIt = components().begin() ;
       componentIt != components().end() ;
       ++componentIt) {
    const Component &component = *componentIt->second;

    // add non exported internal ports of atomic components of the current hierarchy level
    if (component.type() == ATOM) {
      const Atom &atom = dynamic_cast<const Atom &>(component);

      for (map<string, AtomExternalPort *>::const_iterator portIt = atom.externalPorts().begin() ;
	   portIt != atom.externalPorts().end() ;
           ++portIt) {
        AtomExternalPort &port = *portIt->second;

        ports.push_back(&port);
      }
    }
    // add non exported internal ports of atomic components of lower hierarchy level
    else if (component.type() == COMPOUND) {
      const Compound &compound = dynamic_cast<const Compound &>(component);

      ports.insert(ports.end(),
                   compound.externalPorts().begin(),
                   compound.externalPorts().end());
    }
    else {
      assert(false);
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
