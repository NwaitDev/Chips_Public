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

#include "Logger.hpp"
#include "BipError.hpp"
#include "InteractionValue.hpp"
#include "AtomInternalPort.hpp"
#include "AtomExternalPort.hpp"

Logger::Logger(ostream &outputStream, bool verbose, unsigned int limit) :
  mOutputStream(outputStream),
  mVerbose(verbose),
  mLimit(limit),
  mState(0) {
}

Logger::~Logger() {
}


void Logger::log(const string &s) {
  if (verbose()) {
    begin();
    outputStream() << s;
    end();
  }
}
 
void Logger::log(const BipError &error) {
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
    
    end();

    ErrorType returnedErrorType = error.type();

    delete &error;

    exit(returnedErrorType);
  }
}

void Logger::log(const vector<InteractionValue *> &interactions, const vector<AtomInternalPort *> &internals, const vector<AtomExternalPort *> &externals) {
  if (verbose()) {
    begin();

    outputStream() << "state #" << mState << ": ";

    if (interactions.size() == 0 && internals.size() == 0 && externals.size() == 0) {
      outputStream() << "deadlock!";
    }
    else if (reachedLimit()) {
      outputStream() << "stop (reached limit of " << mLimit << " states)";
    }
    else {
      if (interactions.size() > 0) outputStream() << interactions.size() << " interaction";
      if (interactions.size() > 1) outputStream() << "s";
      if (interactions.size() > 0 && internals.size() > 0) outputStream() << " and ";
      if (internals.size() > 0) outputStream() << internals.size() << " internal port";
      if (internals.size() > 1) outputStream() << "s";
      if ((interactions.size() > 0 || internals.size() > 0) && externals.size() > 0) outputStream() << " and ";
      if (externals.size() > 0) outputStream() << externals.size() << " external port";
      if (externals.size() > 1) outputStream() << "s";
      outputStream() << ":";

      for (unsigned int i = 0 ; i < interactions.size() ; ++i) {
        const InteractionValue &interaction = *(interactions[i]);

        newLine();
        outputStream() << "  [" << i << "] " << interaction.connector().fullName() << ": " << interaction;
      }

      for (unsigned int i = 0 ; i < internals.size() ; ++i) {
        const AtomInternalPort &port = *(internals[i]);
      
        newLine();
        outputStream() << "  [" << i + interactions.size() << "] " << port.holder().fullName() << "." << port.name();
      }

      for (unsigned int i = 0 ; i < externals.size() ; ++i) {
        const AtomExternalPort &port = *(externals[i]);
      
        newLine();
        outputStream() << "  [" << i + interactions.size() + internals.size() << "] " << port.holder().fullName() << "." << port.name();
      }
    }

    end();
  }
}

void Logger::log(const InteractionValue &interaction, const vector<InteractionValue *> &interactions, const vector<AtomInternalPort *> &internals, const vector<AtomExternalPort *> &externals) {
  if (verbose()) {
    begin();
    
    // compute the index of interaction
    vector<InteractionValue *>::const_iterator interactionIt =
      find(interactions.begin(),
           interactions.end(),
           &interaction);

    assert(interactionIt != interactions.end());

    unsigned int index = distance(interactions.begin(), interactionIt);

    outputStream() << "-> choose [" << index << "] " << interaction.connector().fullName() << ": " << interaction;
    end();
  }

  newState();
}

void Logger::log(const AtomInternalPort &port, const vector<InteractionValue *> &interactions, const vector<AtomInternalPort *> &internals, const vector<AtomExternalPort *> &externals) {
  if (verbose()) {
    begin();
    
    // compute the index of interaction
    vector<AtomInternalPort *>::const_iterator portIt =
      find(internals.begin(),
           internals.end(),
           &port);

    assert(portIt != internals.end());

    unsigned int index = distance(internals.begin(), portIt) + interactions.size();

    outputStream() << "-> choose [" << index << "] " << port.holder().fullName() << "." << port.name()  ;
    end();
  }

  newState();
}

void Logger::log(const AtomExternalPort &port, const vector<InteractionValue *> &interactions, const vector<AtomInternalPort *> &internals, const vector<AtomExternalPort *> &externals) {
  if (verbose()) {
    begin();
    
    vector<AtomExternalPort *>::const_iterator portIt =
      find(externals.begin(),
           externals.end(),
           &port);

    assert(portIt != externals.end());

    unsigned int index = distance(externals.begin(), portIt) + interactions.size() + internals.size();

    outputStream() << "-> choose [" << index << "] " << port.holder().fullName() << "." << port.name()  ;
    end();
  }

  newState();
}
