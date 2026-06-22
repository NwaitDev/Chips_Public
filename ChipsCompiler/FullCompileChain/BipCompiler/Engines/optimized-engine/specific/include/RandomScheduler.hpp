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

#ifndef _BIP_Engine_RandomScheduler_HPP_
#define _BIP_Engine_RandomScheduler_HPP_

#include "Scheduler.hpp"
#include "StringTree.hpp"

class Engine;
class Logger;
class BipError;
class Atom;
class Component;
class Connector;
class Compound;
class InteractionValue;
class ConnectorExportPort;
class CompoundExportPort;
class AtomInternalPort;
class AtomExportPort;

/** \brief Compute execution sequences in which interactions
 * are chosen randomly.
 */
class RandomScheduler : public Scheduler {
 public:
  RandomScheduler(Engine &engine, Logger &logger, bool debug = false, bool interactive = false, bool randomSeed = true, unsigned int seed = 0);
  virtual ~RandomScheduler();

  virtual BipError &initialize();
  virtual BipError &run();

  bool debug() const { return mDebug; }
  bool interactive() const { return mInteractive; }
  bool randomSeed() const { return mRandomSeed; }
  unsigned int seed() const { return mSeed; }

  static void notify();


 protected:
  bool deadlock() const;
  void waitForNotifications();
  static pid_t pid;
  static volatile unsigned int nbNotifications;
  static void handleSignals(int signum);
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

  bool newNotifications() { return mNbTreatedNotifications != nbNotifications; }
  void updateTreatedNotifications() { mNbTreatedNotifications = nbNotifications; }

  bool checkIsSerializeEnabled();
  string parse(const string &cmdline, size_t &index);

  Logger &logger() const { return mLogger; }

  Logger &mLogger;
  bool mDebug;
  bool mInteractive;
  bool mRandomSeed;
  unsigned int mSeed;

  unsigned int mNbTreatedNotifications;
};

#endif // _BIP_Engine_RandomScheduler_HPP_
