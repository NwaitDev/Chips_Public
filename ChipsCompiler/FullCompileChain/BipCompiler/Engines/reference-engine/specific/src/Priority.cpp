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

#include <Priority.hpp>
#include <Interaction.hpp>
#include <Compound.hpp>
#include <BipError.hpp>

// constructors
Priority::Priority(Interaction *low, Interaction *high) :
  PriorityItf(low, high) {
  /* implement your constructor here */
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

  if (hasLow()) {
    // should be a defined or empty interaction of a top-level connector
    assert(low().isDefined());
    assert(low().connector().isTopLevel());

    if (guard()) {
      if (interaction == low() || interaction.isDominatedLocallyBy(low())) {
        ret = true;
      }
    }
  }
  else {
    // priority rules * < * are not allowed 
    assert(hasHigh()); 

    // should be a defined interaction of a top-level connector
    assert(high().isDefined() || !high().hasPorts());
    assert(high().connector().isTopLevel());

    if (guard() && interaction.connector().isTopLevel() && &interaction.connector() != &high().connector()) {
      return true;
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
  assert(interaction.isDefined());
  assert(interaction.connector().isTopLevel());

  if (hasHigh()) {
    // should be a defined interaction of a top-level connector
    assert(high().isDefined() || !high().hasPorts());
    assert(high().connector().isTopLevel());

    if (guard()) {
      // priority of the form ... < C:I
      if (high().hasPorts()) {
        if (high() == interaction || high().isDominatedLocallyBy(interaction)) {
          ret = true;
	}
      }
      // priority of the form ... < C:*
      else {
        if (&high().connector() == &interaction.connector()) {
          ret = true;
	}
      }
    }
  }
  else {
    // priority rules * < * are not allowed 
    assert(hasLow());

    // should be a defined or empty interaction of a top-level connector
    assert(low().isDefined());
    assert(low().connector().isTopLevel());
    
    if (guard() && interaction.connector().isTopLevel() && &low().connector() != &interaction.connector()) {
      return true;
    }
  }

  return ret;
}


/**
 * \brief Compute the lower interaction matching the priority rule.
 *
 * If hasLow(), only the single interaction low() matches the lower part of the
 * rule, otherwise all the interactions defined (i.e. computed using interactions())
 * in top-level connectors different from the connector of high() match.
 *
 * \return The lower interactions matching the priority rule
 */
vector<Interaction *> Priority::lowInteractions() const {
  vector<Interaction *> ret;

  if (hasLow()) {
    // create an interaction equals to low()
    ret.push_back(&low());
  }
  // priority rule of the form * < C:I
  else {
    // priority rules * < * are not allowed
    assert(hasHigh());

    const Compound &compound = holder();

    for (map<string, Connector *>::const_iterator connectorIt = compound.connectors().begin() ;
         connectorIt != compound.connectors().end() ;
         ++connectorIt) {
      const Connector &targetConnector = *connectorIt->second;

      // the priority rule C:I < * applies
      if (targetConnector.isTopLevel() &&
	(&targetConnector != &high().connector())) {
        const vector<Interaction *> &allInteractions = targetConnector.interactions();

        // all interactions defined in connector dominate 'this'
        ret.insert(ret.end(), allInteractions.begin(), allInteractions.end());
      }
    }
  }

  return ret;
}

/**
 * \brief Compute the higher interaction matching the priority rule.
 *
 * If hasHigh(), only the single interaction high() matches the higher part of the
 * rule, otherwise all the interactions defined (i.e. computed using interactions())
 * in top-level connectors different from the connector of low() match.
 *
 * \return The higher interactions matching the priority rule
 */
vector<Interaction *> Priority::highInteractions() const {
  vector<Interaction *> ret;

  if (hasHigh()) {
    // priority of the form ... < C:I
    if (high().hasPorts()) {
      ret.push_back(&high());
    }
    // priority of the form ... < C:*
    else {
      const vector<Interaction *> &allInteractions = high().connector().interactions();

      // add all defined interactions
      ret.insert(ret.end(), allInteractions.begin(), allInteractions.end());
    }
  }
  // priority rule of the form C:I < *
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
        const vector<Interaction *> &allInteractions = targetConnector.interactions();

        // all interactions defined in connector dominate 'this'
        ret.insert(ret.end(), allInteractions.begin(), allInteractions.end());
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
  if (guard()) {
    vector<Interaction *> interactions = lowInteractions();

    for (vector<Interaction *>::const_iterator interactionIt = interactions.begin() ;
         interactionIt != interactions.end() ;
         ++interactionIt) {
      Interaction &interaction = **interactionIt;

      // check for cycles from (low) interaction
      BipError &error = interaction.detectCycleInPriorities();

      if (error.type() != NO_ERROR) {
        return error;
      }
    }
  }

  return BipError::NoError;
}
