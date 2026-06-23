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
  mDisableMaximalProgress(false) {
}

ReferenceEngine::ReferenceEngine(Compound &top, bool disableMaximalProgress) :
  Engine(top),
  mDisableMaximalProgress(disableMaximalProgress) {
}

ReferenceEngine::~ReferenceEngine() {
  // release all the interactions
  for (vector<InteractionValue *>::const_iterator interactionIt = interactions().begin() ;
       interactionIt != interactions().end() ;
       ++interactionIt) {
    InteractionValue &interaction = **interactionIt;

    // release the interaction
    interaction.connector().releaseInteractionValue(interaction);
  }
}

BipError& ReferenceEngine::initialize() {
  // disable maximal progress if the option is activated
  top().setDisableMaximalProgressForAllSubCompounds(disableMaximalProgress());

  // initialize components recursively
  BipError &error = top().initialize();

  if (error.type() != NO_ERROR) {
    return error;
  }

  // initialize all atom external ports
  top().initializeAllAtomExternalPorts();

  // update interactions and internals
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

  // down
  interaction.connector().down(interaction);

  // execute
  BipError &error = interaction.connector().holder().execute(interaction);

  if (error.type() != NO_ERROR) {
    return error;
  }

  // update component port values
  BipError &errorUpdate = interaction.connector().holder().updateUpperLevels();

  if (errorUpdate.type() != NO_ERROR) {
    return error;
  }

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

  // execute
  BipError &error = external.holder().execute(external);

  if (error.type() != NO_ERROR) {
    return error;
  }

  // update component port values
  BipError &errorUpdate = external.holder().updateUpperLevels();

  if (errorUpdate.type() != NO_ERROR) {
    return errorUpdate;
  }

  return update();
}

BipError& ReferenceEngine::checkExternals() {
  // recompute enabled, waiting, and unexpected from scratch
  externals().clear();
  waiting().clear();

  vector<AtomExternalPort *> allExternals = top().allExternals();

  // handle unexpected events
  for (vector<AtomExternalPort *>::const_iterator portIt = allExternals.begin() ;
       portIt != allExternals.end() ;
       ++portIt) {
    AtomExternalPort &port = **portIt;

    // /!\ hasEvent() may change at any time
    // to keep consistency we take a snapshot of
    // its current value here.
    bool snapshotHasEvent = port.hasEvent();

    if (port.waiting() && snapshotHasEvent) {
      externals().push_back(&port);
    }
    else if (port.waiting() && !snapshotHasEvent) {
      waiting().push_back(&port);
    }
    else if (!port.waiting() && snapshotHasEvent) {
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
    else {
      assert(!port.waiting() && !snapshotHasEvent);
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
  deserialize(state.buffer(), state.size());

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
  // compute interactions and internal ports enabled at the current state
  computeInteractions();
  computeInternals();
  return checkExternals();
}

/* \brief Update interactions values.
 *
 * Update interactions values w.r.t. current state, so that interactions()
 * returns up-to-date values.
 */
void ReferenceEngine::computeInteractions() {
  // release all the interactions
  for (vector<InteractionValue *>::const_iterator interactionIt = interactions().begin() ;
       interactionIt != interactions().end() ;
       ++interactionIt) {
    InteractionValue &interaction = **interactionIt;

    // release the interaction
    interaction.connector().releaseInteractionValue(interaction);
  }

  // compute interactions from scratch
  interactions().clear();

  // get interactions of all non-exported connectors
  vector<InteractionValue *> allInteractions = top().interactions();

  interactions() = allInteractions;
}

/* \brief Update interactions values.
 *
 * Update internal ports w.r.t. current state, so that internals() returns
 * up-to-date values.
 */
void ReferenceEngine::computeInternals() {
  // compute interactions from scratch
  internals().clear();

  // get interactions of all non-exported connectors
  vector<AtomInternalPort *> allInternals = top().internals();

  internals() = allInternals;
}
