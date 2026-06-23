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

#ifndef _BIP_Engine_FastMutex_HPP_
#define _BIP_Engine_FastMutex_HPP_

#include <bip-engineiface-config.hpp>
using namespace bipbasetypes;
using namespace biptypes;

#include <condition_variable>

/** \brief A fast implementation for mutual exclusion
 * mechanisms.
 *
 * 
 */

class FastMutex {
 public:
  FastMutex();
  ~FastMutex() { }

  void lock();
  void unlock();
  bool tryToLock();

 protected:
#ifdef NDEBUG
  atomic_flag mIsLocked;
#else
  atomic<bool> mIsLocked;
#endif
  atomic<unsigned int> mWaiters;
  mutex mMutex;
  condition_variable mConditionVariable;
};

inline
FastMutex::FastMutex() :
  mWaiters(0) {
#ifdef NDEBUG
  mIsLocked.clear();
#else
  mIsLocked.store(false);
#endif
}

inline
void FastMutex::lock() {
  // wait for unlocked and aquire the lock
  if (!tryToLock()) {
    mWaiters.fetch_add(1);

    unique_lock<mutex> lock(mMutex);
    while (!tryToLock()) {
      mConditionVariable.wait(lock);
    }

    mWaiters.fetch_sub(1);
  }
}

inline
void FastMutex::unlock() {
#ifdef NDEBUG
  mIsLocked.clear();
#else
  bool oldIsLocked = mIsLocked.exchange(false);
#endif

  assert(oldIsLocked);

  if (mWaiters.load() > 0) {
    unique_lock<mutex> lock(mMutex);
    mConditionVariable.notify_one();
  }
}

inline
bool FastMutex::tryToLock() {
#ifdef NDEBUG
  bool fail = mIsLocked.test_and_set();
#else
  bool fail = mIsLocked.exchange(true);
#endif

  return !fail;
}

class FastBlockableMutex {
 public:
  FastBlockableMutex() : mIsLocked(false), mWaiters(0), mBlockers(0) { }
  ~FastBlockableMutex() { }

  void lock();
  void unlock();
  bool tryToLock();
  void block();
  void unblock();

 protected:
  atomic<bool> mIsLocked;
  atomic<int> mWaiters;
  atomic<int> mBlockers;
  mutex mMutex;
  condition_variable mConditionVariable;
};

inline
void FastBlockableMutex::lock() {
  // wait for unlocked and aquire the lock
  bool oldIsLocked = !tryToLock();

  if (oldIsLocked || mBlockers.load() > 0) {
    mWaiters.fetch_add(1);

    unique_lock<mutex> lock(mMutex);

    if (oldIsLocked) oldIsLocked = !tryToLock();

    while (oldIsLocked || mBlockers.load() > 0) {
      if (!oldIsLocked) {
        mIsLocked.store(false);

        if (mWaiters.load() > 1) {
          mConditionVariable.notify_all();
        }
      }

      mConditionVariable.wait(lock);

      oldIsLocked = !tryToLock();
    }

    mWaiters.fetch_sub(1);
  }
}

inline
void FastBlockableMutex::unlock() {
  bool oldIsLock = mIsLocked.exchange(false);

  assert(oldIsLock);

  if (oldIsLock && mWaiters.load()  > 0) {
    unique_lock<mutex> lock(mMutex);
    mConditionVariable.notify_all();
  }
}

inline
bool FastBlockableMutex::tryToLock() {
  bool fail = mIsLocked.exchange(true);
  return !fail;
}

inline
void FastBlockableMutex::block() {
  mBlockers.fetch_add(1);

  if (mIsLocked.load()) {
    mWaiters.fetch_add(1);

    unique_lock<mutex> lock(mMutex);

    while (mIsLocked.load()) {
      mConditionVariable.wait(lock);
    }

    mWaiters.fetch_sub(1);
  }
}

inline
void FastBlockableMutex::unblock() {
  unsigned int remainingBlockers = mBlockers.fetch_sub(1) - 1;

  if (remainingBlockers == 0) {
    if (mWaiters.load()  > 0) {
      unique_lock<mutex> lock(mMutex);
      mConditionVariable.notify_one();
    }
  }
}

class FastMutexVector {
 public:
  class Mask {
   public:
    Mask(const FastMutexVector &mutexVector) : mCapacity(mutexVector.mCapacity) {
      mPositions = new unsigned int[mCapacity];

      for (size_t i = 0 ; i < mCapacity ; ++i) {
        mPositions[i] = 0;
      }
    }
    ~Mask() { delete[] mPositions; }

    void add(size_t position) {
      size_t index = position / (sizeof(unsigned int)*8);
      unsigned int mask = 1 << (position % (sizeof(unsigned int)*8));

      mPositions[index] |= mask;
    }

    void print() {
      for (size_t i = 0 ; i < mCapacity ; ++i) {
        unsigned int positions = mPositions[i];

        for (unsigned int j = 0 ; j < 32 ; ++j) {
          if (positions & 1) cout << "1";
          else cout << "0";

          positions = positions >> 1;
	}
        cout << "-";
      }
    }

   protected:
    size_t mCapacity;
    unsigned int *mPositions;
     
    friend class FastMutexVector;
  };

  // constructors
  FastMutexVector(size_t size);

  // destructor
  virtual ~FastMutexVector();

  // getters / setters
  void unlock(size_t position);
  bool tryToLock(size_t position);

  void unlock(const Mask &mask);
  bool tryToLock(const Mask &mask);

 protected:
  void unlock(size_t index, unsigned int mask);
  bool tryToLock(size_t index, unsigned int mask);

  size_t mSize;
  size_t mCapacity;
  atomic<unsigned int> *mIsLocked;
};

inline
void FastMutexVector::unlock(size_t position) {
  size_t index = position / (sizeof(unsigned int)*8);
  unsigned int mask = 1 << (position % (sizeof(unsigned int)*8));

  unlock(index, mask);
}

inline
bool FastMutexVector::tryToLock(size_t position) {
  size_t index = position / (sizeof(unsigned int)*8);
  unsigned int mask = 1 << (position % (sizeof(unsigned int)*8));

  return tryToLock(index, mask);
}


inline
void FastMutexVector::unlock(const Mask &mask) {
  for (size_t i = 0 ; i < mCapacity ; ++i) {
    unlock(i, mask.mPositions[i]);
  }
}

inline
bool FastMutexVector::tryToLock(const Mask &mask) {
  size_t i = 0;
  bool success = true;

  for (i = 0 ; i < mCapacity ; ++i) {
    success = tryToLock(i, mask.mPositions[i]);

    if (!success) {
      break;
    }
  }

  if (!success) {
    while (i > 0) {
      --i;
      unlock(i, mask.mPositions[i]);
    }
  }

  return success;
}


inline
void FastMutexVector::unlock(size_t index, unsigned int mask) {
  // mark unlocked
#ifdef NDEBUG
  mIsLocked[index].fetch_and(~mask);
#else
  unsigned int oldLocks = mIsLocked[index].fetch_and(~mask);
#endif

  assert(((~oldLocks) & mask) == 0);
}

inline
bool FastMutexVector::tryToLock(size_t index, unsigned int mask) {
  bool success = false;

  if (!(mIsLocked[index] & mask)) {
    unsigned int oldLocks = mIsLocked[index].fetch_or(mask);
    unsigned int acquiredLocks = (~oldLocks) & mask;

    success = (acquiredLocks == mask);

    if (!success && acquiredLocks != 0) {
      unlock(index, acquiredLocks);
    }
  }

  return success;
}

class FastMutexGroup;

class GroupableFastMutex {
 public:
  GroupableFastMutex();
  ~GroupableFastMutex();

  void unlock() { if (mMutexVector == NULL) mMutex.unlock(); else mMutexVector->unlock(mPosition); }
  bool tryToLock() { if (mMutexVector == NULL) return mMutex.tryToLock(); else return mMutexVector->tryToLock(mPosition); }

  const vector<FastMutexGroup *> &groups() const { return mGroups; }

  static void initialize();

 protected:
  void setMutexVector(FastMutexVector &mutexVector) { mMutexVector = &mutexVector; }
  void setPosition(size_t position) { mPosition = position; }
  size_t position() const { return mPosition; }

  FastMutex mMutex;
  FastMutexVector *mMutexVector;
  size_t mPosition;

  vector<FastMutexGroup *> mGroups;

  friend class FastMutexGroup;
};

class FastMutexGroup {
 public:
  FastMutexGroup();
  ~FastMutexGroup();

  // operations
  void add(GroupableFastMutex &mutex);

  void unlock() { assert(mMutexVector != NULL && mMask != NULL); mMutexVector->unlock(*mMask); }
  bool tryToLock() { assert(mMutexVector != NULL && mMask != NULL); return mMutexVector->tryToLock(*mMask); }

  const vector<GroupableFastMutex *> &mutexs() const { return mMutexs; }
  vector<FastMutexGroup *> allConflictingGroups();

  void initialize();

  void print() { mMask->print(); }

  // getter
  size_t size() const { return mMutexs.size(); }

 protected:
  void allocate();

  vector<GroupableFastMutex *> allMutexs(vector<FastMutexGroup *> &groups);
  void conflictingWith(FastMutexGroup &group);

  void setMutexVector(FastMutexVector &mutexVector) { mMutexVector = &mutexVector; }
  void setMask(FastMutexVector::Mask &mask) { mMask = &mask; }
  FastMutexVector::Mask &mask() { return *mMask; }

  vector<GroupableFastMutex *> mMutexs;
  vector<FastMutexGroup *> mConflictingGroups;

  FastMutexVector *mMutexVector;
  FastMutexVector::Mask *mMask;
};

#endif // _BIP_Engine_FastMutex_HPP_
