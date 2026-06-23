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

#ifndef _BIP_Engine_Initializable_HPP_
#define _BIP_Engine_Initializable_HPP_

#include <bip-engineiface-config.hpp>
using namespace bipbasetypes;
using namespace biptypes;

/** \brief 
 */
class InitializableItf {
 public:
  // constructor and destructor
  InitializableItf(bool initialized = false) : mIsInitialized(initialized) { }
  virtual ~InitializableItf() { }

  // setters and getters
  void dependsOn(InitializableItf &initializable) { mDependencies.push_back(&initializable); }

  // operations
  void initialize();

 protected:
  // operations
  virtual void compute() = 0;

  bool isInitialized() const { return mIsInitialized; }
  void initialized() { mIsInitialized = true; }

  // protected attributes
  vector<InitializableItf *> mDependencies;
  mutable bool mIsInitialized;
};

template<class T, class C>
class Initializable : public InitializableItf {
 public:
  // constructor and destructor
  Initializable(C *instance, void (C::*method)(T& t)) : mInstance(*instance), mMethod(method) { }
  Initializable(bool initialized, C *instance, void (C::*method)(T& t)) : InitializableItf(initialized), mInstance(*instance), mMethod(method) { }
  virtual ~Initializable() { }

  // setters and getters
  const T &value() const { assert(isInitialized()); return mObject; }

 protected:
  // operations
  virtual void compute() { (mInstance.*mMethod)(mObject); }

  // protected attributes
  C &mInstance;
  void (C::*mMethod)(T& t);
  T mObject;
};

#endif // _BIP_Engine_Initializable_HPP_
