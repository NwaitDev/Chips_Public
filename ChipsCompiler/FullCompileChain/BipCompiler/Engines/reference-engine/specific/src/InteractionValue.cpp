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

#include <InteractionValue.hpp>
#include <PortValue.hpp>
#include <Connector.hpp>
#include <Port.hpp>
#include <AtomExportPort.hpp>
#include <CompoundExportPort.hpp>
#include <Atom.hpp>
#include <Compound.hpp>
#include <BipError.hpp>

// constructors
InteractionValue::InteractionValue() :
  InteractionValueItf() {
  /* implement your constructor here */
}

// destructor
InteractionValue::~InteractionValue() {
  /* implement your destructor here */
}


/**
 * \brief Execute the interaction.
 *
 * Executing an interaction corresponds to executing all the involved
 * components and connetors. This might trigger recursive calls to
 * execute() methods through the hierarchy of connectors and components.
 *
 * For compounds and atoms, execute() method is called using the
 * corresponding port value as a parameter.
 *
 * For connectors, execute() method of their exported ports is
 * called using the corresponding port value as a parameter.
 *
 * \return An error if found during the execution of involved atoms or
 * during the update of port values, BipError::NoError otherwise.
 */
BipError &InteractionValue::execute() {
  // executed all connected connectors, atoms or compounds
  for (unsigned int i = 0 ; i < ports().size() ; ++i) {
    Port &port = *ports()[i];
    PortValue &portValue = *portValues()[i];

    // for components, call their execute() method
    if (port.type() == ATOM_EXPORT) {
      AtomExportPort &atomPort = dynamic_cast<AtomExportPort &>(port);
      BipError &error = atomPort.holder().execute(portValue);

      if (error.type() != NO_ERROR) {
        return error;
      }
    }
    else if (port.type() == COMPOUND_EXPORT) {
      CompoundExportPort &compoundPort = dynamic_cast<CompoundExportPort &>(port);
      BipError &error = compoundPort.holder().execute(portValue);

      if (error.type() != NO_ERROR) {
        return error;
      }
    }
    else if (port.type() == CONNECTOR_EXPORT) {
      ConnectorExportPort &connectorPort = dynamic_cast<ConnectorExportPort &>(port);
      BipError &error = connectorPort.execute(portValue);

      if (error.type() != NO_ERROR) {
        return error;
      }
    }
    else {
      // not a valid type
      assert(false);
    }
  }

  return BipError::NoError;
}

/**
 * \brief Determine if an interaction is defined by a its holding connector.
 *
 * \return true if 'this' is define by its holding connector.
 */
bool InteractionValue::isAllDefined() const {
  bool ret = true;

  if (!interaction().isDefined()) {
    ret = false;
  }

  for (unsigned int i = 0 ; i < ports().size() ; ++i) {
    Port &port = *ports()[i];
  
    // if there is a sub-connector
    if (port.type() == CONNECTOR_EXPORT) {
      ConnectorExportPort &connectorPort = dynamic_cast<ConnectorExportPort &>(port);
      PortValue &value = *portValues()[i];
      const InteractionValue &subInteraction = connectorPort.interaction(value);
      
      // check interactions of subconnectors
      if (!subInteraction.isAllDefined()) {
        ret = false;
      }
    }
  }
  
  return ret;
}


/**
 * \brief Compute enabledness of an interaction in its holding connector.
 *
 * Enabledness is computed without applying priorities. It corresponds to
 * the existance of an interaction value in the holding connector that
 * equals interaction value 'this'. 
 *
 * \return true if interaction 'this' is enabled.
 */
bool InteractionValue::isEnabled() const {
  // should be a defined interaction
  assert(isAllDefined());

  bool ret = false;

  const vector<InteractionValue *> interactions = connector().enabledInteractions();

  for (vector<InteractionValue *>::const_iterator interactionIt = interactions.begin() ;
       interactionIt != interactions.end() ;
       ++interactionIt) {
    const InteractionValue &interaction = **interactionIt;

    // if 'this' is in the set of enabled interactions
    if (*this == interaction) {
      ret = true;
    }
  }

  // relase all the created interactions
  connector().release(interactions);
  
  return ret;
}


/**
 * \brief Determine if an interaction is dominated.
 *
 * An an interaction I is dominated if there exists another interaction J
 * such that J is enabled and J has more priority that I. Priorities is 
 * partial order defined as the transitive closure of maximal progress
 * (implemented by operator< for Interaction and InteractionValue) and
 * user-defined priority rules implemented by instances of Priority.
 * Notice that interaction 'this' can be a non enabled interaction,
 * but it should be a defined interaction.
 * 
 * \return true if interaction 'this' is dominated by an enabled interaction.
 */
bool InteractionValue::isDominated() const {
  // should be a defined interaction
  assert(isAllDefined());

  // disabling comes from maximal progress (in the same connector
  // or user-defined priority rules 
  return isDominatedLocally() || isDominatedByPriorities();
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
bool InteractionValue::isDominatedLocally() const {
  // should be a defined interaction
  assert(isAllDefined());

  bool ret = false;

  const vector<InteractionValue *> interactions = connector().enabledInteractions();

  // look for interactions with higher priority
  for (vector<InteractionValue *>::const_iterator targetIt = interactions.begin() ;
       targetIt != interactions.end() ;
       ++targetIt) {
    InteractionValue &target = **targetIt;

    // check if maximal progress applies
    if (isDominatedLocallyBy(target)) {
      ret = true;
    }
  }

  // release all the create interactions
  connector().release(interactions);

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
bool InteractionValue::isDominatedLocallyBy(const InteractionValue &interaction) const {
  if (connector().holder().disableMaximalProgress()) {
    return false;
  }
  else {
    return *this < interaction;
  }
}

/**
 * \brief Tests inclusion of interaction values.
 *
 * Inclusion of interactions corresponds to inclusion of corresponding
 * sets of ports given by ports(), and it only applies for interactions
 * of the same connector. It also checks inclusion of interaction values
 * of sub-connectors.
 *
 * \param interaction corresponds to the higher interaction value in the
 * inclusion relation, whereas 'this' is the smaller interaction.
 *
 * \return true if 'this' is included in 'interaction'.
 */
bool InteractionValue::operator<=(const InteractionValue &interactionValue) const {
  bool ret = true;

  // check inclusion of interactions w.r.t. top-level connector only
  if (!(interaction() <= interactionValue.interaction())) {
    ret = false;
  }
  else {
    // check if ports of 'this' are also ports of interaction, and do the same
    // for interactions of subconnectors
    for (unsigned int i = 0 ; i < ports().size() ; ++i) {
      Port &port = *ports()[i];
  
      // already checked in the boolean condition of the if
      assert(interactionValue.interaction().contains(port));

      if (port.type() == CONNECTOR_EXPORT) {
        ConnectorExportPort &connectorPort = dynamic_cast<ConnectorExportPort &>(port);

        unsigned int targetIndex = interactionValue.interaction().index(port);

        PortValue &value = *portValues()[i];
        PortValue &targetValue = *interactionValue.portValues()[targetIndex];

        const InteractionValue &subInteraction = connectorPort.interaction(value);
        const InteractionValue &targetSubInteraction = connectorPort.interaction(targetValue);

        // check interactions of subconnectors
        if (!(subInteraction <= targetSubInteraction)) {
          ret = false;
	}
      }
    }
  }

  return ret;
}

ostream& operator<<(ostream &o, const InteractionValue &value) {
  for (unsigned int i = 0 ; i < value.ports().size() ; ++i) {
    const Port &port = *(value.ports()[i]);

    if (i > 0) o << " ";

    if (port.type() == ATOM_EXPORT) {
      const AtomExportPort &atomPort = dynamic_cast<const AtomExportPort &>(port);
      o << atomPort.holder().name();
    }
    else if (port.type() == COMPOUND_EXPORT) {
      const CompoundExportPort &compoundPort = dynamic_cast<const CompoundExportPort &>(port);
      o << compoundPort.holder().name();
    }
    else if (port.type() == CONNECTOR_EXPORT) {
      const ConnectorExportPort &connectorPort = dynamic_cast<const ConnectorExportPort &>(port);
      o << connectorPort.holder().name();
    }
    else {
      assert(false);
    }
    o << "."; 
    o << value.ports()[i]->name();
    o << "(" << value.portValues()[i] << ")";
  }

  return o;
}

ostream& operator<<(ostream &o, const InteractionValue *value) {
  return o << *value;
}

