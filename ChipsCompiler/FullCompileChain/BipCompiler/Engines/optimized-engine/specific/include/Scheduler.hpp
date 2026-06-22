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

#ifndef _BIP_Engine_Scheduler_HPP_
#define _BIP_Engine_Scheduler_HPP_

class Engine;
class BipError;

/** \brief Compute a sequence of interactions.
 *
 * A scheduler implements a specific scheduling policy, e.g.
 * random, interactive, exhaustive, etc.
 */
class Scheduler {
 public:
  Scheduler(Engine &engine);
  virtual ~Scheduler();

  /** \brief Initialize the scheduler
   */
  virtual BipError &initialize() = 0;

  /** \brief Implements the behavior of the scheduler.
   */
  virtual BipError &run() = 0;

  /** \return Engine which is used by the scheduler.
   */
  const Engine& engine() const { return mEngine; }

 protected:

  /** \return Engine which is used by the scheduler.
   */
  Engine& engine() { return mEngine; }

  /** \brief Engine which is used by the scheduler for computing
   * interactions at a given state.
   */
  Engine &mEngine;
};

#endif // _BIP_Engine_Scheduler_HPP_
