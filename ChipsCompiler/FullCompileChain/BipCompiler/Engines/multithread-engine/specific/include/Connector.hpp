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

#ifndef _BIP_Engine_Connector_HPP_
#define _BIP_Engine_Connector_HPP_

// inherited classes
#include <ConnectorItf.hpp>
#include "ConnectorExportPort.hpp"
#include "QuotedPortReference.hpp"

#include "Initializable.hpp"
#include "Resetable.hpp"
#include "ExecuteConnectorJob.hpp"

class Connector : public ConnectorItf {
 public:
  // constructors
  Connector(const string &name);

  // destructor
  virtual ~Connector();

  // operations
  virtual const vector<Interaction *> &interactions() const { return mInteractions.value(); }

  // specific
  bool isTopLevel() const { return mIsTopLevel.value(); }
  const vector<Connector *> &subConnectors() const { return mSubConnectors.value(); }
  const vector<Connector *> &allSubConnectors() const { return mAllSubConnectors.value(); }
  
  Resetable<Interaction *, Connector> &allEnabledPorts() const { return mAllEnabledPorts; }
  Resetable<vector<InteractionValue *>, Connector> &enabledInteractions() const { return mEnabledInteractions; }
  Resetable<vector<InteractionValue *>, Connector> &maximalInteractions() const { return mMaximalInteractions; }
  Resetable<vector<InteractionValue *>, Connector> &locallyMaximalInteractions() const  { return mLocallyMaximalInteractions; }
    
  void release() const;
  void release(const vector<Interaction *> &interactions) const;
  void release(const vector<InteractionValue *> &interactions) const;

  Initializable<vector<Priority *>, Connector> &dominatingPriorities() const { return mDominatingPriorities; }
  Initializable<vector<Priority *>, Connector> &dominatedPriorities() const { return mDominatedPriorities; }
  
  string fullName() const;

  const vector<Priority *> &allDominatingPriorities() const { return mAllDominatingPriorities.value(); }
  const vector<const Connector *> &allDependentConnectors() const { return mAllDependentConnectors.value(); }

  void initialize();
  void initializeAfterPriorities();

  ExecuteConnectorJob &executeJob() { return mExecuteJob; }

 protected:
  // update methods resetable objects
  void recomputeAllEnabledPorts(Interaction *&allEnabledPorts) const;
  void recomputeEnabledInteractions(vector<InteractionValue *> &enabledInteractions) const;
  void recomputeMaximalInteractions(vector<InteractionValue *> &maximalInteractions) const;
  void recomputeLocallyMaximalInteractions(vector<InteractionValue *> &locallyMaximalInteractions) const;

  // initialization methods for initializable objects
  void computeInteractions(vector<Interaction *> &interactions);
  void computeDominatingPriorities(vector<Priority *> &dominatingPriorities);
  void computeDominatedPriorities(vector<Priority *> &dominatedPriorities);
  void computeIsTopLevel(bool &isTopLevel);
  void computeSubConnectors(vector<Connector *> &subConnectors);
  void computeAllSubConnectors(vector<Connector *> &allSubConnectors);
  void computeAllDominatingPriorities(vector<Priority *> &allSubConnectors);
  void computeAllDependentConnectors(vector<const Connector *> &allSubConnectors);

  // protected setters for references
  void addPort(QuotedPortReference &quotedPort);
  void setExportedPort(ConnectorExportPort &exportedPort);

  // specific
  void enumerateInteractions(vector<Interaction *> &allInteractions, vector<QuotedPortReference *> &partialInteraction, unsigned int nextPortIndex) const;
  void enumerateInteractionValues(vector<InteractionValue *> &allInteractions, const Interaction &interaction, vector<PortValue *> &partialValues, unsigned int nextPortIndex, bool keepLocallyMaximalOnly) const;
  void enumerateLocallyMaximalInteractionValues(vector<InteractionValue *> &allInteractions, Interaction &interaction, unsigned int mandatoryIndex) const;
  const Interaction &allEnabledInteraction() const { return *(Interaction *) mAllEnabledPorts; }

  void computeIsTopLevel() const;

  bool mInitializedDependentConnectors;
  vector<Connector *> mDependentConnectors;

  bool mInitializedDependentPriorities;
  vector<Priority *> mDependentPriorities;

  mutable Resetable<Interaction *, Connector> mAllEnabledPorts;
  mutable Interaction *copyOfmAllEnabledPorts; // copy for thread-safety

  mutable Initializable<vector<Interaction *>, Connector> mInteractions;

  mutable Resetable<vector<InteractionValue *>, Connector> mEnabledInteractions;
  mutable Resetable<vector<InteractionValue *>, Connector> mMaximalInteractions;
  mutable Resetable<vector<InteractionValue *>, Connector> mLocallyMaximalInteractions;

  mutable Initializable<vector<Priority *>, Connector> mDominatingPriorities;
  mutable Initializable<vector<Priority *>, Connector> mDominatedPriorities;
  mutable Initializable<bool, Connector> mIsTopLevel;
  mutable Initializable<vector<Connector *>, Connector> mSubConnectors;
  mutable Initializable<vector<Connector *>, Connector> mAllSubConnectors;
  mutable Initializable<vector<Priority *>, Connector> mAllDominatingPriorities;
  mutable Initializable<vector<const Connector *>, Connector> mAllDependentConnectors;
  
  ExecuteConnectorJob mExecuteJob;
};

#endif // _BIP_Engine_Connector_HPP_
