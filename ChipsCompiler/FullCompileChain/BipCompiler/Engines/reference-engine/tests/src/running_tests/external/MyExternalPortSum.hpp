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

#ifndef _MY_EXTERNAL_PORT_SUM_
#define _MY_EXTERNAL_PORT_SUM_

#include <AtomExternalPort.hpp>
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include <signal.h>

#include <thread>
#include <mutex>

using namespace std;

#define BUFFER_SIZE 32768

inline
void customsleep() {
  timespec delay;

  delay.tv_sec = 0;
  // /!\ WARNING: to work properly
  // external_error needs this value to
  // be greater than the maximal sleep 
  // in spinning!
  delay.tv_nsec = 100000000;

  nanosleep(&delay, NULL);
}

class MyExternalPortSum : public AtomExternalPort {
 public:
  MyExternalPortSum(const string &name, const EventConsumptionPolicy &policy) :
    AtomExternalPort(name, policy),
    readIndex(0),
    writeIndex(0) {
  }
  virtual ~MyExternalPortSum() {
  }

  virtual bool hasEvent() const {
    mtx.lock(); // pthread_mutex_lock(&mutex);
    bool ret = (readIndex != writeIndex);
    mtx.unlock(); // pthread_mutex_unlock(&mutex);

    return ret;
  }
  virtual void popEvent() { pop();  }
  virtual void purgeEvents() { purge(); }
  virtual void initialize() { start(); }

  virtual int &lastEvent_get_x() {
    mtx.lock(); // pthread_mutex_lock(&mutex);
    int &ret = m_x[readIndex];
    mtx.unlock(); // pthread_mutex_unlock(&mutex);
    return ret;
  }

  void start() {
    // pthread_create(&pid, NULL, spinning, this);
    spin = new thread(MyExternalPortSum::spinning, this);
  }

 protected:
  static void spinning(MyExternalPortSum *port) {
    sigset_t maskUSR1;
    sigemptyset(&maskUSR1);
    sigaddset(&maskUSR1, SIGUSR1);
    
    pthread_sigmask(SIG_BLOCK, &maskUSR1, NULL);

    timespec delay;

    delay.tv_sec = 0;
    delay.tv_nsec = 0;

    int burst = 0;
  
    for (int i = 1, n = 0 ; i <= 100 ; ++i) {
      if (burst == 0) {
        delay.tv_nsec = (long) 10000000 * (rand() / (RAND_MAX + 1.0));
        nanosleep(&delay, NULL);
        burst = (int) 10 * (rand() / (RAND_MAX + 1.0));
      }
      else {
        burst = burst - 1;
      }

      n += i;
      port->push(n);
    }
  }

  void purge() {
    mtx.lock(); //pthread_mutex_lock(&mutex);

    readIndex = writeIndex;

    mtx.unlock(); //pthread_mutex_unlock(&mutex);
  }

  void push(int v) {
    mtx.lock(); // pthread_mutex_lock(&mutex);

    m_x[writeIndex] = v;
 
    writeIndex = (writeIndex + 1) % BUFFER_SIZE;

    notify();

    mtx.unlock(); // pthread_mutex_unlock(&mutex);
  }

  int pop() {
    mtx.lock(); // pthread_mutex_lock(&mutex);

    int ret = m_x[readIndex];
 
    readIndex = (readIndex + 1) % BUFFER_SIZE;

    mtx.unlock(); // pthread_mutex_unlock(&mutex);

    return ret;
  }

  int m_x[BUFFER_SIZE];

  int readIndex;
  int writeIndex;

  //mutable pthread_mutex_t mutex;
  mutable mutex mtx;
  pthread_t pid;
  thread *spin;
};



#endif

