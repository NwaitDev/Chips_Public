/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
 *  Jacques Combaz (jacques.combaz@univ-grenoble-alpes.fr)
 *  Marc Pouhliès
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

#ifndef _BIP_Engine_ReferenceEngine_HPP_
#define _BIP_Engine_ReferenceEngine_HPP_

#include "Engine.hpp"
#include "Compound.hpp"

#include <bip-engineiface-config.hpp>

class InteractionValue;
class AtomInternalPort;
class AtomExternalPort;
class BipError;

/** \brief Direct implementation of the BIP semantics, without any
 * optimization.
 *
 * It can be used as a reference for testing other engines, or as a
 * starting point for understanding the BIP semantics.
 */
class ReferenceEngine : public Engine {
 public:
  ReferenceEngine(Compound &top);
  ReferenceEngine(Compound &top, bool disableFairness);
  virtual ~ReferenceEngine();

  virtual BipError& initialize();
  virtual BipError& execute(InteractionValue &interaction);
  virtual BipError& execute(AtomInternalPort &internal);
  virtual BipError& execute(AtomExternalPort &external);
  virtual BipError& checkExternals();
  virtual const vector<InteractionValue *> &interactions() const { return mInteractions; }
  virtual const vector<AtomInternalPort *> &internals() const { return mInternals; }
  virtual const vector<AtomExternalPort *> &externals() const { return mExternals; }
  virtual const vector<AtomExternalPort *> &waiting() const { return mWaiting; }

  virtual State getState() const;
  virtual void setState(const State &state);

  bool disableFairness() const { return mDisableFairness; }


 protected:
  /**
   * \brief Update interactions and internals w.r.t. to the current 
   * state of the system.
   */
  BipError &update();

  BipError &checkUnexpected(AtomExternalPort &port);

  /**
   * \brief Returns the set of interactions enabled at the current state.
   */
  vector<InteractionValue *> &interactions() { return mInteractions; }
  /**
   * \brief Returns the set of internal ports enabled at the current state.
   */
  vector<AtomInternalPort *> &internals() { return mInternals; }

  /**
   * \brief Returns the set of exernal ports enabled at the current state.
   */
  vector<AtomExternalPort *> &externals() { return mExternals; }

  /**
   * \brief Returns the set of exernal ports waiting at the current state.
   */
  vector<AtomExternalPort *> &waiting() { return mWaiting; }

  /**
   * \brief Returns the set of exernal ports with unexpected events at the current state.
   */
  vector<AtomExternalPort *> &unexpected() { return mUnexpected; }

  /**
   * \brief Set of internal ports enabled at the current state.
   */
  vector<InteractionValue *> mInteractions;

  /**
   * \brief Set of internal ports enabled at the current state.
   */
  vector<AtomInternalPort *> mInternals;

  /**
   * \brief Set of external ports enabled at the current state.
   */
  vector<AtomExternalPort *> mExternals;

  /**
   * \brief Set of external ports waiting at the current state.
   */
  vector<AtomExternalPort *> mWaiting;

  /**
   * \brief Set of external ports which are not enabled nor waiting.
   */
  vector<AtomExternalPort *> mUnexpected;


  bool mDisableFairness;
};

#endif // _BIP_Engine_ReferenceEngine_HPP_
