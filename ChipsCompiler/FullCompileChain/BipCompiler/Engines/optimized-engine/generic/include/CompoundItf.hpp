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

#ifndef _BIP_Engine_CompoundItf_HPP_
#define _BIP_Engine_CompoundItf_HPP_

#include <bip-engineiface-config.hpp>
using namespace bipbasetypes;
using namespace biptypes;

// inherited classes
#include "ComponentItf.hpp"

// used classes
#include "Component.hpp"
#include "CompoundExportData.hpp"
#include "CompoundExportPort.hpp"
#include "Connector.hpp"
#include "Priority.hpp"

class Component;

class CompoundItf : public virtual ComponentItf {
 public:
  // destructor
  virtual ~CompoundItf();

  // getters for references
  const map<string, Component *> &components() const { return mComponents; }
  bool hasComponents() const { return !mComponents.empty(); }
  const map<string, CompoundExportPort *> &ports() const { return mPorts; }
  bool hasPorts() const { return !mPorts.empty(); }
  const vector<Priority *> &priorities() const { return mPriorities; }
  bool hasPriorities() const { return !mPriorities.empty(); }
  const map<string, Connector *> &connectors() const { return mConnectors; }
  bool hasConnectors() const { return !mConnectors.empty(); }
  const map<string, CompoundExportData *> &data() const { return mData; }
  bool hasData() const { return !mData.empty(); }

 protected:
  // protected constructors
  CompoundItf(const string &name);

  // protected getters for references
  map<string, Component *> &components() { return mComponents; }
  map<string, CompoundExportPort *> &ports() { return mPorts; }
  vector<Priority *> &priorities() { return mPriorities; }
  map<string, Connector *> &connectors() { return mConnectors; }
  map<string, CompoundExportData *> &data() { return mData; }

  // protected setters for references
  virtual void addComponent(Component &component) = 0;
  virtual void addPort(CompoundExportPort &port) = 0;
  virtual void addPriority(Priority &priority) = 0;
  virtual void addConnector(Connector &connector) = 0;
  virtual void addData(CompoundExportData &data) = 0;

  // references
  map<string, Component *> mComponents;
  map<string, CompoundExportPort *> mPorts;
  vector<Priority *> mPriorities;
  map<string, Connector *> mConnectors;
  map<string, CompoundExportData *> mData;

  // specific rights for deploying the system
  friend Component* deploy(int argc, char** argv);
};

#endif // _BIP_Engine_CompoundItf_HPP_
