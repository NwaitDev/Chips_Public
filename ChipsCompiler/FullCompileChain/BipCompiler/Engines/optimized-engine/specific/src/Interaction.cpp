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
}

// destructor
Interaction::~Interaction() {
}


/**
 * \brief Compute enabledness of an interaction in its holding connector.
 *
 * Maximality is computed w.r.t. priorities.
 *
 * \return true if interaction 'this' is maximal.
 */
bool Interaction::isEnabled() const {
  // should be a defined interaction
  assert(isDefined());

  bool ret = false;

  // get enabled interactions
  const vector<InteractionValue *> &enabledInteractions = connector().enabledInteractions();

  for (vector<InteractionValue *>::const_iterator interactionIt = enabledInteractions.begin() ;
       interactionIt != enabledInteractions.end() ;
       ++interactionIt) {
    const Interaction &interaction = (*interactionIt)->interaction();

    // if 'this' is in the set of enabled interactions
    if (*this == interaction) {
      ret = true;
      break;
    }
  }
  
  return ret;
}


/**
 * \brief Compute maximality of an interaction in its holding connector.
 *
 * Enabledness is computed without applying priorities. It corresponds to
 * the existance of an interaction value in the holding connector such that
 * its corresponding set of ports and the set of ports corresponding to 
 * interaction 'this' are the same. Sets of ports are given by ports().
 *
 * \return true if interaction 'this' is enabled.
 */
bool Interaction::isMaximal() const {
  // should be a defined interaction
  assert(isDefined());

  bool ret = false;

  // get maximal interactions
  const vector<InteractionValue *> &maximalInteractions = connector().maximalInteractions();

  for (vector<InteractionValue *>::const_iterator interactionIt = maximalInteractions.begin() ;
       interactionIt != maximalInteractions.end() ;
       ++interactionIt) {
    const Interaction &interaction = (*interactionIt)->interaction();

    // if 'this' is in the set of enabled interactions
    if (*this == interaction) {
      ret = true;
      break;
    }
  }
  
  return ret;
}


/**
 * \brief Compute maximality of an interaction in its holding connector.
 *
 * Enabledness is computed without applying priorities. It corresponds to
 * the existance of an interaction value in the holding connector such that
 * its corresponding set of ports and the set of ports corresponding to 
 * interaction 'this' are the same. Sets of ports are given by ports().
 *
 * \return true if interaction 'this' is enabled.
 */
bool Interaction::isLocallyMaximalOrDominated() const {
  // should be a defined interaction
  assert(isDefined());

  bool ret = false;

  // get locally maximal interactions
  const vector<InteractionValue *> &locallyMaximalInteractions = connector().locallyMaximalInteractions();

  for (vector<InteractionValue *>::const_iterator interactionIt = locallyMaximalInteractions.begin() ;
       interactionIt != locallyMaximalInteractions.end() ;
       ++interactionIt) {
    const Interaction &interaction = (*interactionIt)->interaction();

    // if 'this' is in the set of enabled interactions
    if (*this <= interaction) {
      ret = true;
      break;
    }
  }
  
  return ret;
}


/**
 * \brief Check if an interaction is dominated by user-defined priority rules.
 * 
 * The interaction can be enabled or not in its corresponding connector.
 * The graph of priority rules enabled by their guards should be acyclic.
 *
 * \return true if interaction 'this' is dominated through a priority rule.
 */
bool Interaction::isDominatedByPriorities() const {
  bool ret = false;

  for (vector<Priority *>::const_iterator priorityIt = connector().dominatingPriorities().value().begin() ;
       priorityIt != connector().dominatingPriorities().value().end() ;
       ++priorityIt) {
    const Priority &priority = **priorityIt;

    if (priority.appliesLow(*this) && priority.active()) {
      ret = true;
      break;
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
 * interaction, but it should be a defined interaction.
 *
 * \return true if interaction 'this' is dominated by an enabled interaction of
 * the same connector, and considering maximal progress only.
 */
bool Interaction::isDominatedLocally() const {
  // should be a defined interaction
  assert(isDefined());

  bool ret = false;

  // look for interactions with higher priority w.r.t. maximal progress
  const vector<InteractionValue *> &locallyMaximalInteractions = connector().locallyMaximalInteractions();

  for (vector<InteractionValue *>::const_iterator targetIt = locallyMaximalInteractions.begin() ;
       targetIt != locallyMaximalInteractions.end() ;
       ++targetIt) {
    // warning: at this level we consider only interaction, not interaction values
    const Interaction &target = (*targetIt)->interaction();

    // check if maximal progress applies
    if (*this < target) {
      ret = true;
      break;
    }
  }

  return ret;
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
      break;
    }
  }

  return ret;
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
