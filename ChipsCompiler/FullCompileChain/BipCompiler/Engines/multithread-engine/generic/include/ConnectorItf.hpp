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

#ifndef _BIP_Engine_ConnectorItf_HPP_
#define _BIP_Engine_ConnectorItf_HPP_

#include <bip-engineiface-config.hpp>
using namespace bipbasetypes;
using namespace biptypes;

// used classes
#include "ConnectorExportPort.hpp"

// referenced classes
class Compound;
class Interaction;
class InteractionValue;
class Port;
class PortValue;
class QuotedPortReference;

class Component;

class ConnectorItf {
 public:
  // destructor
  virtual ~ConnectorItf();

  // operations
  virtual PortValue &up(const InteractionValue &interaction) const = 0;
  virtual void down(InteractionValue &interaction, PortValue &portValue) const = 0;
  virtual Interaction &createInteraction() const = 0;
  virtual Interaction &createInteraction(const vector<Port *> &ports) const = 0;
  virtual InteractionValue &createInteractionValue(const Interaction &interaction, const vector<PortValue *> &values) const = 0;
  virtual void down(InteractionValue &interaction) const = 0;
  virtual bool guard(const InteractionValue &interaction) const = 0;
  virtual void releaseInteraction(Interaction &interaction) const = 0;
  virtual void releaseInteractionValue(InteractionValue &interactionValue) const = 0;
  virtual const vector<Interaction *> &interactions() const = 0;
  virtual bool canUpOnlyMaximalInteractions() const = 0;

  // getters for references
  const vector<QuotedPortReference *> &ports() const { return mPorts; }
  bool hasPorts() const { return !mPorts.empty(); }
  ConnectorExportPort &exportedPort() const { return *mExportedPort; }
  bool hasExportedPort() const { return mExportedPort != NULL; }

  // getters for attributes
  const string &name() const { return mName; }

  // opposites accessors
  Compound &holder() const { return *mHolder; }
  bool hasHolder() const { return mHolder != NULL; }
  void setHolder(Compound &compound) { mHolder = &compound; }

 protected:
  // protected constructors
  ConnectorItf(const string &name);

  // protected getters for references
  vector<QuotedPortReference *> &ports() { return mPorts; }
  ConnectorExportPort &exportedPort() { return *mExportedPort; }

  // protected setters for references
  virtual void addPort(QuotedPortReference &port) = 0;
  virtual void setExportedPort(ConnectorExportPort &exportedPort) = 0;

  // attributes
  const string mName;

  // references
  vector<QuotedPortReference *> mPorts;
  ConnectorExportPort *mExportedPort;

  // opposites
  Compound *mHolder;

  // specific rights for deploying the system
  friend Component* deploy(int argc, char** argv);
};

#endif // _BIP_Engine_ConnectorItf_HPP_
