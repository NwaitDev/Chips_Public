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

#include <Component.hpp>
#include <Compound.hpp>
#include <BipError.hpp>

// constructors
Component::Component(const string &name, const ComponentType &type) :
  ComponentItf(name, type) {
  /* implement your constructor here */
}

// destructor
Component::~Component() {
  /* implement your destructor here */
}

/**
 * \brief Update port values of upper level compounds.
 *
 * Requires that compound 'this' is up-to-date.
 *
 * \return An error if found during the update of port values,
 * BipError::NoError otherwise.
 */
BipError &Component::updateUpperLevels() {
  if (hasHolder()) {
    BipError &error = holder().update();

    if (error.type() != NO_ERROR) {
      return error;
    }

    holder().updateUpperLevels();
  }

  return BipError::NoError;
}

string Component::fullName() const {
  string ret;

  if (hasHolder()) {
    ret = holder().fullName() + ".";
  }

  ret = ret + name();

  return ret;
}
