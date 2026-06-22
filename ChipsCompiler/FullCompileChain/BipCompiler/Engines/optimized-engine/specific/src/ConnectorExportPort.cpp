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

#include <ConnectorExportPort.hpp>
#include <Connector.hpp>
#include <PortValue.hpp>
#include <InteractionValue.hpp>
#include <BipError.hpp>
#include <PortValue.hpp>

// constructors
ConnectorExportPort::ConnectorExportPort(const string &name) :
  PortItf(name, CONNECTOR_EXPORT),
  Port(name, CONNECTOR_EXPORT),
  ConnectorExportPortItf(name),
  mPortValues(this, &ConnectorExportPort::recomputePortValues),
  mMaximalPortValues(this, &ConnectorExportPort::recomputeMaximalPortValues) {
  /* implement your constructor here */
}

// destructor
ConnectorExportPort::~ConnectorExportPort() {
}


/**
 * \brief Execute the interaction corresponding to a port value.
 *
 * The execution of an interaction is performed by method
 * execute() of the corresponding interaction which executes
 * all the components and connectors involved in the interaction.
 *
 * \param portValue The port value that parameters the execution.
 */
BipError &ConnectorExportPort::execute(PortValue &portValue) {
  // should be mapped to an interaction
  assert(portValue.hasInteraction());

  // get the interaction
  //InteractionValue &interaction = *mappedPortValues()[&portValue];
  InteractionValue &interaction = portValue.interaction();

  // same holding connector
  assert(&interaction.connector() == &holder());

  // should be an enabled interaction
  assert(interaction.isEnabled());

  // down
  holder().down(interaction, portValue);

  // execute
  return interaction.execute();
}


/**
 * \brief Compute the port values and the maximal port values
 * exported by the port.
 *
 * Requires that port values of the ports connected by
 * the connector holder are up-to-date.
 *
 * Port values exported by 'this' correspond to the application
 * of up() method of the connector holder, for all interactions
 * enabled by the connector holder, which are the interactions
 * returned by interaction() in the connector holder.
 * The computed port values can be accessed using portValues().
 *
 * Maximal port values exported by the port correspond to
 * port values of maximal interactions.
 * The computed maximal port values can be accessed using
 * maximalPortValues().
 */
void ConnectorExportPort::recomputePortValues(vector<PortValue *> &portValues) const {
  // purge existing references to ports values and maximal port values
  portValues.clear();
  
  Connector &connector = holder();

  // get enabled interactions
  const vector<InteractionValue *> &enabledInteractions = connector.enabledInteractions();
  
  // add one port value for each interaction
  for (vector<InteractionValue *>::const_iterator interactionIt = enabledInteractions.begin() ;
       interactionIt != enabledInteractions.end() ;
       ++interactionIt) {
    InteractionValue &interaction = **interactionIt;
    
    // do the up of the connector
    PortValue &portValue = connector.up(interaction);
    
    // add port value
    portValues.push_back(&portValue);
    
    // map port value to the interaction
    portValue.setInteraction(interaction);
  }
}

void ConnectorExportPort::recomputeMaximalPortValues(vector<PortValue *> &portValues) const {
  // purge existing references to ports values and maximal port values
  portValues.clear();
  
  Connector &connector = holder();
  
  // add one port value for each interaction
  const vector<InteractionValue *> &maximalInteractions = connector.maximalInteractions();

  for (vector<InteractionValue *>::const_iterator interactionIt = maximalInteractions.begin() ;
       interactionIt != maximalInteractions.end() ;
       ++interactionIt) {
    InteractionValue &interaction = **interactionIt;
    
    // do the up of the connector
    PortValue &portValue = connector.up(interaction);
    
    portValues.push_back(&portValue);
    
    // map port value to the interaction
    portValue.setInteraction(interaction);
  }
}
