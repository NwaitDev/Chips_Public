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

#ifndef _BIP_Engine_CompoundExportPort_HPP_
#define _BIP_Engine_CompoundExportPort_HPP_

// inherited classes
#include <CompoundExportPortItf.hpp>
#include "Port.hpp"
#include "PortValue.hpp"

class BipError;

class CompoundExportPort : public virtual PortItf, public virtual Port, public CompoundExportPortItf {
 public:
  // constructors
  CompoundExportPort(const string &name);

  // destructor
  virtual ~CompoundExportPort();

  // operations
  virtual const vector<PortValue *> &portValues() const { return mPortValues; }
  virtual bool hasPortValues() const { return !portValues().empty(); }

  // specific
  virtual BipError &execute(PortValue& portValue);
  bool hasPortValue(PortValue& portValue) const;
  virtual ResetableItf &reset() { return mPortValues; }

 protected:
  void addForwardPort(Port &forwardPort);
  
  
  void recomputePortValues(vector<PortValue *> &portValues) const;

  /**
   * \brief Associate a port to a port value.
   */
  void mapPortValue(PortValue &portValue, Port &port) {
    // if it's a final destination, map it!
    if (port.type() == ATOM_EXPORT ||
        port.type() == CONNECTOR_EXPORT) {
      portValue.setPort(port);
    }
  }
  
  mutable Resetable<vector<PortValue *>, CompoundExportPort> mPortValues;

  // specific rights for deploying the system
  friend Component* deploy(int argc, char** argv);
};

#endif // _BIP_Engine_CompoundExportPort_HPP_
