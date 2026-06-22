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

#include <Atom.hpp>
#include <Connector.hpp>
#include <AtomExportPort.hpp>
#include <CompoundExportPort.hpp>
#include <PortValue.hpp>
#include <Compound.hpp>
#include <BipError.hpp>

// constructors
CompoundExportPort::CompoundExportPort(const string &name) :
  PortItf(name, COMPOUND_EXPORT),
  Port(name, COMPOUND_EXPORT),
  CompoundExportPortItf(name),
  mPortValues(this, &CompoundExportPort::recomputePortValues) {
  /* implement your constructor here */
}

// destructor
CompoundExportPort::~CompoundExportPort() {
  /* implement your destructor here */
}

/* \brief Execute a port value.
 *
 * \param portValue is the target port value, it should a port
 * value exported by 'this'.
 *
 * \return An error if found during the execution of involved atoms or
 * during the update of port values, BipError::NoError otherwise.
 */
BipError &CompoundExportPort::execute(PortValue& portValue) {
  // must be a port value of 'this'
  assert(portValue.hasPort());

  // execute the correspondint "internal" port
  Port &internalPort = portValue.port();

  return internalPort.execute(portValue);
}


/**
 * \brief Compute the port values exported by the port.
 *
 * Requires that port values of "internal" ports exported
 * through 'this' are up-to-date.
 * Port values exported by 'this' are the union of the port
 * values of these internal ports, accessed by portValues().
 */
void CompoundExportPort::recomputePortValues(vector<PortValue *> &portValues) const {
  // purge existing references to ports values
  portValues.clear();    
  
  // map port values of forwarded ports
  for (vector<Port *>::const_iterator forwardIt = forwardPorts().begin() ;
       forwardIt != forwardPorts().end() ;
       ++forwardIt) {
    Port &forwardPort = **forwardIt;
    
    // consider port values for atom export ports andcompound export ports
    if (forwardPort.type() == ATOM_EXPORT ||
        forwardPort.type() == COMPOUND_EXPORT) {
      // check dependencies
      assert(mPortValues.isDependentOf(forwardPort.reset()));

      const vector<PortValue *> &forwardPortValues = forwardPort.portValues();

      // export the port values of the forward port
      portValues.insert(portValues.end(),
                        forwardPortValues.begin(),
                        forwardPortValues.end());

      // map port values to port
      if (forwardPort.type() == ATOM_EXPORT) {
        for (vector<PortValue *>::const_iterator valueIt = forwardPortValues.begin() ;
             valueIt != forwardPortValues.end() ;
             ++valueIt) {
          PortValue &portValue = **valueIt;
      
          portValue.setPort(forwardPort);
	    }
      }
    }
    else if (forwardPort.type() == CONNECTOR_EXPORT) {
      ConnectorExportPort &connectorPort = dynamic_cast<ConnectorExportPort &>(forwardPort);

      // check dependencies
      assert(mPortValues.isDependentOf(connectorPort.maximalPortValues()));
      
      const vector<PortValue *> &forwardPortValues = connectorPort.maximalPortValues();

      // export the port values of the forward port
      portValues.insert(portValues.end(),
                        forwardPortValues.begin(),
                        forwardPortValues.end());

      // map port values to port
      for (vector<PortValue *>::const_iterator valueIt = forwardPortValues.begin() ;
           valueIt != forwardPortValues.end() ;
           ++valueIt) {
        PortValue &portValue = **valueIt;
      
        portValue.setPort(forwardPort);
      }
    }
    else {
      // not a valid type
      assert(false);
    }
  }
}


/**
 * \brief Check if a port value belongs to exported port values.
 *
 * Check if a port value is exported by 'this', that is, if it is in the set
 * of exported port values given portValues().
 *
 * \param portValue The target port value to check.
 *
 * \return true if portValue is in portValues().
 */
bool CompoundExportPort::hasPortValue(PortValue& portValue) const {
  vector<PortValue *>::const_iterator findIt = find(
    portValues().begin(),
    portValues().end(),
    &portValue);

  return findIt != portValues().end();
}

void CompoundExportPort::addForwardPort(Port &forwardPort) {
  // standard addForwardPort() of the interface
  CompoundExportPortItf::addForwardPort(forwardPort);

  // manage dependencies
  if (forwardPort.type() == ATOM_EXPORT ||
      forwardPort.type() == COMPOUND_EXPORT) {
    mPortValues.dependsOn(forwardPort.reset());
  }
  else if (forwardPort.type() == CONNECTOR_EXPORT) {
    ConnectorExportPort &connectorPort = dynamic_cast<ConnectorExportPort &>(forwardPort);
    mPortValues.dependsOn(connectorPort.maximalPortValues());
  }
  else {
    assert(false);
  }
}
