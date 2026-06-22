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

#ifndef _BIP_Engine_AtomItf_HPP_
#define _BIP_Engine_AtomItf_HPP_

#include <bip-engineiface-config.hpp>
using namespace bipbasetypes;
using namespace biptypes;

// inherited classes
#include "ComponentItf.hpp"

// used classes
#include "AtomExportData.hpp"
#include "AtomExportPort.hpp"
#include "AtomInternalPort.hpp"
#include "Component.hpp"

// referenced classes
class BipError;
class PortValue;

class Component;

class AtomItf : public virtual ComponentItf {
 public:
  // destructor
  virtual ~AtomItf();

  // operations
  virtual BipError &initialize() = 0;
  virtual BipError &execute(PortValue &portValue) = 0;
  virtual string toString() const = 0;

  // getters for references
  const map<string, AtomInternalPort *> &internalPorts() const { return mInternalPorts; }
  bool hasInternalPorts() const { return !mInternalPorts.empty(); }
  const map<string, AtomExportPort *> &ports() const { return mPorts; }
  bool hasPorts() const { return !mPorts.empty(); }
  const map<string, AtomExportData *> &data() const { return mData; }
  bool hasData() const { return !mData.empty(); }

 protected:
  // protected constructors
  AtomItf(const string &name);

  // protected getters for references
  map<string, AtomInternalPort *> &internalPorts() { return mInternalPorts; }
  map<string, AtomExportPort *> &ports() { return mPorts; }
  map<string, AtomExportData *> &data() { return mData; }

  // protected setters for references
  virtual void addInternalPort(AtomInternalPort &internalPort) = 0;
  virtual void addPort(AtomExportPort &port) = 0;
  virtual void addData(AtomExportData &data) = 0;

  // references
  map<string, AtomInternalPort *> mInternalPorts;
  map<string, AtomExportPort *> mPorts;
  map<string, AtomExportData *> mData;

  // specific rights for deploying the system
  friend Component* deploy(int argc, char** argv);
};

#endif // _BIP_Engine_AtomItf_HPP_
