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

#include "FastMutex.hpp"

FastMutexVector::FastMutexVector(size_t size) :
  mSize(size),
  mCapacity(1 + size / (sizeof(unsigned int)*8)) {
  // allocate arrays
  mIsLocked = new atomic<unsigned int>[mCapacity];

  // locked status to unlock
  for (size_t i = 0 ; i < mCapacity ; ++i) {
    mIsLocked[i] = 0;
  }
}

FastMutexVector::~FastMutexVector() {
  delete[] mIsLocked;
}

GroupableFastMutex::GroupableFastMutex() :
  mMutexVector(NULL),
  mPosition(0) {
}

GroupableFastMutex::~GroupableFastMutex() {
}

FastMutexGroup::FastMutexGroup() :
  mMutexVector(NULL),
  mMask(NULL) {
}

FastMutexGroup::~FastMutexGroup() {
}

void FastMutexGroup::add(GroupableFastMutex &mutex) {
  // should be non initialized
  assert(mMutexVector == NULL && mMask == NULL);

  // update the conflicts
  if (find(mMutexs.begin(), mMutexs.end(), &mutex) == mMutexs.end()) {
    // update conflicts
    for (vector<FastMutexGroup *>::const_iterator groupIt = mutex.mGroups.begin() ;
         groupIt != mutex.mGroups.end() ;
         ++groupIt) {
      FastMutexGroup &group = **groupIt;

      conflictingWith(group);
    }

    // record that mutex belong to a new group
    mutex.mGroups.push_back(this);
    mMutexs.push_back(&mutex);
  }
}

void FastMutexGroup::conflictingWith(FastMutexGroup &group) {
  // should be non initialized
  assert(mMutexVector == NULL && mMask == NULL);

  mConflictingGroups.push_back(&group);
  group.mConflictingGroups.push_back(this);
}

vector<FastMutexGroup *> FastMutexGroup::allConflictingGroups() {
  vector<FastMutexGroup *> toVisitGroups;
  vector<FastMutexGroup *> visitedGroups;

  toVisitGroups.push_back(this);

  while (!toVisitGroups.empty()) {
    // pick one group to visit
    FastMutexGroup &group = *(toVisitGroups.back());
    toVisitGroups.pop_back();

    // store it as visited
    if (find(visitedGroups.begin(),
             visitedGroups.end(),
             &group) == visitedGroups.end()) {
      visitedGroups.push_back(&group);
    }

    // check its conflicting groups
    for (vector<FastMutexGroup *>::const_iterator groupIt = group.mConflictingGroups.begin() ;
         groupIt != group.mConflictingGroups.end() ;
         ++groupIt) {
      FastMutexGroup &conflictingGroup = **groupIt;

      // check if conflicting group has been already visited
      if ((find(visitedGroups.begin(),
                visitedGroups.end(),
                &conflictingGroup) == visitedGroups.end()) &&
          (find(toVisitGroups.begin(),
                toVisitGroups.end(),
                &conflictingGroup) == toVisitGroups.end())) {
        toVisitGroups.push_back(&conflictingGroup);
      }
    }
  }

  return visitedGroups;
}

vector<GroupableFastMutex *> FastMutexGroup::allMutexs(vector<FastMutexGroup *> &groups) {
  vector<GroupableFastMutex *> ret;

  for (vector<FastMutexGroup *>::const_iterator groupIt = groups.begin() ;
       groupIt != groups.end() ;
       ++groupIt) {
    FastMutexGroup &group = **groupIt;

    for (vector<GroupableFastMutex *>::const_iterator mutexIt = group.mutexs().begin() ;
         mutexIt != group.mutexs().end() ;
         ++mutexIt) {
      GroupableFastMutex &mutex = **mutexIt;

      // allocate a position for mutex if not already allocated
      if (find(ret.begin(),
               ret.end(),
               &mutex) == ret.end()) {
        ret.push_back(&mutex);
      }
    }
  }

  return ret;
}

void FastMutexGroup::initialize() {
  allocate();
}

void FastMutexGroup::allocate() {
  // check whether it is already allocated or not
  if (mMutexVector == NULL && mMask == NULL) {
    // compute all mutexs and groups that should be allocated at the same time
    vector<FastMutexGroup *> groupsToAllocate = allConflictingGroups();
    vector<GroupableFastMutex *> mutexsToAllocate = allMutexs(groupsToAllocate);

    // allocate a new vector for representing mutexs
    FastMutexVector &mutexVector = *new FastMutexVector(mutexsToAllocate.size());

    // allocate groups
    for (vector<FastMutexGroup *>::const_iterator groupIt = groupsToAllocate.begin() ;
         groupIt != groupsToAllocate.end() ;
         ++groupIt) {
      FastMutexGroup &group = **groupIt;

      // alloacte a new mask
      FastMutexVector::Mask &mask = *new FastMutexVector::Mask(mutexVector);

      group.setMutexVector(mutexVector);
      group.setMask(mask);
    }

    // allocated mutexs et update mask
    for (size_t i = 0 ; i < mutexsToAllocate.size() ; ++i) {
      GroupableFastMutex &mutex = *mutexsToAllocate[i];

      mutex.setMutexVector(mutexVector);
      mutex.setPosition(i);

      // update mask of corresponding groups
      for (vector<FastMutexGroup *>::const_iterator groupIt = mutex.groups().begin() ;
           groupIt != mutex.groups().end() ;
           ++groupIt) {
        FastMutexGroup &group = **groupIt;

        group.mask().add(i);
      }
    }
  }
  else {
    assert(mMutexVector != NULL && mMask != NULL);
  }
}
