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

#ifndef _BIP_Engine_Logger_HPP_
#define _BIP_Engine_Logger_HPP_

#include <bip-engineiface-config.hpp>

using namespace bipbasetypes;
using namespace biptypes;

#include <string>
#include <iostream>
#include <sstream>

#include "BipError.hpp"
#include <NonDeterministicPetriNetError.hpp>
#include <NonOneSafePetriNetError.hpp>
#include <CycleInPrioritiesError.hpp>
#include <CycleInAtomPrioritiesError.hpp>
#include <AtomInvariantViolationError.hpp>
#include <UnexpectedEventError.hpp>
#include "Connector.hpp"
#include "InteractionValue.hpp"
#include "Atom.hpp"
#include "AtomInternalPort.hpp"
#include "AtomExternalPort.hpp"

#include "Executer.hpp"

/** \brief Represent a node in a tree of strings
 */
class Logger {
 public:
  // constructor and destructor
  Logger(ostream &outoutStream, bool verbose, unsigned int limit);
  virtual ~Logger();
    
  // operations
  void log(const string &s);
  void log(BipError &error);
  void log(const InteractionValue &interaction, const vector<InteractionValue *> &interactions);
  void log(const AtomInternalPort &port, const vector<AtomInternalPort *> &internals);
  void log(const AtomExternalPort &port, const vector<AtomExternalPort *> &externals);
  void logDeadlock() { if (verbose()) { begin(); outputStream() << "state #" << mState << ": deadlock!"; end(); } }
      
 protected:
  // operations
  void begin() { while(mIsDisplaying.exchange(true)); outputStream() << "[BIP ENGINE]: "; }
  void newLine() { outputStream() << endl << "[BIP ENGINE]: "; }
  void end() { outputStream() << endl; mIsDisplaying.store(false); }
 
  // getters
  bool verbose() const { return mVerbose; }
  ostream &outputStream() { return mOutputStream; }
 
  ostream &mOutputStream;
  bool mVerbose;
  unsigned int mLimit;
public:
  atomic<unsigned int> mState;
  atomic<bool> mIsDisplaying;
 };
 
inline
void Logger::log(const string &s) {
  if (verbose()) {
    begin();
    outputStream() << s;    
    end();
  }
}
 
inline
void Logger::log(BipError &error) {
  if (error.type() != NO_ERROR) {
    begin();
    
    outputStream() << "ERROR: ";

    if (error.type() == NON_DETERMINISTIC_PETRI_NET) {
      const NonDeterministicPetriNetError &errorNonDetPetriNet = dynamic_cast<const NonDeterministicPetriNetError &>(error);

      if (errorNonDetPetriNet.hasPort()) {
        outputStream() << "non-deterministic choice between transitions labelled by " << errorNonDetPetriNet.port().name();
      }
      else {
        outputStream() << "non-deterministic choice between internal transitions";
      }

      outputStream() << " in " << errorNonDetPetriNet.atom().name() << "!";
    }
    else if (error.type() == CYCLE_IN_PRIORITIES) {
      outputStream() << "cycle in priorities! (";

      const CycleInPrioritiesError &errorPriorities = dynamic_cast<const CycleInPrioritiesError &>(error);

      for (vector<const Interaction *>::const_iterator interactionIt = errorPriorities.cycle().begin() ;
           interactionIt != errorPriorities.cycle().end() ;
           ++interactionIt) {
        const Interaction &interaction = **interactionIt;

        if (interactionIt != errorPriorities.cycle().begin()) {
          outputStream() << " < ";
        }

        outputStream() << interaction;
      }

      outputStream() << ")";
    }
    else if (error.type() == CYCLE_IN_ATOM_PRIORITIES) {
      outputStream() << "cycle in priorities! (";

      const CycleInAtomPrioritiesError &errorPriorities = dynamic_cast<const CycleInAtomPrioritiesError &>(error);

      for (vector<const AtomInternalPort *>::const_iterator portIt = errorPriorities.cycle().begin() ;
           portIt != errorPriorities.cycle().end() ;
           ++portIt) {
        const AtomInternalPort &port = **portIt;

        if (portIt != errorPriorities.cycle().begin()) {
          outputStream() << " < ";
        }

        outputStream() << port.name();
      }

      outputStream() << ")";
    }
    else if (error.type() == NON_ONE_SAFE_PETRI_NET) {
      const NonOneSafePetriNetError &errorNonOneSafe = dynamic_cast<const NonOneSafePetriNetError &>(error);

      outputStream() << "the Peri net of " << errorNonOneSafe.atom().name() << " is not 1-safe! (";
      if (errorNonOneSafe.hasPort()) {        
        outputStream() << "when executing a transition labelled by " << errorNonOneSafe.port().name();
      }
      else {
        outputStream() << "when executing an internal transition";
      }
      outputStream() << ")";
    }
    else if (error.type() == ATOM_INVARIANT_VIOLATION) {
      const AtomInvariantViolationError &errorInvariantViolation = dynamic_cast<const AtomInvariantViolationError &>(error);

      cout << "the invariant " << errorInvariantViolation.invariantName() << " of component " << errorInvariantViolation.atom().name() << " has been violated!";
    }
    else if (error.type() == UNEXPECTED_EVENT) {
      const UnexpectedEventError &errorUnexpectedEvent = dynamic_cast<const UnexpectedEventError &>(error);

      cout << "port " << errorUnexpectedEvent.port().name() << " of component " << errorUnexpectedEvent.atom().name() << " has received an event while being disabled and having event consumption policy 'error'!";
    }
    else {
      // unsupported type of error
      assert(false);
    }

    Executer::jobs.stop(error);
    
    end();
  }
}

inline
void Logger::log(const InteractionValue &interaction, const vector<InteractionValue *> &interactions) {
  unsigned int newState = 0;

  if (verbose()) {
    begin();    
    outputStream() << "state #" << mState << ": ";
    
    outputStream() << interactions.size() << " interaction";
    if (interactions.size() > 1) outputStream() << "s";
    outputStream() << ":";
        
    unsigned int index = 0;

    for (unsigned int i = 0 ; i < interactions.size() ; ++i) {
      const InteractionValue &possibleInteraction = *(interactions[i]);
      
      if (&interaction == &possibleInteraction) {
        index = i;
      }

      newLine();
      outputStream() << "  [" << i << "] " << possibleInteraction.connector().fullName() << ": " << possibleInteraction;
    }
    
    
    newLine();
    outputStream() << "-> choose [" << index << "] " << interaction.connector().fullName() << ": " << interaction;

    // /!\ order is critical!
    // for consistency of displayed states, the following incrementation
    // should be placed before end() in the verbose mode!
    newState = ++mState;

    end();
  }
  else {
    newState = ++mState;
  }

  if (mLimit != 0) {
    if (newState == mLimit) {
      Executer::jobs.stop(BipError::NoError);

      if (verbose()) {
        begin();
        outputStream() << "state #" << mState << ": stop (reached limit of " << mLimit << " interactions)";
        end();
      }
    }
  }
}

inline
void Logger::log(const AtomInternalPort &port, const vector<AtomInternalPort *> &internals) {
  unsigned int newState = 0;

  if (verbose()) {
    begin();
    outputStream() << "state #" << mState << ": ";

    outputStream() << internals.size() << " internal port";
    if (internals.size() > 1) outputStream() << "s";
    outputStream() << ":";
        
    unsigned int index = 0;

    for (unsigned int i = 0 ; i < internals.size() ; ++i) {
      const AtomInternalPort &possibleInternal = *(internals[i]);
      
      if (&port == &possibleInternal) {
        index = i;
      }

      newLine();
      outputStream() << "  [" << i << "] " << possibleInternal.holder().fullName() << "." << possibleInternal.name();
    }
    
    // /!\ order is critical!
    // for consistency of displayed states, the following incrementation
    // should be placed before end() in the verbose mode!
    newState = ++mState;
    
    newLine(); 
    outputStream() << "-> choose [" << index << "] " << port.holder().fullName() << "." << port.name()  ;

    end();
  }
  else {
    newState = ++mState;
  }

  if (mLimit != 0) {
    if (newState == mLimit) {
      Executer::jobs.stop(BipError::NoError);

      if (verbose()) {
        begin();
        outputStream() << "state #" << mState << ": stop (reached limit of " << mLimit << " interactions)";
        end();
      }
    }
  }
}

inline
void Logger::log(const AtomExternalPort &port, const vector<AtomExternalPort *> &externals) {
  unsigned int newState = 0;

  if (verbose()) {
    begin();
    outputStream() << "state #" << mState << ": ";

    outputStream() << externals.size() << " external port";
    if (externals.size() > 1) outputStream() << "s";
    outputStream() << ":";
        
    unsigned int index = 0;

    for (unsigned int i = 0 ; i < externals.size() ; ++i) {
      const AtomExternalPort &possibleInternal = *(externals[i]);
      
      if (&port == &possibleInternal) {
        index = i;
      }

      newLine();
      outputStream() << "  [" << i << "] " << possibleInternal.holder().fullName() << "." << possibleInternal.name();
    }
    
    
    newLine(); 
    outputStream() << "-> choose [" << index << "] " << port.holder().fullName() << "." << port.name();

    // /!\ order is critical!
    // for consistency of displayed states, the following incrementation
    // should be placed before end() in the verbose mode!
    newState = ++mState;

    end();
  }
  else {
    newState = ++mState;
  }

  if (mLimit != 0) {
    if (newState == mLimit) {
      Executer::jobs.stop(BipError::NoError);

      if (verbose()) {
        begin();
        outputStream() << "state #" << mState << ": stop (reached limit of " << mLimit << " states)";
        end();
      }
    }
  }
}


#endif // _BIP_Engine_Logger_HPP_
