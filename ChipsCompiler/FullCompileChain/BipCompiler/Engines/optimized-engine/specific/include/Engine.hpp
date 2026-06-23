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

#ifndef _BIP_Engine_Engine_HPP_
#define _BIP_Engine_Engine_HPP_

#include <Compound.hpp>
#include <State.hpp>

#include <bip-engineiface-config.hpp>

class InteractionValue;
class AtomInternalPort;
class AtomExternalPort;
class BipError;

/** \brief Provides the basic interface for executing a model.
 *
 * It can initialize the system, execute an interaction or an internal port,
 * and compute the set of interactions and internal ports enabled at the
 * current state of the system.
 */
class Engine {
 public:
  Engine(Compound &top);
  virtual ~Engine();

  inline const Compound& top() const { return mTop; }

  /** 
   * \brief Initialize the engine.
   *
   * This step should include the initialization of the components
   * which includes calls to initialize() methods of atoms and
   * update of the port values of all ports of the system.
   */
  virtual BipError &initialize() = 0;

  /** 
   * \brief Execute an interaction.
   *
   * The chosen interaction should be enabled at the current state of mTop,
   * i.e. should be in the set returned by interactions().
   *
   * \param interaction The chosen interaction.
   */
  virtual BipError &execute(InteractionValue& interaction) = 0;

  /** 
   * \brief Execute a internal port.
   *
   * This internal port should be enabled at the current state of mTop,
   * i.e. should be in the set returned by internals().
   *
   * \param internal The chosen atom internal port.
   */
  virtual BipError &execute(AtomInternalPort& internal) = 0;

  /** 
   * \brief Execute an external port.
   *
   * This external port should be waiting for an event a the current
   * state of mTop (should be in the set returned by externals()), and
   * it should have an event.
   *
   * \param external The chosen atom external port.
   */
  virtual BipError &execute(AtomExternalPort& external) = 0;

  virtual BipError &checkExternals() = 0;

  /** 
   * \brief Returns the set of interactions enabled at current state.
   */
  virtual const vector<InteractionValue *> &interactions() const = 0;

  /** 
   * \brief Returns the set of internal ports enabled at current state.
   */
  virtual const vector<AtomInternalPort *> &internals() const = 0;

  /** 
   * \brief Returns the set of external ports enabled at current state.
   */
  virtual const vector<AtomExternalPort *> &externals() const = 0;

  /** 
   * \brief Returns the set of external ports waiting at current state.
   */
  virtual const vector<AtomExternalPort *> &waiting() const = 0;

  /** 
   * \brief Returns the current state of the model.
   */
  virtual State getState() const = 0;

  /** 
   * \brief Set the current state of the model.
   */
  virtual void setState(const State &state) = 0;

  static const int SIGBIP;

 protected:
  inline Compound& top() { return mTop; }

  Compound &mTop;
};

#endif // _BIP_Engine_Engine_HPP_
