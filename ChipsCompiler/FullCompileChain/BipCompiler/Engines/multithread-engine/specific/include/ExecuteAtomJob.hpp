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

#ifndef _BIP_Engine_ExecuteAtomJob_HPP_
#define _BIP_Engine_ExecuteAtomJob_HPP_

// inherited classes
#include <Job.hpp>
#include <BipError.hpp>
#include "PortValue.hpp"
#include "AtomInternalPort.hpp"
#include "ReadyQueue.hpp"
#include "Resource.hpp"

class Atom;
class PortValue;
class BipError;
class Logger;
class ExecuteConnectorJob;
class AtomInternalPort;
class AtomExternalPort;

class ExecuteAtomJob : public Job {
 public:
  // constructors
  ExecuteAtomJob(Atom &atom);

  // destructor
  virtual ~ExecuteAtomJob();

  // getters for references
  Atom &atom() const { return mAtom; }
  PortValue &portValue() const { return *mPortValue; }
  bool hasPortValue() const { return mPortValue != NULL; }
  Logger &logger() { return *mLogger; }
  bool hasLogger() const { return mLogger != NULL; }
  Resource::Writer &writer() { return mWriter; }

  // setters
  void setPortValue(PortValue &portValue) { mPortValue = &portValue; }
  void clearPortValue() { mPortValue = NULL; }
  void setLogger(Logger &logger) { mLogger = &logger; }
  void clearLogger() { mLogger = NULL; }

  // operations
  void initialize();
  void initializeMutexs() { mAllReserver.initialize(); mPortsDataReserver.initialize(); }

 protected:
  // operations
  virtual void realJob();
  virtual void prologue();
  virtual void epilogue();

  BipError &executeAllExternalPortsAndInternalTransitions();
  void recomputeInternals();
  BipError &recomputeExternals();
  BipError &checkExternals();
  BipError &checkUnexpected(AtomExternalPort &port);
  void initializeAllExternalPorts();

  BipError &initializeAtom();
  BipError &execute(PortValue &portValue);
  BipError &execute(AtomInternalPort &port);
  BipError &execute(AtomExternalPort &port);
  BipError &update();

  void reserveAll();
  void reserve();
  void free();

  void resetIsReady();

  bool mInitialized;
  Atom &mAtom;
  PortValue *mPortValue;
  Logger *mLogger;

  vector<AtomInternalPort *> mNonExportedPorts;

  vector<AtomInternalPort *> mInternals;
  vector<AtomExternalPort *> mExternals;
  vector<AtomExternalPort *> mWaiting;
  vector<AtomExternalPort *> mUnexpected;

  Resource::Writer mWriter;
  Resource::Reserver mAllReserver;
  Resource::Reserver mPortsDataReserver;
};

#endif // _BIP_Engine_ExecuteAtomJob_HPP_
