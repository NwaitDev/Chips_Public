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

#ifndef _BIP_Engine_Resetable_HPP_
#define _BIP_Engine_Resetable_HPP_

#include <bip-engineiface-config.hpp>
using namespace bipbasetypes;
using namespace biptypes;

/** \brief 
 */
class ResetableItf {
 public:
  // constructor and destructor
  ResetableItf() : mIsReset(false), mShouldBeInitialized(false) {
#ifndef NDEBUG
    if (mIsReset) mShouldBeInitialized = true;
#endif
  }
  virtual ~ResetableItf() { }

  // setters and getters
  void dependsOn(ResetableItf &resetable) {
    // should not have been reset previously
    assert(!mShouldBeInitialized);

    resetable.mDependent.push_back(this);
  }
  bool isDependentOf(ResetableItf &resetable) const;

  // operations
  void reset();

  // setters and getters
  void setIsReset(bool b) const {
#ifndef NDEBUG
    mShouldBeInitialized = true;
#endif
    mIsReset = b;
  }
  bool isReset() const { return mIsReset; }

 protected:
  // protected attributes
  vector<ResetableItf *> mDependent;
  mutable bool mIsReset;
  mutable bool mShouldBeInitialized;
};

inline bool ResetableItf::isDependentOf(ResetableItf &resetable) const {
  return find(resetable.mDependent.begin(),
              resetable.mDependent.end(),
              this)
         != resetable.mDependent.end();
}


template<class T, class C>
class Resetable : public ResetableItf {
 public:
  // constructor and destructor
  Resetable(C *instance, void (C::*method)(T& t) const) : mInstance(*instance), mMethod(method) { }
  Resetable(C *instance, void (C::*method)(T& t) const, const T &object) : mInstance(*instance), mMethod(method), mObject(object) { }
  virtual ~Resetable() { }

  // operations
  operator const T & () const;

 protected:
  // protected attributes
  C &mInstance;
  void (C::*mMethod)(T& t) const;
  mutable T mObject;
};

template<class T, class C>
Resetable<T, C>::operator const T & () const {
  if (isReset()) {
    // call recompute method
    (mInstance.*mMethod)(mObject);

    // mark as up-to-date
    setIsReset(false);
  }

  return mObject;
}

#endif // _BIP_Engine_Resetable_HPP_
