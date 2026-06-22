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

#include <Atom.hpp>
#include <Compound.hpp>
#include <BipError.hpp>

// constructors
Atom::Atom(const string &name) :
  ComponentItf(name, ATOM),
  Component(name, ATOM),
  AtomItf(name) {
  /* implement your constructor here */
}

// destructor
Atom::~Atom() {
  /* implement your destructor here */
}
 
/* \brief Execute an internal port.
 *
 * \param internalPort is the target internal port, it should be an internal
 * port of atom 'this'.
 *
 * \return An error if found during the execution of the corresponding
 * transition, BipError::NoError otherwise.
 */
BipError &Atom::execute(AtomInternalPort &internalPort) {
  // execute
  BipError &error = execute(internalPort.portValue());

  if (error.type() != NO_ERROR) {
    return error;
  }

  // reset the interface ports
  reset();

  return BipError::NoError;
}

void Atom::reset() {
  // reset exported port which is propagate through the hierarchy
  for (map<string, AtomExportPort *>::const_iterator portIt = ports().begin() ;
       portIt != ports().end() ;
       ++portIt) {
    AtomExportPort &port = *portIt->second;

    // force recomputation of interactions and port values of connected
    // ports and connectors
    if (port.isReset()) {
      // reset connected connectors/ports
      port.reset().setIsReset(false);
      port.reset().reset();
    }
  }
}

void Atom::allNotReady() {
  // mark all exported ports as ready
  for (map<string, AtomExportPort *>::const_iterator portIt = ports().begin() ;
       portIt != ports().end() ;
       ++portIt) {
    AtomExportPort &port = *portIt->second;

    port.unsetReady();
  }
}

ostream& operator<<(ostream &o, const Atom &atom) {
  return o << atom.toString();
}

ostream& operator<<(ostream &o, const Atom *atom) {
  return o << atom->toString();
}

