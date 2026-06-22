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

#include <Atom.hpp>
#include <Connector.hpp>
#include <AtomExportPort.hpp>
#include <CompoundExportPort.hpp>
#include <ConnectorExportPort.hpp>
#include <PortValue.hpp>
#include <Compound.hpp>
#include <BipError.hpp>

// constructors
CompoundExportPort::CompoundExportPort(const string &name) :
  PortItf(name, COMPOUND_EXPORT),
  Port(name, COMPOUND_EXPORT),
  CompoundExportPortItf(name) {
  /* implement your constructor here */
}

// destructor
CompoundExportPort::~CompoundExportPort() {
  /* implement your destructor here */
}

/* \brief Execute a port value.
 *
 * \param portValue is the target port value, it must a port
 * value exported by 'this'.
 *
 * \return An error if found during the execution of involved atoms or
 * during the update of port values, BipError::NoError otherwise.
 */
BipError &CompoundExportPort::execute(PortValue& portValue) {
  map<PortValue *, Port *>::const_iterator portIt = mappedPortValues().find(&portValue);

  // must be a port value of 'this'
  assert(portIt != mappedPortValues().end());

  // execute the correspondint "internal" port
  Port &internalPort = *portIt->second;

  // for components, call their execute() method
  if (internalPort.type() == ATOM_EXPORT) {
    AtomExportPort &atomPort = dynamic_cast<AtomExportPort &>(internalPort);
    BipError &error = atomPort.holder().execute(portValue);

    if (error.type() != NO_ERROR) {
      return error;
    }
  }
  else if (internalPort.type() == COMPOUND_EXPORT) {
    CompoundExportPort &compoundPort = dynamic_cast<CompoundExportPort &>(internalPort);
    BipError &error = compoundPort.holder().execute(portValue);

    if (error.type() != NO_ERROR) {
      return error;
    }
  }
  else if (internalPort.type() == CONNECTOR_EXPORT) {
    ConnectorExportPort &connectorPort = dynamic_cast<ConnectorExportPort &>(internalPort);
    BipError &error = connectorPort.execute(portValue);

    if (error.type() != NO_ERROR) {
      return error;
    }
  }
  else {
    // not a valid type
    assert(false);
  }

  return BipError::NoError;
}


/**
 * \brief Compute the port values exported by the port.
 *
 * Require that port values of "internal" ports exported
 * through 'this' are up-to-date.
 * Port values exported by 'this' are the union of the port
 * values of these internal ports, accessed by portValues().
 */
void CompoundExportPort::updatePortValues() {
  // purge mapping between port values and port
  clearMappedPortValues();

  // purge existing references to ports values
  clearPortValues();

  // map port values of forwarded ports
  for (vector<Port *>::const_iterator forwardIt = forwardPorts().begin() ;
       forwardIt != forwardPorts().end() ;
       ++forwardIt) {
    Port &forwardPort = **forwardIt;

    // target port values to add
    const vector<PortValue *> *portValues = NULL;

    // consider port values for atom export ports and compound export ports
    if (forwardPort.type() == ATOM_EXPORT ||
        forwardPort.type() == COMPOUND_EXPORT) {
      portValues = &forwardPort.portValues();
    }
    else if (forwardPort.type() == CONNECTOR_EXPORT) {
      ConnectorExportPort &connectorPort = dynamic_cast<ConnectorExportPort &>(forwardPort);

      // keep only maximal port values, according to the semantics
      portValues = &connectorPort.maximalPortValues();
    }
    else {
      // not a valid type
      assert(false);
    }

    // add corresponding port values
    for (vector<PortValue *>::const_iterator valueIt = portValues->begin() ;
         valueIt != portValues->end() ;
         ++valueIt) {
      PortValue &portValue = **valueIt;

      // add port value to exported port
      addPortValue(portValue);

      // map port value to the "internal" port
      mapPortValue(portValue, forwardPort);
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
