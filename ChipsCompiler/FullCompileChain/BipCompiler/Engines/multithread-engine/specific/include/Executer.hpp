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

#ifndef _BIP_Engine_Executer_HPP_
#define _BIP_Engine_Executer_HPP_

#include "StringTree.hpp"
#include "ReadyQueue.hpp"
#include "Resource.hpp"

class BipError;
class Atom;
class Component;
class Connector;
class Compound;
class Port;
class InteractionValue;
class ConnectorExportPort;
class CompoundExportPort;
class AtomInternalPort;
class AtomExportPort;
class Logger;
class Thread;
class Job;

/** \brief Compute execution sequences in which interactions
 * are chosen randomly.
 */
class Executer {
 public:
  Executer(Compound &top, Logger &logger, unsigned int nbThreads, bool randomSeed = true, unsigned int seed = 0);
  virtual ~Executer();

  BipError &initialize();
  BipError &run();
  bool debug() const { return mDebug; }
  bool interactive() const { return mInteractive; }
  bool randomSeed() const { return mRandomSeed; }
  unsigned int seed() const { return mSeed; }
  unsigned int limit() const { return mLimit; }

  static ReadyQueue<Job> jobs;

 protected:
  void initializeReserver(const Compound &compound);
  void initializeThreads();
  void startThreads();
  void stopThreads();
  void print();
  StringTree print(const ConnectorExportPort &port);
  StringTree print(const CompoundExportPort &port);
  StringTree print(const AtomInternalPort &port);
  StringTree print(const AtomExportPort &port);
  StringTree print(const InteractionValue &port);
  StringTree print(const Connector &connector);
  StringTree print(const Atom &atom);
  StringTree print(const Compound &compound);
  StringTree print(const Component &component);

  Logger &logger() { return mLogger; }

  /** \return Root component.
   */
  Compound& top() { return mTop; }

  Compound &mTop;

  Logger &mLogger;
  bool mDebug;
  bool mInteractive;
  unsigned int mNbThreads;
  bool mRandomSeed;
  unsigned int mSeed;
  unsigned int mLimit;

  vector<Thread *> mThreads;
  Resource::Reserver mReserver;
};

#endif // _BIP_Engine_Executer_HPP_
