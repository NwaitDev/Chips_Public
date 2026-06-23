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

#include <Connector.hpp>
#include <Interaction.hpp>
#include <InteractionValue.hpp>
#include <Compound.hpp>
#include <Atom.hpp>
#include <AtomExportPort.hpp>
#include <ConnectorExportPort.hpp>
#include <CompoundExportPort.hpp>


// constructors
Connector::Connector(const string &name) :
  ConnectorItf(name),
  mAllEnabledPorts(this, &Connector::recomputeAllEnabledPorts, NULL),
  copyOfmAllEnabledPorts(NULL),
  mInteractions(this, &Connector::computeInteractions),
  mEnabledInteractions(this, &Connector::recomputeEnabledInteractions),
  mMaximalInteractions(this, &Connector::recomputeMaximalInteractions),
  mLocallyMaximalInteractions(this, &Connector::recomputeLocallyMaximalInteractions),
  mDominatingPriorities(this, &Connector::computeDominatingPriorities),
  mDominatedPriorities(this, &Connector::computeDominatedPriorities),
  mIsTopLevel(this, &Connector::computeIsTopLevel),
  mSubConnectors(this, &Connector::computeSubConnectors),
  mAllSubConnectors(this, &Connector::computeAllSubConnectors),
  mAllDominatingPriorities(this, &Connector::computeAllDominatingPriorities),
  mAllDependentConnectors(this, &Connector::computeAllDependentConnectors),
  mExecuteJob(*this) {
  // set all the dependencies between resetable objects
  mEnabledInteractions.dependsOn(mAllEnabledPorts);
  mLocallyMaximalInteractions.dependsOn(mAllEnabledPorts);
  mMaximalInteractions.dependsOn(mLocallyMaximalInteractions);
  
  // set all the dependencies between initializable objects
  mDominatingPriorities.dependsOn(mIsTopLevel);
  mDominatedPriorities.dependsOn(mIsTopLevel);
  mAllSubConnectors.dependsOn(mSubConnectors);
}

// destructor
Connector::~Connector() {
  //if (mAllEnabledPorts != NULL) {
  //  delete mAllEnabledPorts;
  //}
}


/**
 * \brief Determine if a connector is top-level in its holding compound.
 *
 * We consider that a connector is top-level if it has no exported port, or
 * if its exported port is only connected to an exported port of a compound.
 *
 * \return true if the connector 'this' is top-level.
 */
void Connector::computeIsTopLevel(bool &isTopLevel) {
  isTopLevel = true;

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

        // the exported port is connected to a connector => non top-level!
        if (&portRef.port() == &exportedPort()) {
          isTopLevel = false;
          break;
        }
      }
    }
  }
}


/**
 * \brief Compute the set of immediate subconnectors.
 *
 * The immediate subconnectors includes only subconnectors that are directly
 * connected to connector 'this' via a ConnectorExportPort. Notice that immediate
 * subconnectors and 'this' are in the same compound, and that they do not
 * include 'this'.
 *
 * \return The set of immediate subconnectors of connector 'this'.
 */
void Connector::computeSubConnectors(vector<Connector *> &subConnectors) {
  for (vector<QuotedPortReference *>::const_iterator portRefIt = ports().begin() ;
       portRefIt != ports().end() ;
       ++portRefIt) {
    QuotedPortReference &portRef = **portRefIt;
    Port &port = portRef.port();

    // connection to sub-connector through port
    if (port.type() == CONNECTOR_EXPORT) {
      ConnectorExportPort &connectorPort = dynamic_cast<ConnectorExportPort &>(port);
      Connector &subConnector = connectorPort.holder();

      subConnectors.push_back(&subConnector);
    }
  }
}


/**
 * \brief Compute the list of subconnectors.
 *
 * The subconnectors includes all connectors that are connected to 'this',
 * immediately of via other connectors, and that are in the compound
 * holding 'this'. Notice that subconnectors do not include 'this'.
 * Subconnectors are sorted in hierarchical order, i.e.:
 * subConnector()[j] cannot be a subconnector of subConnector()[i] if j>i.
 *
 * \return The list of subconnectors of connector 'this', sorted sorted in hierarchical.
 */
void Connector::computeAllSubConnectors(vector<Connector *> &allSubConnectorsVector) {
  // add subconnectors of all immediate subconnectors
  for (vector<Connector *>::const_iterator connectorIt = subConnectors().begin() ; 
       connectorIt != subConnectors().end() ;
       ++connectorIt) {
    Connector &connector = **connectorIt;

    allSubConnectorsVector.insert(allSubConnectorsVector.end(), connector.allSubConnectors().begin(), connector.allSubConnectors().end());
  }

  // add all immediate subconnectors
  for (vector<Connector *>::const_iterator connectorIt = subConnectors().begin() ; 
       connectorIt != subConnectors().end() ;
       ++connectorIt) {
    Connector &connector = **connectorIt;

    allSubConnectorsVector.push_back(&connector);
  }
}


/**
 * \brief Compute the set of maximal interaction values enabled at the current state.
 *
 * Requires up-to-date port values for all connected ports. Maximality is computed
 * based on maximal progress priority amongst the interactions enabled in the same
 * connector, i.e. in connector 'this'.
 *
 * Interactions are created and need to be deleted using release().
 *
 * \return The set of interaction values that are maximal and enabled by connector 'this'.
 */
void Connector::recomputeMaximalInteractions(vector<InteractionValue *> &maximalInteractions) const {
  // clear maximal interactions
  maximalInteractions.clear();

  // check dependencies
  assert(mMaximalInteractions.isDependentOf(mLocallyMaximalInteractions));

  // keeps only maximal interactions
  const vector<InteractionValue *> &locMaxInteractions = locallyMaximalInteractions();

  for (vector<InteractionValue *>::const_iterator interactionIt = locMaxInteractions.begin() ;
       interactionIt != locMaxInteractions.end() ;
       ++interactionIt) {
    InteractionValue &interaction = **interactionIt;

    if (!interaction.isDominatedByPriorities()) {
      maximalInteractions.push_back(&interaction);
    }
  }
}

/**
 * \brief Compute the set of locally maximal interaction values enabled at the current state.
 *
 * Requires up-to-date port values for all connected ports. Maximality is computed
 * based on maximal progress priority amongst the interactions enabled in the same
 * connector, i.e. in connector 'this'.
 *
 * Interactions are created and need to be deleted using release().
 *
 * \return The set of interaction values that are maximal and enabled by connector 'this'.
 */
void Connector::recomputeLocallyMaximalInteractions(vector<InteractionValue *> &locallyMaximalInteractions) const {
  // release allocated interactions
  release(locallyMaximalInteractions);

  // clear maximal interactions
  locallyMaximalInteractions.clear();

  // check dependencies
  assert(mLocallyMaximalInteractions.isDependentOf(mAllEnabledPorts));

  // force uptate of mAllEnabledPorts and copyOfmAllEnabledPorts (if needed)
  mAllEnabledPorts.recompute();

  // compute interactions maximal w.r.t. maximal progress
  enumerateLocallyMaximalInteractionValues(locallyMaximalInteractions, *copyOfmAllEnabledPorts, 0);
}

/**
 * \brief Compute the set of interaction values enabled at the current state.
 *
 * Requires up-to-date port values for all connected ports.
 * Interactions are created and need to be deleted using release().
 *
 * \return The set of interaction values enabled by connector 'this'.
 */
void Connector::recomputeEnabledInteractions(vector<InteractionValue *> &enabledInteractions) const {
  // release previously created interactions
  release(enabledInteractions);

  // clear enabled and maximal interactions
  enabledInteractions.clear();
    
  vector<PortValue *> partialValues;
  partialValues.reserve(ports().size());

  // check dependencies
  assert(mEnabledInteractions.isDependentOf(mAllEnabledPorts));

  for (vector<Interaction *>::const_iterator interactionIt = interactions().begin() ;
       interactionIt != interactions().end() ;
       ++interactionIt) {
    const Interaction &interaction = **interactionIt;

    if (interaction <= allEnabledInteraction()) {
      enumerateInteractionValues(enabledInteractions, interaction, partialValues, 0, false);
    }
  }
}


void Connector::computeInteractions(vector<Interaction *> &interactions) {
  vector<QuotedPortReference *> emptyInteraction;
  enumerateInteractions(interactions, emptyInteraction, 0);
}


/**
 * \brief Release all interactions of a list of interactions.
 *
 * Calls relaseInteraction for all interactions.
 *
 * \param interactions is a list of interactions to release.
 */
void Connector::release() const {
  //release(mInteractions);
  //release(mEnabledInteractions);
  //release(mLocallyMaximalInteractions);
}

/**
 * \brief Release all interactions of a list of interactions.
 *
 * Calls relaseInteraction for all interactions.
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
 * Calls relaseInteractionValue for all interaction values.
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


void Connector::computeDominatingPriorities(vector<Priority *> &dominatingPriorities) {
  const Compound &compound = holder();

  for (vector<Priority *>::const_iterator priorityIt = compound.priorities().begin() ;
       priorityIt != compound.priorities().end() ;
       ++priorityIt) {
    Priority &priority = **priorityIt;

    if (priority.hasLow()) {
      // should be a defined interaction of a top-level connector
      // assert(priority.low().isDefined());
      // assert(priority.low().connector().isTopLevel());

      if (&priority.low().connector() == this) {
        dominatingPriorities.push_back(&priority);
      }
    }
    else {
      assert(priority.hasHigh());
      if (&priority.high().connector() != this) {
        dominatingPriorities.push_back(&priority);
      }
    }
  }
}


void Connector::computeDominatedPriorities(vector<Priority *> &dominatedPriorities) {
  const Compound &compound = holder();

  for (vector<Priority *>::const_iterator priorityIt = compound.priorities().begin() ;
       priorityIt != compound.priorities().end() ;
       ++priorityIt) {
    Priority &priority = **priorityIt;

    if (priority.hasHigh()) {
      // should be a defined interaction of a top-level connector
      // assert(priority.high().isDefined() || !priority.high().hasPorts());
      // assert(priority.high().connector().isTopLevel());

      if (&priority.high().connector() == this) {
        dominatedPriorities.push_back(&priority);
      }
    }
    else {
      assert(priority.hasLow());

      if (&priority.low().connector() != this) {
        dominatedPriorities.push_back(&priority);
      }
    }
  }
}

void Connector::computeAllDominatingPriorities(vector<Priority *> &allDominatingPriorities) {
  vector<Priority *> remaining;

  // insert first level priority domination
  remaining.insert(remaining.end(),
                   dominatingPriorities().value().begin(),
                   dominatingPriorities().value().end());

  while (!remaining.empty()) {
    Priority &priority = *(remaining.back());
    remaining.pop_back();

    vector<Priority *>::const_iterator findIt = find(
      allDominatingPriorities.begin(),
      allDominatingPriorities.end(),
      &priority);

    if (findIt == allDominatingPriorities.end()) {
      allDominatingPriorities.push_back(&priority);

      remaining.insert(remaining.end(),
                       priority.dominatingPriorities().value().begin(),
                       priority.dominatingPriorities().value().end());
    }
  }
}

void Connector::computeAllDependentConnectors(vector<const Connector *> &allDependentConnectors) {
  for (vector<Priority *>::const_iterator priorityIt = allDominatingPriorities().begin() ;
       priorityIt != allDominatingPriorities().end() ;
       ++priorityIt) {
    const Priority &priority = **priorityIt;

    if (priority.hasHigh()) {
      // dependent connector due to priorities
      const Connector &dependentConnector = priority.high().connector();

      // check if the dependent connector is already there
      vector<const Connector *>::const_iterator findIt = find(
        allDependentConnectors.begin(),
        allDependentConnectors.end(),
        &dependentConnector);

      // add the dependent connector if not already there
      if (findIt == allDependentConnectors.end()) {
        allDependentConnectors.push_back(&dependentConnector);
      }
    }
    else {
      const Compound &compound = holder();

      for (map<string, Connector *>::const_iterator dependentConnectorIt = compound.connectors().begin() ;
           dependentConnectorIt != compound.connectors().end() ;
           ++dependentConnectorIt) {
        const Connector &dependentConnector = *dependentConnectorIt->second;

        if (this != &dependentConnector) {
          // check if the dependent connector is already there
          vector<const Connector *>::const_iterator findIt = find(
            allDependentConnectors.begin(),
            allDependentConnectors.end(),
            &dependentConnector);

          // add the dependent connector if not already there
          if (findIt == allDependentConnectors.end()) {
            allDependentConnectors.push_back(&dependentConnector);
          }
        }
      }
    }
  }
}

void Connector::addPort(QuotedPortReference &quotedPort) {
  // add the port to the connector ports
  mPorts.push_back(&quotedPort);
  quotedPort.setHolder(*this);
    
  // manage dependencies
  Port &port = quotedPort.port();

  // add dependencies to port values
  mAllEnabledPorts.dependsOn(port.reset());
}

void Connector::setExportedPort(ConnectorExportPort &exportedPort) {
  mExportedPort = &exportedPort;
  exportedPort.setHolder(*this);

  // manage dependencies
  exportedPort.reset().dependsOn(mEnabledInteractions);
  exportedPort.maximalPortValues().dependsOn(mMaximalInteractions);
}


/**
 * \brief Compute the set of interactions defined by the connector recursively.
 */
void Connector::enumerateInteractions(vector<Interaction *> &allInteractions, vector<QuotedPortReference *> &partialInteraction, unsigned int nextPortIndex) const {
  if (nextPortIndex < ports().size()) {
    QuotedPortReference *port = ports()[nextPortIndex];

    // all interactions that do     involve port
    partialInteraction.push_back(port);
    enumerateInteractions(allInteractions, partialInteraction, nextPortIndex + 1);

    // remove
    partialInteraction.pop_back();

    // all interactions that do not involve port
    enumerateInteractions(allInteractions, partialInteraction, nextPortIndex + 1);
  }
  else {
    vector<Port *> portsOfInteraction;

    bool maximal = partialInteraction.size() == ports().size();
    bool trigger = false;

    for (vector<QuotedPortReference *>::const_iterator portIt = partialInteraction.begin() ;
         portIt != partialInteraction.end() ;
         ++portIt) {
      QuotedPortReference *portRef = *portIt;

      if (portRef->trigger()) {
        trigger = true;
      }

      portsOfInteraction.push_back(&portRef->port());
    }

    // an interaction is maximal if a trigger is involved or if it is maximal
    if (trigger || maximal) {
      Interaction &interaction = createInteraction(portsOfInteraction);
      allInteractions.push_back(&interaction);
    }
  }
}


/**
 * \brief Compute the set of interaction values for the current state recursively.
 */
void Connector::enumerateInteractionValues(vector<InteractionValue *> &allInteractions, const Interaction &interaction, vector<PortValue *> &partialValues, unsigned int nextPortIndex, bool keepLocallyMaximalOnly) const {
  if (nextPortIndex < interaction.ports().size()) {
    const Port *port = interaction.ports()[nextPortIndex];

    if (port->hasPortValues()) {
      for (vector<PortValue *>::const_iterator valueIt = port->portValues().begin() ;
           valueIt != port->portValues().end() ;
           ++valueIt) {
        PortValue *value = *valueIt;

        // enumerate using value
        partialValues.push_back(value);
        enumerateInteractionValues(allInteractions, interaction, partialValues, nextPortIndex + 1, keepLocallyMaximalOnly);

        // remove value for next iteration (avoids using multiple vector<PortValue *>)
        // if (valueIt + 1 != port->portValues().end()) {
          partialValues.pop_back();
        // }
      }
    }
  }
  else {
    InteractionValue &interactionValue = createInteractionValue(interaction, partialValues);

    // check the guard of the build interaction value, if true, keep it
    bool keepIt = false;

    if (guard(interactionValue)) {
      keepIt = true;

      if (keepLocallyMaximalOnly) {
        vector<InteractionValue *>::iterator targetIt = allInteractions.begin();

        while (targetIt != allInteractions.end()) {
          InteractionValue &target = **targetIt;

          if (interactionValue < target) {
            keepIt = false;
            break;
          }
          else if (interactionValue > target) {
            // release the previously created interaction
            releaseInteractionValue(target);

            // remove it from the set of maximal interactions
            targetIt = allInteractions.erase(targetIt);
          }
          else {
            ++targetIt;
          }
        }
      }
    }

    if (keepIt) {
      allInteractions.push_back(&interactionValue);
    }
    else {
      // release the created interaction
      releaseInteractionValue(interactionValue);
    }
  }
}


void Connector::enumerateLocallyMaximalInteractionValues(vector<InteractionValue *> &allInteractions, Interaction &interaction, unsigned int mandatoryIndex) const {
  vector<PortValue *> partialValues;
  partialValues.reserve(ports().size());

  unsigned int oldSize = allInteractions.size();

  // if the interaction is defined, compute all enabled interaction values if exist
  if (interaction.isDefined()) {
    enumerateInteractionValues(allInteractions, interaction, partialValues, 0, true);
  }

  // if no interaction is found, check sub interactions
  if (allInteractions.size() == oldSize && interaction.hasSubDefined()) {
    unsigned int subMandatory =  mandatoryIndex;

    // try interactions immediatly dominated by maximal progress
    for (vector<Port *>::const_iterator portIt = interaction.ports().begin() + mandatoryIndex;
         portIt != interaction.ports().end() ;
         ++portIt) {
      Port &port = **portIt;

      // try sub-interaction without port
      interaction.removePort(port);

      // enumerate without port
      enumerateLocallyMaximalInteractionValues(allInteractions, interaction, subMandatory);
      // put back port in the subInteraction
      interaction.addPort(port);

      ++subMandatory;
    }
  }
}

void Connector::recomputeAllEnabledPorts(Interaction *&allEnabledPorts) const {
  if (allEnabledPorts == NULL) {
    allEnabledPorts = &createInteraction();
    copyOfmAllEnabledPorts = &createInteraction();
  }
  else {
    allEnabledPorts->recycle();
    copyOfmAllEnabledPorts->recycle();
  }

  for (vector<QuotedPortReference *>::const_iterator portRefIt = ports().begin() ;
       portRefIt != ports().end() ;
       ++portRefIt) {
    const QuotedPortReference &portRef = **portRefIt;
    Port &port = portRef.port();

    // check dependencies
    assert(mAllEnabledPorts.isDependentOf(port.reset()));

    // if port is enabled, add it to the interaction
    if (port.hasPortValues()) {
      allEnabledPorts->addPort(port);
      copyOfmAllEnabledPorts->addPort(port);
    }
  }
}

string Connector::fullName() const {
  return holder().fullName() + "." + name();
}

void Connector::initialize() {
  mDominatingPriorities.initialize();
  mDominatedPriorities.initialize();
  mIsTopLevel.initialize();
  mSubConnectors.initialize();

  for (vector<Connector *>::const_iterator subConnectorIt = subConnectors().begin() ;
       subConnectorIt != subConnectors().end() ;
       ++subConnectorIt) {
    Connector &subConnector = **subConnectorIt;

    subConnector.initialize();
    mAllSubConnectors.dependsOn(subConnector.mAllSubConnectors);
  }

  // initialize allSubConnectors
  mAllSubConnectors.initialize();

  // set dependencies between maximal interactions and active of priorities
  for (vector<Priority *>::const_iterator priorityIt = dominatingPriorities().value().begin() ;
       priorityIt != dominatingPriorities().value().end() ;
       ++priorityIt) {
    Priority &priority = **priorityIt;
    
    mMaximalInteractions.dependsOn(priority.active());
  }
}

void Connector::initializeAfterPriorities() {
  // transitive closure of priorities and dependencies
  // /!\ requires the initialization of priorities
  mAllDominatingPriorities.initialize();
  mAllDependentConnectors.initialize();
}
