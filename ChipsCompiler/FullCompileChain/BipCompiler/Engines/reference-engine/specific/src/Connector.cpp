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

#include <Connector.hpp>
#include <Interaction.hpp>
#include <InteractionValue.hpp>
#include <Compound.hpp>

// constructors
Connector::Connector(const string &name) :
  ConnectorItf(name) {
  /* implement your constructor here */
}

// destructor
Connector::~Connector() {
  /* implement your destructor here */
}


/**
 * \brief Determine if a connector is top-level w.r.t. to the hierarchy of
 * connectors in its holding compound.
 *
 * We consider that a connector is top-level if it has no exported port, or
 * if its exported port is only connected to an exported port of a compound.
 * In other words, a connector is not top-level if its exported port is
 * connected to a connector.
 *
 * \return true if the connector 'this' is top-level.
 */
bool Connector::isTopLevel() const {
  bool ret = true;

  const Compound &compound = holder();

  // in case of exported port, check whether it is connected to a connector or not
  if (hasExportedPort()) {
    // check all connectors of the same hierarchical level
    for (map<string, Connector *>::const_iterator connectorIt = compound.connectors().begin() ;
         connectorIt != compound.connectors().end() ;
         ++connectorIt) {
      const Connector &connector = *connectorIt->second;

      // check all ports of the connector
      for (vector<QuotedPortReference *>::const_iterator portIt = connector.ports().begin() ;
           portIt != connector.ports().end() ;
           ++portIt) {
        const QuotedPortReference &portRef = **portIt;

        // the exported port is connected to a connector => not top-level
        if (&portRef.port() == &exportedPort()) {
          ret = false;
	}
      }
    }
  }

  return ret;
}


/**
 * \brief Compute the set of immediate subconnectors in the hierarchy of
 * connectors.
 *
 * The immediate subconnectors includes only subconnectors that are directly
 * connected to connector 'this' via a ConnectorExportPort. Notice that immediate
 * subconnectors and 'this' are in the same compound, and that they do not
 * include 'this'.
 *
 * \return The set of immediate subconnectors of connector 'this'.
 */
vector<Connector *> Connector::subConnectors() const {
  vector<Connector *> ret;

  for (vector<QuotedPortReference *>::const_iterator portRefIt = ports().begin() ;
       portRefIt != ports().end() ;
       ++portRefIt) {
    QuotedPortReference &portRef = **portRefIt;
    Port &port = portRef.port();

    // connection to sub-connector through port
    if (port.type() == CONNECTOR_EXPORT) {
      ConnectorExportPort &connectorPort = dynamic_cast<ConnectorExportPort &>(port);
      Connector &subConnector = connectorPort.holder();

      ret.push_back(&subConnector);
    }
  }

  return ret;
}


/**
 * \brief Compute all subconnectors.
 *
 * The subconnectors includes all connectors that are connected to 'this',
 * immediately of via other connectors, in the hierarchy of connectors of the
 * compound holding 'this'. Notice that subconnectors do not include 'this'.
 * Subconnectors are sorted in hierarchical order, i.e. the returned list
 * satisfy the following property:
 *   subConnector()[j] cannot be a subconnector of subConnector()[i] if j>i.
 *
 * \return The list of subconnectors of connector 'this', sorted sorted
 * according to the hierarchy.
 */
vector<Connector *> Connector::allSubConnectors() const {
  vector<Connector *> ret;
  vector<Connector *> subconnectors = subConnectors();

  // add subconnectors of all immediate subconnectors
  for (vector<Connector *>::const_iterator connectorIt = subconnectors.begin() ; 
       connectorIt != subconnectors.end() ;
       ++connectorIt) {
    Connector &connector = **connectorIt;
    vector<Connector *> allsubconnectors = connector.allSubConnectors();

    ret.insert(ret.end(), allsubconnectors.begin(), allsubconnectors.end());
  }

  // add all immediate subconnectors
  for (vector<Connector *>::const_iterator connectorIt = subconnectors.begin() ; 
       connectorIt != subconnectors.end() ;
       ++connectorIt) {
    Connector &connector = **connectorIt;

    ret.push_back(&connector);
  }

  return ret;
}

/**
 * \brief Update the exported port values.
 *
 * Update the port values of the exported port of 'this', if applies.
 */
void Connector::updatePortValues() {
  // check for the presence of an exported port
  if (hasExportedPort()) {
    // update the port values of the exported port
    exportedPort().updatePortValues();
  }
}


/**
 * \brief Compute the set of maximal interaction values enabled at the current
 * state.
 *
 * Require up-to-date port values for all connected ports. Maximality is computed
 * based on priorities.
 *
 * Interactions are created and need to be deleted using release().
 *
 * \return The set of interaction values that are maximal and enabled by 'this'.
 */
vector<InteractionValue *> Connector::maximalInteractions() const {
  vector<InteractionValue *> ret;
  vector<InteractionValue *> allInteractions = enabledInteractions();

  // keeps only maximal interactions
  for (vector<InteractionValue *>::const_iterator interactionIt = allInteractions.begin() ;
       interactionIt != allInteractions.end() ;
       ++interactionIt) {
    InteractionValue &interaction = **interactionIt;

    if (!interaction.isDominated()) {
      ret.push_back(&interaction);
    }
    else {
      releaseInteractionValue(interaction);
    }
  }

  return ret;
}

/**
 * \brief Compute the set of interaction values enabled at the current state.
 *
 * Require up-to-date port values for all connected ports.
 * Interactions are created and need to be deleted using release().
 *
 * \return The set of interaction values enabled by 'this'.
 */
vector<InteractionValue *> Connector::enabledInteractions() const {
  vector<InteractionValue *> ret;

  // for all (static) interaction, compute an interaction value (when applies)
  for (vector<Interaction *>::const_iterator interactionIt = interactions().begin() ;
       interactionIt != interactions().end() ;
       ++interactionIt) {
    const Interaction &interaction = **interactionIt;
    // check that ports enable the interaction
    bool enabledByPorts = true;
    for (vector<Port *>::const_iterator portIt = interaction.ports().begin() ;
         portIt != interaction.ports().end() ;
         ++portIt) {
      const Port &port = **portIt;

      if (!port.hasPortValues()) {
        enabledByPorts = false;
      }
    }

    if (enabledByPorts) {
      vector<PortValue *> partialValues;
      enumerateInteractionValues(ret, interaction, partialValues, 0);
    }
  }

  return ret;
}


/**
 * \brief Release all interactions of a list of interactions.
 *
 * Call relaseInteraction for all interactions.
 *
 * \param interactions is a list of interactions to release.
 */
void Connector::release(const vector<Interaction *> &interactions) const {
  for (vector<Interaction *>::const_iterator interactionIt = interactions.begin() ;
       interactionIt != interactions.end() ;
       ++interactionIt) {
    Interaction &interaction = **interactionIt;

    releaseInteraction(interaction);
  }
}


/**
 * \brief Release all interaction values of a list of interactions values.
 *
 * Call relaseInteractionValue for all interaction values.
 *
 * \param interactions is a list of interaction values to release.
 */
void Connector::release(const vector<InteractionValue *> &interactions) const {
  for (vector<InteractionValue *>::const_iterator interactionIt = interactions.begin() ;
       interactionIt != interactions.end() ;
       ++interactionIt) {
    InteractionValue &interaction = **interactionIt;

    releaseInteractionValue(interaction);
  }
}


/**
 * \brief Compute the set of interaction values for the current state
 * recursively.
 *
 * Enumerate the interaction values for an interaction, considering a mandatory
 * part that must be in the interaction values.
 *
 * \param allInteractions is used to store the set interaction values
 * \param partialValues is the mandatory part, i.e. a list of port values that
 * must be in the computed interaction values
 * \param nextPortIndex is the index in the list of ports 'ports()' of interaction
 * from which interaction values are be enumerated
 */
void Connector::enumerateInteractionValues(vector<InteractionValue *> &allInteractions, const Interaction &interaction, vector<PortValue *> partialValues, unsigned int nextPortIndex) const {
  if (nextPortIndex < interaction.ports().size()) {
    const Port *port = interaction.ports()[nextPortIndex];

    for (vector<PortValue *>::const_iterator valueIt = port->portValues().begin() ;
         valueIt != port->portValues().end() ;
         ++valueIt) {
      PortValue *value = *valueIt;

      // enumerate using value
      partialValues.push_back(value);
      enumerateInteractionValues(allInteractions, interaction, partialValues, nextPortIndex + 1);

      // remove value for next iteration (avoids using multiple vector<PortValue *>)
      partialValues.pop_back();
    }
  }
  else {
    // build an interaction value based on interaction and the port values partial values
    vector<PortValue *> values; 

    for (vector<PortValue *>::const_iterator valueIt = partialValues.begin() ;
         valueIt != partialValues.end() ;
         ++valueIt) {
      values.push_back(*valueIt);
    }

    InteractionValue &interactionValue = createInteractionValue(interaction, values);

    // check the guard of the build interaction value, if true, keep it
    if (guard(interactionValue)) {
      allInteractions.push_back(&interactionValue);
    }
    else {
      releaseInteractionValue(interactionValue);
    }
  }
}

string Connector::fullName() const {
  return holder().fullName() + "." + name();
}
