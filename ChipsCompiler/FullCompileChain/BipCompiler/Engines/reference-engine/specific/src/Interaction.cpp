/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
 *  Marc Pouhliès
 *  Jacques Combaz (jacques.combaz@univ-grenoble-alpes.fr)
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

#include <Interaction.hpp>
#include <Connector.hpp>
#include <Port.hpp>
#include <Priority.hpp>
#include <Compound.hpp>
#include <BipError.hpp>
#include <CycleInPrioritiesError.hpp>

#include <iostream>

// constructors
Interaction::Interaction(const Connector &connector) :
  InteractionItf(connector) {
  /* implement your constructor here */
}

// destructor
Interaction::~Interaction() {
  /* implement your destructor here */
}


/**
 * \brief Release the interaction.
 */
void Interaction::release() {
  connector().releaseInteraction(*this);
}


/**
 * \brief Compute enabledness of an interaction in its holding connector.
 *
 * Enabledness is computed without applying priorities. It corresponds to
 * the existance of an interaction value in the holding connector such that
 * its corresponding set of ports and the set of ports corresponding to 
 * interaction 'this' are the same. Sets of ports are given by ports().
 *
 * \return true if interaction 'this' is enabled.
 */
bool Interaction::isEnabled() const {
  // must be a defined interaction
  assert(isDefined());

  bool ret = false;

  const vector<InteractionValue *> interactions = connector().enabledInteractions();

  for (vector<InteractionValue *>::const_iterator interactionIt = interactions.begin() ;
       interactionIt != interactions.end() ;
       ++interactionIt) {
    // cast the target interaction value into an interaction
    const InteractionValue &interactionValue = **interactionIt;

    // if 'this' is in the set of enabled interactions
    if (*this == interactionValue.interaction()) {
      ret = true;
    }
  }

  // relase all the created interactions
  connector().release(interactions);
  
  return ret;
}


/**
 * \brief Check if an interaction is dominated by user-defined priority rules.
 * 
 * The interaction can be enabled or not in its corresponding connector.
 * The graph of priority rules enabled by their guards must be acyclic.
 *
 * \return true if interaction 'this' is dominated through a priority rule.
 */
bool Interaction::isDominatedByPriorities() const {
  // must be a defined interaction
  assert(isDefined());

  bool ret = false;

  // check reachability recursively considering priority rules
  vector<Interaction *> immediateDominators = dominators();

  for (vector<Interaction *>::const_iterator dominatorIt = immediateDominators.begin() ;
       dominatorIt != immediateDominators.end() ;
       ++dominatorIt) {
    const Interaction &dominator = **dominatorIt;

    // direct domination
    if (dominator.isEnabled()) {
      ret = true;
    }

    // indirect domination through maximal progress
    if (dominator.isDominatedLocally()) {
      ret = true;
    }

    // indirect domination through user-defined priority rules
    if (dominator.isDominatedByPriorities()) {
      ret = true;
    }
  }

  return ret;
}


/**
 * \brief Determine if an interaction is dominated w.r.t. maximal progress
 * in the same connector.
 *
 * Maximal progress is a partial order induced by inclusion, implemented
 * by operator<. Notice that interaction 'this' can be a non enabled
 * interaction, but it must be a defined interaction.
 *
 * \return true if interaction 'this' is dominated by an enabled interaction of
 * the same connector, and considering maximal progress only.
 */
bool Interaction::isDominatedLocally() const {
 // must be a defined interaction
  assert(isDefined());

  bool ret = false;

  const vector<InteractionValue *> interactions = connector().enabledInteractions();

  // look for interactions with higher priority w.r.t. maximal progress
  for (vector<InteractionValue *>::const_iterator targetIt = interactions.begin() ;
       targetIt != interactions.end() ;
       ++targetIt) {
    // warning: at this level we consider only interaction, not interaction values
    const InteractionValue &interactionValue = **targetIt;
    const Interaction &target = interactionValue.interaction();

    // check if maximal progress applies
    if (isDominatedLocallyBy(target)) {
      ret = true;
    }
  }

  // release all the created interactions
  connector().release(interactions);

  return ret;
}


/**
 * \brief Computes the priorities such that dominates an interaction.
 *
 * A priority P dominates interaction 'this' if 'this' <= P.low(),
 * meaning that P applies to 'this'.
 *
 * \return returns priorities that dominates interaction 'this'.
 */
vector<Priority *> Interaction::dominatingPriorities() const {
  vector<Priority *> ret;

  // must be a defined interaction
  assert(isDefined());

  const Compound &compound = connector().holder();

  for (vector<Priority *>::const_iterator priorityIt = compound.priorities().begin() ;
       priorityIt != compound.priorities().end() ;
       ++priorityIt) {
    Priority &priority = **priorityIt;

    // add priority if it applies
    if (priority.appliesLow(*this)) {
      ret.push_back(&priority);
    }
  }

  return ret;
}


/**
 * \brief Computes the successors in the graph of user-defined priority rules.
 *
 * \return returns the successors graph of user-defined priority rules.
 */
vector<Interaction *> Interaction::dominators() const {
  vector<Interaction *> ret;

  vector<Priority *> priorities = dominatingPriorities();

  for (vector<Priority *>::const_iterator priorityIt = priorities.begin() ;
       priorityIt != priorities.end() ;
       ++priorityIt) {
    Priority &priority = **priorityIt;
    vector<Interaction *> interactions = priority.highInteractions();

    // add all the high interactions
    ret.insert(ret.end(), interactions.begin(), interactions.end());
  }

  return ret;
}


/**
 * \brief Detects if there a cycle in the priorities from an interaction.
 *
 * Priorities are defined as the transitive closure of the union of maximal
 * progress (i.e. inclusion of interactions values implemented by operator<)
 * and user-defined priority rules (i.e. instances of Priority given by
 * priorities()).
 *
 * \return An instance of CycleInPrioritiesError if a cyle has been found
 * in priorities, BipError::NoError otherwise.
 */
BipError &Interaction::detectCycleInPriorities() const {
  vector<const Interaction *> path;
  path.push_back(this);

  return detectCycleInPriorities(path);
}


/**
 * \brief Check for cycles in the priorities from an interaction.
 *
 * Priorities are defined as the transitive closure of the union of maximal
 * progress (i.e. inclusion of interactions values implemented by operator<)
 * and user-defined priority rules (i.e. instances of Priority given by
 * priorities()).
 *
 * \param path represents the already seen interactions.
 *
 * \return An instance of CycleInPrioritiesError if a cyle has been found
 * in priorities, BipError::NoError otherwise.
 */
BipError &Interaction::detectCycleInPriorities(const vector<const Interaction *> &path) const {
  // must be a defined interaction
  assert(isDefined());

  vector<Priority *> priorities = dominatingPriorities();

  // find cycle(s) from dominating priorities
  for (vector<Priority *>::const_iterator priorityIt = priorities.begin() ;
       priorityIt != priorities.end() ;
       ++priorityIt) {
    const Priority &priority = **priorityIt;
    vector<Interaction *> dominatorsThroughPriority = priority.highInteractions();

    // check for cycles from all dominators of 'this' w.r.t. priority
    for (vector<Interaction *>::const_iterator dominatorIt = dominatorsThroughPriority.begin() ;
         dominatorIt != dominatorsThroughPriority.end() ;
         ++dominatorIt) {
      const Interaction &dominator = **dominatorIt;
      vector<const Interaction *> updatedPath = path;

      // add intermediate interactions if needed
      if (priority.hasLow()) {
        if (*this != priority.low()) {
          updatedPath.push_back(&priority.low());
        }
      }
      updatedPath.push_back(&dominator);

      // check for a cycle through maximal progress
      for (unsigned int i = 0 ; i < updatedPath.size() - 1 ; ++i) {
        // cycle through max progress
        if (dominator <= *updatedPath[i]) {
          CycleInPrioritiesError &error = *(new CycleInPrioritiesError());
          vector<const Interaction *> &cycle = error.cycle();

          // insert all interactions of the cycle
          cycle.insert(cycle.begin(), updatedPath.begin() + i, updatedPath.end());

          // add the intermediate domination (i.e. through maximal progress)
          if (dominator != *updatedPath[i]) {
            error.addCycle(*updatedPath[i]);
          }

          return error;
        }
      }

      // check for a cycle through user-defined priority rules
      BipError &error = dominator.detectCycleInPriorities(updatedPath);

      if (error.type() != NO_ERROR) {
        return error;
      }
    }
  }

  return BipError::NoError;
}


/**
 * \brief Computes the index of a port.
 *
 * The index is computed with respect to the list of ports given by ports().
 *
 * \param port corresponds to the target port.
 *
 * \return the index of port if port is found in ports(), ports().size
 * otherwise.
 */
unsigned int Interaction::index(const Port &port) const {
  unsigned ret = ports().size();

  for (unsigned int i = 0 ;
       i < ports().size() ;
       ++i) {
    const Port &targetPort = *ports()[i];

    if (&targetPort == &port) {
      ret = i;
    }
  }

  return ret;
}


/**
 * \brief Maximal progress priority.

 * \param interaction corresponds to the higher interaction value in the
 * maximal progress priority, whereas 'this' is the smaller interaction.
 *
 * \return true if interaction has more priority than 'this' with
 * respect to maximal progress priorities.
 */
bool Interaction::isDominatedLocallyBy(const Interaction &interaction) const {
  if (connector().holder().disableMaximalProgress()) {
    return false;
  }
  else {
    return *this < interaction;
  }
}


ostream& operator<<(ostream &o, const Interaction &interaction) {
  o << interaction.connector().name() << ":";

  for (unsigned int i = 0 ; i < interaction.ports().size() ; ++i) {
    o << " " << interaction.ports()[i]->name();
  }

  return o;
}

ostream& operator<<(ostream &o, const Interaction *interaction) {
  return o << *interaction;
}
