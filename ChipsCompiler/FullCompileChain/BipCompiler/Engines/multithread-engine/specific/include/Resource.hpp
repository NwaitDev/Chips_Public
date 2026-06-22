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

#ifndef _BIP_Engine_Resource_HPP_
#define _BIP_Engine_Resource_HPP_

#include "FastMutex.hpp"
#include "Job.hpp"

class Resource {
 public:
  class Accessor;
  class Writer;
  class Validator;

  enum Status { FREE, RESERVED, USED };

  // constructors
  Resource() : mStatus(FREE) { }

  // destructor
  virtual ~Resource() { }

  // getters/setters
  Status status() const { return mStatus.load(); }
  void setStatus(Status status);

  // operations
  void use();
  void free();

  class Reserver {
   public:
    Reserver() : mJob(NULL) { }
    Reserver(Job &job) : mJob(&job) { }
    virtual ~Reserver() { }

    const vector<Resource *> &resources() const { return mResources; }
    const vector<Resource *> &observedResources() const { return mObservedResources; }
    Job &job() { return *mJob; }
    bool hasJob() const { return mJob != NULL; }
    
    void addResource(Resource &resource);
    void addObservedResource(Resource &resource);
    void initialize();
    
    bool tryToReserve();
    virtual void uponReservation() { }
    void free();

    void start();
    void end();
      
   protected:
    void addValidator(Validator &validator);
    
    void preventReservers();
    void unpreventReservers();
    
    void block() { mBlocker.block(); }
    void unblock() { mBlocker.unblock(); }
    
    vector<Resource *> mResources;
    vector<Resource *> mObservedResources;
    vector<Validator *> mValidators;
    
    FastBlockableMutex mBlocker;
    FastMutexGroup mReserveGroup;
    FastMutexGroup mObservedReserveGroup;
    Job *mJob;

    friend class Validator;
    friend class Resource;
  };

  class Writer {
   public:
    Writer() { }
    virtual ~Writer() { }
    
    const vector<Resource *> &resources() const { return mResources; }

    void addResource(Resource &resource);
    
    void free();
    
    void start();
    void end();
  
   protected:
    vector<Resource *> mResources;
    FastMutexGroup mReserveGroup;
  };

  class Validator {
   public:
    Validator() : mIsValid(true) { }
    virtual ~Validator() { }

    const vector<Resource *> &resources() const { return mResources; }
    void addResource(Resource &resource);

    bool isValid() const { return mIsValid.load(); }
    void setIsValid(bool valid);
    
    virtual void reset(const vector<Resource *> &resources) = 0;
    virtual void free(Resource &resource) = 0;
    
   protected:
    vector<Resource *> mResources;
    GroupableFastMutex mReserve;

    atomic<bool> mIsValid;

    friend class Reserver;
  };

 protected:  
  // getters
  const vector<Reserver *> &reservers() const { return mReservers; }
  const vector<Writer *> &writers() const { return mWriters; }
  const vector<Validator *> &validators() const { return mValidators; }

  // setters
  void addReserver(Reserver &reserver);
  void addWriter(Writer &writer);
  void addValidator(Validator &validator);
  
  // operations
  void block();
  void unblock();

  void preventReservers();
  void unpreventReservers();

  void notifyValidators();
  
  // attributes
  GroupableFastMutex mReserve;
  atomic<Status> mStatus;

  // references
  vector<Reserver *> mReservers;
  vector<Writer *> mWriters;
  vector<Validator *> mValidators;
};

inline void Resource::addReserver(Resource::Reserver &reserver) {
  if (find(mReservers.begin(),
           mReservers.end(),
           &reserver)
      == mReservers.end()) {
    mReservers.push_back(&reserver);
  }
}

inline void Resource::addWriter(Resource::Writer &writer) {
  if (find(mWriters.begin(),
           mWriters.end(),
           &writer)
      == mWriters.end()) {
    mWriters.push_back(&writer);
  }
}

inline void Resource::addValidator(Resource::Validator &validator) {
  if (find(mValidators.begin(),
           mValidators.end(),
           &validator)
      == mValidators.end()) {
    mValidators.push_back(&validator);

    for (vector<Reserver *>::const_iterator reserverIt = reservers().begin() ;
         reserverIt != reservers().end() ;
         ++reserverIt) {
      Reserver &reserver = **reserverIt;

      reserver.addValidator(validator);
    }
  }
}

inline void Resource::setStatus(Status status) {
#ifdef NDEBUG
  mStatus.store(status);
#else
  Status oldStatus = mStatus.exchange(status);
#endif
  
  assert((oldStatus == FREE && status == RESERVED) ||
         (oldStatus == RESERVED && status == USED) ||
         (oldStatus == RESERVED && status == FREE) ||
         (oldStatus == USED && status == FREE));
}

inline void Resource::use() {
  block();

  assert(status() == RESERVED);
      
  setStatus(USED);
}

inline void Resource::free() {
  assert(status() == RESERVED || status() == USED);

  bool used = (status() == USED);
    
  setStatus(FREE);

  notifyValidators();
  
  unpreventReservers();
  
  mReserve.unlock();
  
  if (used) {
    unblock();
  }
}

inline void Resource::block() {
  for (vector<Resource::Reserver *>::const_iterator reserverIt = mReservers.begin() ;
       reserverIt != mReservers.end() ;
       ++reserverIt) {
    Resource::Reserver &reserver = **reserverIt;

    reserver.block();
  }

  preventReservers();
}

inline void Resource::unblock() {
  for (vector<Resource::Reserver *>::const_iterator reserverIt = mReservers.begin() ;
       reserverIt != mReservers.end() ;
       ++reserverIt) {
    Resource::Reserver &reserver = **reserverIt;

    reserver.unblock();
  }

  unpreventReservers();
}

inline void Resource::preventReservers() {
  for (vector<Resource::Reserver *>::const_iterator reserverIt = mReservers.begin() ;
       reserverIt != mReservers.end() ;
       ++reserverIt) {
    Resource::Reserver &reserver = **reserverIt;

    if (reserver.hasJob()) {
      reserver.job().preventEnqueuing();
    }
  }
}

inline void Resource::unpreventReservers() {
  for (vector<Resource::Reserver *>::const_iterator reserverIt = mReservers.begin() ;
       reserverIt != mReservers.end() ;
       ++reserverIt) {
    Resource::Reserver &reserver = **reserverIt;

    if (reserver.hasJob()) {
      reserver.job().unpreventEnqueuing();
    }
  }
}

inline void Resource::notifyValidators() {
  for (vector<Validator *>::const_iterator validatorIt = validators().begin() ;
       validatorIt != validators().end() ;
       ++validatorIt) {
    Validator &validator = **validatorIt;

    validator.free(*this);
  }
}

inline void Resource::Reserver::addResource(Resource &resource) {
  if (find(mResources.begin(),
           mResources.end(),
           &resource)
      == mResources.end()) {
    mResources.push_back(&resource);
  }
  
  mReserveGroup.add(resource.mReserve);
  
  resource.addReserver(*this);

  for (vector<Validator *>::const_iterator validatorIt = resource.validators().begin() ;
       validatorIt != resource.validators().end() ;
       ++validatorIt) {
    Validator &validator = **validatorIt;

    addValidator(validator);
  }
}

inline void Resource::Reserver::addObservedResource(Resource &resource) {
  if (find(mResources.begin(),
           mResources.end(),
           &resource)
      == mResources.end()) {    
    mObservedResources.push_back(&resource);    
  }
  
  mReserveGroup.add(resource.mReserve);
  mObservedReserveGroup.add(resource.mReserve);
  
  resource.addReserver(*this);
}

inline void Resource::Reserver::addValidator(Validator &validator) {  
  if (find(mValidators.begin(),
           mValidators.end(),
           &validator)
      == mValidators.end()) {
    mReserveGroup.add(validator.mReserve);
    mValidators.push_back(&validator);
  }
}

inline void Resource::Reserver::preventReservers() {
  for (vector<Resource *>::const_iterator resourceIt = resources().begin() ;
       resourceIt != resources().end() ;
       ++resourceIt) {
    Resource &resource = **resourceIt;

    resource.preventReservers();
  }
}

inline void Resource::Reserver::unpreventReservers() {
  for (vector<Resource *>::const_iterator resourceIt = resources().begin() ;
       resourceIt != resources().end() ;
       ++resourceIt) {
    Resource &resource = **resourceIt;

    resource.unpreventReservers();
  }
}

inline void Resource::Reserver::initialize() {
  mReserveGroup.initialize();
  mObservedReserveGroup.initialize();
}

inline bool Resource::Reserver::tryToReserve() {
  bool success = mReserveGroup.tryToLock();

  if (success) {
    // reserve specific action
    uponReservation();
    
    // let observed resources
    mObservedReserveGroup.unlock();
    
    // prevent other reservers from enqueuing 
    preventReservers();

    // update status of modified resources (FREE->RESERVED)
    for (vector<Resource *>::const_iterator resourceIt = resources().begin() ;
         resourceIt != resources().end() ;
         ++resourceIt) {
      Resource &resource = **resourceIt;

      assert(resource.status() == FREE);

      resource.setStatus(RESERVED);
    }

    // reset all impacted validators
    for (vector<Validator *>::const_iterator validatorIt = mValidators.begin() ;
         validatorIt != mValidators.end() ;
         ++validatorIt) {
      Validator &validator = **validatorIt;

      assert(validator.isValid());
      
      validator.reset(resources());
    }
  }

  return success;
}

inline void Resource::Reserver::free() {
  for (vector<Resource *>::const_iterator resourceIt = resources().begin() ;
       resourceIt != resources().end() ;
       ++resourceIt) {
    Resource &resource = **resourceIt;

    resource.free();
  }
}

inline void Resource::Reserver::start() {
  mBlocker.lock();
}

inline void Resource::Reserver::end() {
  mBlocker.unlock();
}

inline void Resource::Writer::addResource(Resource &resource) {
  if (find(mResources.begin(),
           mResources.end(),
           &resource)
      == mResources.end()) {
    mResources.push_back(&resource);
  }
  
  mReserveGroup.add(resource.mReserve);

  resource.addWriter(*this);
}

inline void Resource::Writer::free() {
  for (vector<Resource *>::const_iterator resourceIt = resources().begin() ;
       resourceIt != resources().end() ;
       ++resourceIt) {
    Resource &resource = **resourceIt;

    assert(resource.status() == RESERVED);

    resource.free();
  }
}

inline void Resource::Writer::start() {
  for (vector<Resource *>::const_iterator resourceIt = resources().begin() ;
       resourceIt != resources().end() ;
       ++resourceIt) {
    Resource &resource = **resourceIt;
    
    resource.use();
  }
}

inline void Resource::Writer::end() {
  for (vector<Resource *>::const_iterator resourceIt = resources().begin() ;
       resourceIt != resources().end() ;
       ++resourceIt) {
    Resource &resource = **resourceIt;
    
    assert(resource.status() == USED);

    resource.free();
  }
}

inline void Resource::Validator::addResource(Resource &resource) {
  if (find(mResources.begin(),
           mResources.end(),
           &resource)
      == mResources.end()) {
    mResources.push_back(&resource);
  }

  resource.addValidator(*this);

  for (vector<Reserver *>::const_iterator reserverIt = resource.reservers().begin() ;
       reserverIt != resource.reservers().end() ;
       ++reserverIt) {
    Reserver &reserver = **reserverIt;

    if (find(reserver.observedResources().begin(),
             reserver.observedResources().end(),
             &resource)
        == reserver.observedResources().end()) {
      assert(find(reserver.resources().begin(),
                  reserver.resources().end(),
                  &resource)
             != reserver.resources().end());
      reserver.mReserveGroup.add(mReserve);
    }
  }
}

inline void Resource::Validator::setIsValid(bool valid) {
  bool oldIsValid = mIsValid.exchange(valid);

  if (!oldIsValid && valid) {
    mReserve.unlock();

    for (vector<Resource *>::const_iterator resourceIt = resources().begin() ;
         resourceIt != resources().end() ;
         ++resourceIt) {
      Resource &resource = **resourceIt;

      resource.unpreventReservers();
    }
  }
  else if (oldIsValid && !valid) {
    for (vector<Resource *>::const_iterator resourceIt = resources().begin() ;
         resourceIt != resources().end() ;
         ++resourceIt) {
      Resource &resource = **resourceIt;

      resource.preventReservers();
    }
  }
}

#endif
