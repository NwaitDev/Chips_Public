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

#ifndef _BIP_Engine_ReadyQueue_HPP_
#define _BIP_Engine_ReadyQueue_HPP_

#include <bip-engineiface-config.hpp>
using namespace bipbasetypes;
using namespace biptypes;

#include <BipError.hpp>

class Thread;

/** \brief Thread-safe implementation of a ready queue.
 *
 * 
 */
template<class T>
class ReadyQueue {
 public:
  // constructors
  ReadyQueue(unsigned int capacity) : mCapacity(0), mIsStopped(false), mError(&BipError::NoError), mPopIndex(0), mPushIndex(0), mSporadicPush(0), mInactive(false) {
    // round capacity to a power of 2
    mCapacity = 1;

    while (capacity != 0) {
      capacity >>= 1;
      mCapacity <<= 1;
    }

    // mask for keeping only relevant bits
    mCapacityMask = mCapacity - 1;

    // allocate places
    mArray = new atomic<T *>[mCapacity];
    mWaiters = new atomic<unsigned int>[mCapacity];
    mMutex = new mutex[mCapacity];
    mConditionVariable = new condition_variable[mCapacity];

    // initialize places to empty (i.e. NULL)
    for (unsigned int i = 0 ; i < mCapacity ; ++i) {
      mArray[i].store(NULL);
      mWaiters[i].store(0);
    }
  }

  // destructor
  virtual ~ReadyQueue();

  // getters / setters
  bool empty() const;
  void stop(BipError &error);

  T *waitAndPop();
  void push(T &t);

  void addThread(Thread &thrd) { mThreads.push_back(&thrd); }
  const vector<Thread *> &threads() const { return mThreads; }

  void addSporadicPush(unsigned int v) { mSporadicPush.fetch_add(v); }
  void removeSporadicPush(unsigned int v) { mSporadicPush.fetch_sub(v); }

  BipError &waitForNoActivity();

 protected:
  void setActive() { mInactive.store(false); }
  void setInactive();

  // capacity
  unsigned int mCapacity;
  unsigned int mCapacityMask;

  // status: active or not
  atomic<bool> mIsStopped;
  BipError *mError;

  // indexes for pop and push
  atomic<unsigned int> mPopIndex;
  atomic<unsigned int> mPushIndex;

  // synchronization variables
  atomic<unsigned int> *mWaiters;
  mutex *mMutex;
  condition_variable *mConditionVariable;

  // content of the queue
  atomic<T *> *mArray;
  
  // potential waiting threads
  vector<Thread *> mThreads;

  // number of sporadic push (can be performed at any time)
  atomic<unsigned int> mSporadicPush;

  // activity
  atomic<bool> mInactive;

  // global mutexs
  mutex mGlobalMutex;
  condition_variable mGlobalConditionVariable;
};

template<class T>
inline ReadyQueue<T>::~ReadyQueue() {
}

template<class T>
inline bool ReadyQueue<T>::empty() const {
  // order is critical to avoid spurious empty() == true
  unsigned int popIndex = mPopIndex.load();
  unsigned int pushIndex = mPushIndex.load();

  // empty if pressure = nb of threads
  return popIndex == pushIndex + mThreads.size();
}

template<class T>
inline void ReadyQueue<T>::stop(BipError &error) {
  // mark inactive to prevent from further push
  if (!mIsStopped.exchange(true)) {
    // set the error that caused the stop
    mError = &error;

    // purge the queue
    for (unsigned int i = 0 ; i < mCapacity ; ++i) {
      mArray[i].store(NULL);
      unique_lock<mutex> lock(mMutex[i]);
      mConditionVariable[i].notify_all();
    }

    // inform inactivity
    setInactive();
  }
}

template<class T>
inline T *ReadyQueue<T>::waitAndPop() {
  T *ret = NULL;

  // first try
  unsigned int popIndex = mPopIndex.fetch_add(1);
  unsigned int myIndex = popIndex;

  // implements circular indexing
  if (myIndex >= mCapacity) {
    myIndex &= mCapacityMask;
  }

  ret = mArray[myIndex].exchange(NULL);

  while (ret == NULL && mPushIndex.load() > popIndex && !mIsStopped.load()) {
    ret = mArray[myIndex].exchange(NULL);
  }

  // wait notify/mechanism
  if (ret == NULL && !mIsStopped.load()) {
    mWaiters[myIndex].fetch_add(1);

    unique_lock<mutex> lock(mMutex[myIndex]);

    // retry
    ret = mArray[myIndex].exchange(NULL);

    while (ret == NULL && !mIsStopped.load()) {
      // check for inactivity
      if (empty() && mSporadicPush.load() == 0) {
        setInactive();
      }

      // wait for new values
      mConditionVariable[myIndex].wait(lock);

      // retry
      ret = mArray[myIndex].exchange(NULL);
    }

    mWaiters[myIndex].fetch_sub(1);
  }

  if (mIsStopped.load()) ret = NULL;

  return ret;
}

template<class T>
inline void ReadyQueue<T>::push(T &t) {
  if (!mIsStopped.load()) {
    // compute the correct index for pushing
    unsigned int myIndex = mPushIndex.fetch_add(1);

    // implements circular indexing
    if (myIndex >= mCapacity) {
      myIndex &= mCapacityMask;

      if (mPopIndex >= mCapacity) {
        // order is critical to avoid spurious empty() == true
        mPopIndex.fetch_and(mCapacityMask);
        mPushIndex.fetch_and(mCapacityMask);
      }
    }

    // perform the push in the queue
    T *nullValue = NULL;

    while (!((mArray[myIndex]).compare_exchange_weak(nullValue, &t)) && !mIsStopped.load()) {
      nullValue = NULL;
    }

    // notify waiting threads
    if (mWaiters[myIndex].load() > 0 && mArray[myIndex].load() != NULL) {
      unique_lock<mutex> lock(mMutex[myIndex]);
      mConditionVariable[myIndex].notify_one();
      setActive();
    }
  }
}

template<class T>
inline BipError &ReadyQueue<T>::waitForNoActivity() {
  unique_lock<mutex> lock(mGlobalMutex);

  while (!mInactive.load()) {
    mGlobalConditionVariable.wait(lock);
  }

  return *mError;
}

template<class T>
inline void ReadyQueue<T>::setInactive() {
  if (!mInactive.exchange(true)) {
    unique_lock<mutex> lock(mGlobalMutex);
    mGlobalConditionVariable.notify_all();
  }
}


#endif // _BIP_Engine_ReadyQueue_HPP_
