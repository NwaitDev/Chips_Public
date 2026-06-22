/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
 *  Marc Pouhliès
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

#include <Explorer.hpp>
#include <InteractionValue.hpp>
#include <Atom.hpp>
#include <AtomInternalPort.hpp>
#include <AtomExportPort.hpp>
#include <BipError.hpp>
#include <NonDeterministicPetriNetError.hpp>
#include <NonOneSafePetriNetError.hpp>
#include <CycleInPrioritiesError.hpp>
#include <CycleInAtomPrioritiesError.hpp>
#include <State.hpp>

#include <stdlib.h>
#include <engine-version.hpp>

#include <string>
#include <iostream>
#include <sstream>

bool isSerializeEnabled();
void serialize(char **, size_t *);
void deserialize(const char *, size_t);

Explorer::Explorer(Engine &engine, bool verbose, unsigned int limit) :
  Scheduler(engine),
  mVerbose(verbose),
  mLimit(limit),
  nbErrors(0) {
}

Explorer::~Explorer() {
}

/**
 * \brief Initialize the system.
 */
BipError &Explorer::initialize() {
  if (verbose()) {
    cout << "[BIP ENGINE]: BIP Engine (version " ENGINE_VERSION  " )" << endl;
    cout << "[BIP ENGINE]:" << endl;
    cout << "[BIP ENGINE]: initialize components..." << endl;
  }

  BipError &error = engine().initialize();

  if (error.type() != NO_ERROR) {
    ++nbErrors;
  } 

  return BipError::NoError;
}

/**
 * \brief Compute all execution sequences and corresponding reachable states
 * of the model.
 */
BipError &Explorer::run() {
  vector<State> states;
  vector<State> deadlocks;
  vector<State> errors;

  if (verbose()) {
    cout << "[BIP ENGINE]: computing reachable states:";
  }

  if (isSerializeEnabled()) {
    if (nbErrors == 0) {
      nbErrors = dfsExplore(states, deadlocks, errors, 0);
    }

    if (verbose()) {
      cout << " found " << states.size() << " reachable state";
      if (states.size() > 1) cout << "s";

      cout << ", " << deadlocks.size() << " deadlock";
      if (deadlocks.size() > 1) cout << "s";

      cout << ", and " << nbErrors << " error";
      if (nbErrors > 1) cout << "s";

      cout << " in " << errors.size() << " state";
      if (errors.size() > 1) cout << "s";

      cout << endl;
	}
  }
  else {
    cout << endl;
    cout << "[BIP ENGINE]: ERROR: missing serialization functions!" << endl;
    cout << "[BIP ENGINE]: Try to recompile with option '--gencpp-enable-marshalling'" << endl;
  }

  return BipError::NoError;
}


/**
 * \brief Recursive method for exploration of execution sequences.
 *
 * The exploration is made by a DFS search implemented recursively.
 * The recursion is stopped whenever a state has been already visited, or
 * a deadlock or an error is found.
 *
 * \param states is used for storing all the reachable states.
 * \param deadlocks is used for storing all the reachable states from
 * which no interaction / internal port is enabled.
 * \param errors is used for storing all the reachable states form
 * which the execution of an interaction / internal port leads to an
 * error.
 * \param size is the current size of the computed execution sequence.
 *
 * \return the total number of errors found from the error states.
 */
unsigned int Explorer::dfsExplore(vector<State> &states, vector<State> &deadlocks, vector<State> &errors, unsigned int size) {
  if (verbose()) {
    cout << "."; cout.flush();
  }

  int nbErrors = 0;
  State state = engine().getState();

  // check for visisted states
  if (find(states.begin(), states.end(), state) == states.end()) {
    unsigned int nbInteractions = engine().interactions().size();
    unsigned int nbInternals = engine().internals().size();

    // add the current state to reachable states
    states.push_back(state);

    // check for deadlocks
    if (nbInteractions == 0 && nbInternals == 0) {
      deadlocks.push_back(state);
    }

    bool errorFromState = false;

    // check for limit of execution sequences
    if (!(limit() > 0 && size >= limit())) {
      for (unsigned int i = 0 ; i < nbInteractions ; ++i) {
        // go back to the origin state
        engine().setState(state);

        InteractionValue &chosenInteraction = *engine().interactions()[i];
        BipError &error = engine().execute(chosenInteraction);

        if (error.type() == NO_ERROR) {
          nbErrors += dfsExplore(states, deadlocks, errors, size + 1);
        }
        else {
          errorFromState = true;
          ++nbErrors;
        }
      }

      for (unsigned int i = 0 ; i < nbInternals ; ++i) {
        // go back to the original state
        engine().setState(state);

        AtomInternalPort &chosenInternal = *engine().internals()[i];
        BipError &error = engine().execute(chosenInternal);

        if (error.type() == NO_ERROR) {
          nbErrors += dfsExplore(states, deadlocks, errors, size + 1);
        }
        else {
          errorFromState = true;
          ++nbErrors;
        }
      }

      if (errorFromState) {
        errors.push_back(state);
      }
    }
  }

  return nbErrors;
}

/**
 * \brief Handle error returned by the engine.
 * 
 * initialize() and execute() methods of the engine may return an error,
 * i.e. an instance of BipError. Such instances should be catched by
 * the scheduler in order to stop the current execution and provide
 * a useful report to the user (e.g. error message, etc.).
 *
 * \param error: the target instance of BipError.
 */
void Explorer::handleError(BipError &error) {
  if (error.type() != NO_ERROR) {

    cout << "[BIP ENGINE]: ERROR: ";

    if (error.type() == NON_DETERMINISTIC_PETRI_NET) {
      const NonDeterministicPetriNetError &errorNonDetPetriNet = dynamic_cast<const NonDeterministicPetriNetError &>(error);

      if (errorNonDetPetriNet.hasPort()) {
        cout << "non-deterministic choice between transitions labelled by" << errorNonDetPetriNet.port().name();
      }
      else {
        cout << "non-deterministic choice between internal transitions";
      }

      cout << " in " << errorNonDetPetriNet.atom().name() << "!";
    }
    else if (error.type() == CYCLE_IN_PRIORITIES) {
      cout << "cycle in priorities! (";

      const CycleInPrioritiesError &errorPriorities = dynamic_cast<const CycleInPrioritiesError &>(error);

      for (vector<const Interaction *>::const_iterator interactionIt = errorPriorities.cycle().begin() ;
           interactionIt != errorPriorities.cycle().end() ;
           ++interactionIt) {
        const Interaction &interaction = **interactionIt;

        if (interactionIt != errorPriorities.cycle().begin()) {
          cout << " < ";
        }

        cout << interaction;
      }

      cout << ")";
    }
    else if (error.type() == CYCLE_IN_ATOM_PRIORITIES) {
      cout << "cycle in priorities! (";

      const CycleInAtomPrioritiesError &errorPriorities = dynamic_cast<const CycleInAtomPrioritiesError &>(error);

      for (vector<const AtomInternalPort *>::const_iterator portIt = errorPriorities.cycle().begin() ;
           portIt != errorPriorities.cycle().end() ;
           ++portIt) {
        const AtomInternalPort &port = **portIt;

        if (portIt != errorPriorities.cycle().begin()) {
          cout << " < ";
        }

        cout << port.name();
      }

      cout << ")";
    }
    else if (error.type() == NON_ONE_SAFE_PETRI_NET) {
      const NonOneSafePetriNetError &errorNonOneSafe = dynamic_cast<const NonOneSafePetriNetError &>(error);

      cout << "the Peri net of " << errorNonOneSafe.atom().name() << " is not 1-safe! (";
      if (errorNonOneSafe.hasPort()) {        
        cout << "when executing a transition labelled by " << errorNonOneSafe.port().name();
      }
      else {
        cout << "when executing an internal transition";
      }
      cout << ")";
    }
    else {
      // unsupported type of error
      assert(false);
    }

    cout << endl;

    ErrorType returnedErrorType = error.type();

    delete &error;

    exit(returnedErrorType);
  }
}
