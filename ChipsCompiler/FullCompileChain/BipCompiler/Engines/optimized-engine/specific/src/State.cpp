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

#include "State.hpp"

#include <stdlib.h>
#include <string.h>
#include <iostream>
//#include <unordered_map>

State::State(char *buffer, size_t size) :
  mBuffer(buffer),
  mSize(size),
  mResetHash(true) {
}

State::State(const State &state) {
  mSize = state.size();
  mBuffer = new char[size()];
  memcpy(mBuffer, (void *) state.buffer(), size());

  mResetHash = true;
}

State::~State() {
  delete[] buffer();
}

/**
 * \brief 
 */
bool State::operator==(const State &state) const {
  bool ret = false;

  if (size() == state.size() && hash() == state.hash()) {
    if (memcmp(buffer(), state.buffer(), size()) == 0) {
      ret = true;
    }
  }

  return ret;
}

/**
 * \brief 
 */
bool State::operator<(const State &state) const {
  bool ret = false;

  size_t minSize = size();

  if (state.size() < minSize) {
    minSize = state.size();
  }

  int cmp = memcmp(buffer(), state.buffer(), minSize);

  if (cmp < 0) {
    ret = true;
  }
  else if (cmp == 0 && size() < state.size()) {
    ret = true;
  }

  return ret;
}

/**
 * \brief 
 */
State &State::operator=(const State &state) {
  if (this != &state) {
    delete[] buffer();

    mSize = state.size();
    mBuffer = new char[size()];
    memcpy(mBuffer, (void *) state.buffer(), size());

    mResetHash = true;
  }

  return *this;
}

/**
 * \brief Re-compute the hash value and store it into mHash.
 */
void State::recomputeHash() const {
  mHash = 2166136261;

  mHash = size();
  mHash = mHash xor size();
  mHash *= 16777619;

  for (unsigned int i = 0 ; i < size() ; ++i) {
    mHash = mHash xor buffer()[i];
    mHash *= 16777619;
  }

  mResetHash = false;
}
