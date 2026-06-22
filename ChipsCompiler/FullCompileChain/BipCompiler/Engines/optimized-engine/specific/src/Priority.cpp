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

#include <Priority.hpp>
#include <Interaction.hpp>
#include <Compound.hpp>
#include <BipError.hpp>
#include <CycleInPrioritiesError.hpp>
#include <AtomExportData.hpp>
#include <CompoundExportData.hpp>
#include <CycleInPriorities.hpp>

// constructors
Priority::Priority(Interaction *lowInteraction, Interaction *highInteraction) :
  PriorityItf(lowInteraction, highInteraction),
  mDominatingPriorities(this, &Priority::computeDominatingPriorities),
  mDominatedPriorities(this, &Priority::computeDominatedPriorities),
  mPreviousGuard(false),
  mActive(this, &Priority::recomputeActive) {
}

// destructor
Priority::~Priority() {
  /* implement your destructor here */
}


/**
 * \brief 
 *
 * \return 
 */
bool Priority::appliesLow(const Interaction &interaction) const {
  bool ret = false;

  // should be a defined interaction of a top-level connector
  assert(interaction.isDefined() || !interaction.hasPorts());

  if (interaction.connector().isTopLevel()) {
    if (hasLow()) {
      // should be a defined or empty interaction of a top-level connector
      assert(low().isDefined());
      assert(low().connector().isTopLevel());

      if (interaction <= low()) {
        ret = true;
      }
    }
    else {
      // priority rules * < * are not allowed
      assert(hasHigh()); 

      // should be a defined interaction of a top-level connector
      assert(high().isDefined() || !high().hasPorts());
      assert(high().connector().isTopLevel());

      if (&interaction.connector() != &high().connector()) {
        return true;
      }
    }
  }

  return ret;
}


/**
 * \brief 
 *
 * \return 
 */
bool Priority::appliesHigh(const Interaction &interaction) const {
  bool ret = false;

  // should be a defined interaction of a top-level connector
  assert(interaction.isDefined() || !interaction.hasPorts());

  if (interaction.connector().isTopLevel()) {
    if (hasHigh()) {
      // should be a defined interaction of a top-level connector
      assert(high().isDefined() || !high().hasPorts());
      assert(high().connector().isTopLevel());

      if (high() <= interaction) {
        ret = true;
      }
    }
    else {
      // priority rules * < * are not allowed
      assert(hasLow());

      // should be a defined or empty interaction of a top-level connector
      assert(low().isDefined());
      assert(low().connector().isTopLevel());
    
      if (&low().connector() != &interaction.connector()) {
        return true;
      }
    }
  }

  return ret;
}


/**
 * \brief Detects if there a cycle in the priorities from a priority.
 *
 * Priorities are defined as the transitive closure of the union of maximal
 * progress (i.e. inclusion of interactions values implemented by operator<)
 * and user-defined priority rules (i.e. instances of Priority given by
 * priorities()).
 *
 * \return An instance of CycleInPrioritiesError if a cycle has been found
 * in priorities, BipError::NoError otherwise.
 */
BipError &Priority::detectCycle() const {
  for (vector<const CycleInPriorities *>::const_iterator cycleIt = cycles().begin() ;
       cycleIt != cycles().end() ;
       ++cycleIt) {
    const CycleInPriorities &cycle = **cycleIt;

    if (cycle.allGuardsTrue()) {
      CycleInPrioritiesError &error = *(new CycleInPrioritiesError());

      vector<const Interaction *> interactions = cycle.interactions();

      for (vector<const Interaction *>::const_iterator interactionIt = interactions.begin() ;
           interactionIt != interactions.end() ;
           ++interactionIt) {
        const Interaction &interaction = **interactionIt;

        error.addCycle(interaction);
      }
      

      return error;
    }
  }

  return BipError::NoError;
}


void Priority::computeDominatingPriorities(vector<Priority *> &priorities) {
  if (hasHigh()) {
    for (vector<Priority *>::const_iterator priorityIt = high().connector().dominatingPriorities().value().begin() ;
         priorityIt != high().connector().dominatingPriorities().value().end() ;
         ++priorityIt) {
      Priority &priority = **priorityIt;

      if (priority.appliesLow(high())) {
        priorities.push_back(&priority);
      }
    }
  }
  else {
    // this is of the from ... < *:*
    const Compound &compound = holder();

    for (vector<Priority *>::const_iterator priorityIt = compound.priorities().begin() ;
         priorityIt != compound.priorities().end() ;
         ++priorityIt) {
      Priority &priority = **priorityIt;

      assert(hasLow());

      if (priority.hasLow()) {
        if (&priority.low().connector() != &low().connector()) {
          priorities.push_back(&priority);
        }
      }
      else {
        // priority is of the from *:* < ...
        assert(priority.hasHigh());

        for (map<string, Connector *>::const_iterator connectorIt = compound.connectors().begin() ;
             connectorIt != compound.connectors().end() ;
             ++connectorIt) {
          Connector &connector = *connectorIt->second;

          // if exists a connector statisfying both wildcards
          if (connector.isTopLevel() &&
              &connector != &low().connector() &&
              &connector != &priority.high().connector()) {
            // connector must have at least one defined interaction
            // to match the wildcard
            assert(!connector.interactions().empty());

            priorities.push_back(&priority);
          }
        }
      } 
    }
  }
}

void Priority::computeDominatedPriorities(vector<Priority *> &priorities) {
  if (hasLow()) {
    for (vector<Priority *>::const_iterator priorityIt = low().connector().dominatedPriorities().value().begin() ;
         priorityIt != low().connector().dominatedPriorities().value().end() ;
         ++priorityIt) {
      Priority &priority = **priorityIt;

      if (priority.appliesHigh(low())) {
        priorities.push_back(&priority);
      }
    }
  }
  else {
    // this is of the from *:* < ...
    const Compound &compound = holder();

    for (vector<Priority *>::const_iterator priorityIt = compound.priorities().begin() ;
         priorityIt != compound.priorities().end() ;
         ++priorityIt) {
      Priority &priority = **priorityIt;

      assert(hasHigh());

      if (priority.hasHigh()) {
        if (&priority.high().connector() != &high().connector()) {
          priorities.push_back(&priority);
        }
      }
      else {
        // priority is of the from ... < *:*
        assert(priority.hasLow());

        for (map<string, Connector *>::const_iterator connectorIt = compound.connectors().begin() ;
             connectorIt != compound.connectors().end() ;
             ++connectorIt) {
          Connector &connector = *connectorIt->second;

          // if exists a connector statisfying both wildcards
          if (connector.isTopLevel() &&
              &connector != &high().connector() &&
              &connector != &priority.low().connector()) {
            // connector must have at least one defined interaction
            // to match the wildcard
            assert(!connector.interactions().empty());

            priorities.push_back(&priority);
          }
        }
      } 
    }
  }
}

void Priority::recomputeActive(bool &activity) const {
  activity = false;

  // cycles need to be checked before
  assert(detectCycle().type() == NO_ERROR);

  if (guard()) {
    // check if the priority applies directly
    if (hasHigh()) {
      // check dependencies
      assert(mActive.isDependentOf(high().connector().locallyMaximalInteractions()));

      if (high().hasPorts()) {
       // check if the priority is active itself
        if (high().isLocallyMaximalOrDominated()) {
          activity = true;
          return;
        }
      }
      // priority of the form ... < C:*
      else {
        const Connector &connector = high().connector();
        // check for the presence of interactions in connector
        const vector<InteractionValue *> &locallyMaximalInteractions = connector.locallyMaximalInteractions(); 

        if (!locallyMaximalInteractions.empty()) {
          activity = true;
          return;
        }
      }
    }
    // priority of the form ... < *:*
    else {
      // priority rules * < * are not allowed 
      assert(hasLow());

      const Compound &compound = holder();
      for (map<string, Connector *>::const_iterator connectorIt = compound.connectors().begin() ;
           connectorIt != compound.connectors().end() ;
           ++connectorIt) {
        const Connector &targetConnector = *connectorIt->second;

        // the priority rule C:I < * applies
        if (targetConnector.isTopLevel() &&
          (&targetConnector != &low().connector())) {
          // check dependencies
          assert(mActive.isDependentOf(high().connector().locallyMaximalInteractions()));

          // check for the presence of interactions in targetConnector
          const vector<InteractionValue *> &locallyMaximalInteractions = targetConnector.locallyMaximalInteractions(); 

          if (!locallyMaximalInteractions.empty()) {
            activity = true;
            return;
          }
	    }
      }
    }

    // check if the priority applies indirectly
    for (vector<Priority *>::const_iterator priorityIt = dominatingPriorities().value().begin() ;
         priorityIt != dominatingPriorities().value().end() ;
         ++priorityIt) {
      Priority &priority = **priorityIt;

      if (priority.active()) {
        activity = true;
        return;
      }
    }
  }
}

void Priority::initialize() {
  // set dependencies between initializable objects
  if (hasHigh()) {
    mDominatingPriorities.dependsOn(high().connector().dominatingPriorities());
  }
  if (hasLow()) {
    mDominatedPriorities.dependsOn(low().connector().dominatedPriorities());
  }

  mDominatingPriorities.initialize();
  mDominatedPriorities.initialize();

  // set dependencies to locally maximal interactions of connectors
  if (hasHigh()) {
    const Connector &highConnector = high().connector();

    mActive.dependsOn(highConnector.locallyMaximalInteractions());
  }
  else {
    // priority rules * < * are not allowed 
    assert(hasLow());

    const Compound &compound = holder();
    for (map<string, Connector *>::const_iterator connectorIt = compound.connectors().begin() ;
         connectorIt != compound.connectors().end() ;
         ++connectorIt) {
      const Connector &targetConnector = *connectorIt->second;

      // the priority rule C:I < * applies
      if (targetConnector.isTopLevel() &&
        (&targetConnector != &low().connector())) {
        mActive.dependsOn(targetConnector.locallyMaximalInteractions());
      }
    }
  }

  // set dependencies to active of other priorities
  for (vector<Priority *>::const_iterator priorityIt = dominatingPriorities().value().begin() ;
       priorityIt != dominatingPriorities().value().end() ;
       ++priorityIt) {
    Priority &priority = **priorityIt;

    mActive.dependsOn(priority.mActive);
  }

  // set dependencies to data of components
  for (vector<Data *>::const_iterator dataIt = data().begin() ;
       dataIt != data().end() ;
       ++dataIt) {
    Data *data = *dataIt;

    // go through the hierarchy to reach the corresponding atom
    while (data->type() == COMPOUND_EXPORT) {
      CompoundExportData &compoundData = dynamic_cast<CompoundExportData &>(*data);
      data = &compoundData.forwardData();
    }

    // should be a data exported by an atom
    assert(data->type() == ATOM_EXPORT);

    AtomExportData &atomData = dynamic_cast<AtomExportData &>(*data);

    // add a dependency to atomData
    mActive.dependsOn(atomData.reset());
  }
}
