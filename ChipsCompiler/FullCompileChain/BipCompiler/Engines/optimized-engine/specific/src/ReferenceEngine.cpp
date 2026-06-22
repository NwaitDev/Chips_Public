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

#include "ReferenceEngine.hpp"

#include <InteractionValue.hpp>
#include <AtomInternalPort.hpp>
#include <AtomExternalPort.hpp>
#include <Component.hpp>
#include <Compound.hpp>
#include <CompoundExportPort.hpp>
#include <Port.hpp>
#include <Atom.hpp>
#include <BipError.hpp>
#include <CycleInPrioritiesError.hpp>
#include <UnexpectedEventError.hpp>

void serialize(char **, size_t *);
void deserialize(const char *, size_t);

ReferenceEngine::ReferenceEngine(Compound &top) :
  Engine(top),
  mDisableFairness(false)  {
}

ReferenceEngine::ReferenceEngine(Compound &top, bool disableFairness) :
  Engine(top),
  mDisableFairness(disableFairness) {
}

ReferenceEngine::~ReferenceEngine() {
}

BipError& ReferenceEngine::initialize() {
  // initialize top component
  BipError &error = top().initialize();

  if (error.type() != NO_ERROR) {
    return error;
  }

  // initialize all atom external ports
  top().initializeAllAtomExternalPorts();

  return update();
}

/* \brief Execute an interaction value.
 *
 * \param interactionValue is the target interaction value, it should an
 * enabled interaction value of a top-level connector, i.e. it should belong
 * to the set of interactions returned by interactions().
 *
 * \return An error if found during the execution of involved atoms or
 * during the update of port values, BipError::NoError otherwise.
 */
BipError& ReferenceEngine::execute(InteractionValue &interaction) {
  // should be an interaction proposed by the engine
  assert(find(interactions().begin(),
              interactions().end(),
              &interaction)
         != interactions().end());

  // connector of the interaction
  const Connector &connector = interaction.connector();

  // down
  connector.down(interaction);

  // execute
  BipError &error = connector.holder().execute(interaction);

  if (error.type() != NO_ERROR) {
    return error;
  }

  // update component port values
  BipError &errorUpdate = connector.holder().updateUpperLevels();

  if (errorUpdate.type() != NO_ERROR) {
    return error;
  }

  // updates the interaction values and internal ports
  return update();
}

/* \brief Execute an internal port.
 *
 * \param internal is the target internal port, it should an enabled
 * internal port of an atom, i.e. it should belong to the set of internal
 * ports returned by internals().
 *
 * \return An error if found during the execution of involved atoms or
 * during the update of port values, BipError::NoError otherwise.
 */
BipError& ReferenceEngine::execute(AtomInternalPort &internal) {
  // should be an internal proposed by the engine
  assert(find(internals().begin(),
              internals().end(),
              &internal)
         != internals().end());

  // mark all ports as not ready
  internal.holder().allNotReady();

  // execute
  BipError &error = internal.holder().execute(internal);

  if (error.type() != NO_ERROR) {
    return error;
  }

  // update component port values
  BipError &errorUpdate = internal.holder().updateUpperLevels();

  if (errorUpdate.type() != NO_ERROR) {
    return errorUpdate;
  }

  // updates the interaction values and internal ports
  return update();
}

/* \brief Execute an external port.
 *
 * \param external is the target external port, it should a waiting
 * external port of an atom, i.e. it should belong to the set of external
 * ports returned by externals(), and it should also have a pending event.
 *
 * \return An error if found during the execution of involved atoms or
 * during the update of port values, BipError::NoError otherwise.
 */
BipError& ReferenceEngine::execute(AtomExternalPort &external) {
  // should be an internal proposed by the engine
  assert(find(externals().begin(),
              externals().end(),
              &external)
         != externals().end());

  // mark all ports as not ready
  external.holder().allNotReady();

  // execute
  BipError &error = external.holder().execute(external);

  if (error.type() != NO_ERROR) {
    return error;
  }

  // reset the corresponding atom
  external.holder().reset();

  // update component port values
  BipError &errorUpdate = external.holder().updateUpperLevels();

  if (errorUpdate.type() != NO_ERROR) {
    return errorUpdate;
  }

  return update();
}

BipError& ReferenceEngine::checkExternals() {
  vector<AtomExternalPort *>::iterator portIt = waiting().begin();

  // check incoming events on waiting ports
  while (portIt != waiting().end()) {
    AtomExternalPort &port = **portIt;

    assert(port.waiting());

    // /!\ hasEvent() may change at any time
    if (port.hasEvent()) {
      // add port to the enabled external ports
      externals().push_back(&port);
      
      // remove port of the waiting external ports
      portIt = waiting().erase(portIt);
    }
    else {
      ++portIt;
    }
  }

  // check incoming events on non-waiting ports
  for (portIt = unexpected().begin() ;
       portIt != unexpected().end() ;
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

/* \brief Returns the current state of the model.
 *
 * \return an instance of State representing the current state of the model.
 */
State ReferenceEngine::getState() const {
  char *buffer;
  size_t size;

  serialize(&buffer, &size);

  return State(buffer, size);
}

/* \brief Modify the current state of the model.
 *
 * \param state is the new state for the model.
 */
void ReferenceEngine::setState(const State &state) {
  // mark all ports as not ready
  top().allNotReady();

  // set new state of atomic components
  deserialize(state.buffer(), state.size());

  // reset all atoms to force recomputation of connectors / ports values
  top().resetAll();

  // update the components interface (port values)
  top().recursiveUpdate();

  // update the interactions and internal ports of the engine
  update();
}

/* \brief Update interactions values and internal ports.
 *
 * Update interactions values and internal ports w.r.t. current state, so
 * that interactions() and internals() return up-to-date values.
 */
BipError &ReferenceEngine::update() {
  // recompute from scratch
  internals().clear();
  interactions().clear();
  externals().clear();
  waiting().clear();
  unexpected().clear();

  for (vector<AtomExternalPort *>::const_iterator portIt = top().externalPorts().begin() ;
       portIt != top().externalPorts().end() ;
       ++portIt) {
    AtomExternalPort &port = **portIt;
    
    // /!\ hasEvent() may change at any time
    // you must ensure it is read once
    // to keep consistency!
    if (port.waiting()) {
      if (port.hasEvent()) {
        if (!disableFairness() || externals().empty()) {
          externals().push_back(&port);
        }
      }
      else {
        waiting().push_back(&port);
      }
    }
    else {
      unexpected().push_back(&port);

      BipError &error = checkUnexpected(port);

      if (error.type() != NO_ERROR) {
        return error;
      }
    }
  }

  for (vector<AtomInternalPort *>::const_iterator portIt = top().nonExportedInternalPorts().begin() ;
       portIt != top().nonExportedInternalPorts().end() ;
       ++portIt) {
    AtomInternalPort &port = **portIt;

    // add non exported internal ports enabled by transitions
    if (port.hasPortValue()) {
      mInternals.push_back(&port);

      if (disableFairness()) {
        return BipError::NoError;;
      }
    }
  }

  for (vector<Connector *>::const_iterator connectorIt = top().nonExportedConnectors().begin() ;
       connectorIt != top().nonExportedConnectors().end() ;
       ++connectorIt) {
    const Connector &connector = **connectorIt;

    // add maximal interactions of all non exported connectors
    const vector<InteractionValue *> &maximalInteractions = connector.maximalInteractions();

    // keep one maximal interaction
    mInteractions.insert(mInteractions.end(),
                         maximalInteractions.begin(),
                         maximalInteractions.end());

    if (disableFairness() && !mInteractions.empty()) {
      return BipError::NoError;;
    }
  }

  return BipError::NoError;
}

BipError &ReferenceEngine::checkUnexpected(AtomExternalPort &port) {
  assert(!port.waiting());

  // /!\ hasEvent() may change at any time
  // you must ensure it is read once
  // to keep consistency!
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
