// // From Generated code. FIXME: we should give java location.

#include <TeaStoreVariation/AT__TeaStoreVariation__ServerMachine_xcore.hpp>

#include <iostream>
#include <sstream>

#include <CycleInAtomPrioritiesError.hpp>
#include <NonDeterministicPetriNetError.hpp>
#include <NonOneSafePetriNetError.hpp>
#include <AtomInvariantViolationError.hpp>


bool AT__TeaStoreVariation__ServerMachine_xcore::atINIT () const {
    return __statesbv[ 0/(8*sizeof(int))] & 1<< (0%(8*sizeof(int)));
}

bool AT__TeaStoreVariation__ServerMachine_xcore::toINIT () {
    if (atINIT()) return false;
    __statesbv[ 0/(8*sizeof(int))] |= 1<< (0%(8*sizeof(int)));
    return true;
}

bool AT__TeaStoreVariation__ServerMachine_xcore::fromINIT () {
    if (!atINIT()) return false;
    __statesbv[ 0/(8*sizeof(int))] &= ~(1<< (0%(8*sizeof(int))));
    return true;
}

bool AT__TeaStoreVariation__ServerMachine_xcore::atRECEIVE () const {
    return __statesbv[ 1/(8*sizeof(int))] & 1<< (1%(8*sizeof(int)));
}

bool AT__TeaStoreVariation__ServerMachine_xcore::toRECEIVE () {
    if (atRECEIVE()) return false;
    __statesbv[ 1/(8*sizeof(int))] |= 1<< (1%(8*sizeof(int)));
    return true;
}

bool AT__TeaStoreVariation__ServerMachine_xcore::fromRECEIVE () {
    if (!atRECEIVE()) return false;
    __statesbv[ 1/(8*sizeof(int))] &= ~(1<< (1%(8*sizeof(int))));
    return true;
}

bool AT__TeaStoreVariation__ServerMachine_xcore::atTHEN () const {
    return __statesbv[ 2/(8*sizeof(int))] & 1<< (2%(8*sizeof(int)));
}

bool AT__TeaStoreVariation__ServerMachine_xcore::toTHEN () {
    if (atTHEN()) return false;
    __statesbv[ 2/(8*sizeof(int))] |= 1<< (2%(8*sizeof(int)));
    return true;
}

bool AT__TeaStoreVariation__ServerMachine_xcore::fromTHEN () {
    if (!atTHEN()) return false;
    __statesbv[ 2/(8*sizeof(int))] &= ~(1<< (2%(8*sizeof(int))));
    return true;
}

bool AT__TeaStoreVariation__ServerMachine_xcore::atSEND () const {
    return __statesbv[ 3/(8*sizeof(int))] & 1<< (3%(8*sizeof(int)));
}

bool AT__TeaStoreVariation__ServerMachine_xcore::toSEND () {
    if (atSEND()) return false;
    __statesbv[ 3/(8*sizeof(int))] |= 1<< (3%(8*sizeof(int)));
    return true;
}

bool AT__TeaStoreVariation__ServerMachine_xcore::fromSEND () {
    if (!atSEND()) return false;
    __statesbv[ 3/(8*sizeof(int))] &= ~(1<< (3%(8*sizeof(int))));
    return true;
}

AT__TeaStoreVariation__ServerMachine_xcore::AT__TeaStoreVariation__ServerMachine_xcore(const string &name , AtomIPort__TeaStoreVariation__port_xt &_iport_decl__start_aipd, AtomIPort__TeaStoreVariation__port_xt &_iport_decl__then_aipd, AtomIPort__TeaStoreVariation__boolintintint_xport_xt &_iport_decl__send_aipd, AtomIPort__TeaStoreVariation__intintint_xport_xt &_iport_decl__recv_aipd
                         
                         , AtomEPort__TeaStoreVariation__boolintintint_xport_xt &_eport_decl__send_aepd, AtomEPort__TeaStoreVariation__intintint_xport_xt &_eport_decl__recv_aepd
                         
                         , bool _comp_param__starts) :  ComponentItf(name, ATOM), Atom(name) , _iport_decl__start_aipd(_iport_decl__start_aipd), _iport_decl_pv__start_aipd(), _iport_decl__then_aipd(_iport_decl__then_aipd), _iport_decl_pv__then_aipd(), _iport_decl__send_aipd(_iport_decl__send_aipd), _iport_decl_pv__send_aipd(_id__userAuth_aidd, _id__nbData_aidd, _id__userID_aidd, _id__fromServerToInternet_aidd), _iport_decl__recv_aipd(_iport_decl__recv_aipd), _iport_decl_pv__recv_aipd(_id__wpServed_aidd, _id__maxNbData_aidd, _id__fromInternet_aidd), _eport_decl__send_aepd(_eport_decl__send_aepd), _eport_decl__recv_aepd(_eport_decl__recv_aepd), _comp_param__starts(_comp_param__starts), _transguard__1(false), _transguard__2(false), _transguard__3(false), _transguard__4(false), _transguard__5(false), __previous(-1) {
    this->addInternalPort(_iport_decl__start_aipd);

    // link data internal to internal port
    this->addInternalPort(_iport_decl__then_aipd);

    // link data internal to internal port
    this->addInternalPort(_iport_decl__send_aipd);

    // link data internal to internal port
    this->addInternalPort(_iport_decl__recv_aipd);
    // export port
    this->addPort(_eport_decl__send_aepd);
    this->addPort(_eport_decl__recv_aepd);
}

BipError& AT__TeaStoreVariation__ServerMachine_xcore::execute(PortValue &portValue) {
    BipError *ret = &BipError::NoError;

#ifndef NDEBUG
    bool something_happened = false;
#endif

    // find the right transitions to execute
    if ((&_iport_decl_pv__start_aipd == &portValue) && _transguard__1) {
        // check consistency (enabledness, port values, ...)
        assert(_iport_decl__start_aipd.hasPortValue());
        assert(&_iport_decl__start_aipd.portValue() == &portValue);

        // check at most one transitions is executed
        assert(!something_happened);

        // the transition should be enabled by places
        assert(atINIT());

        // update input places
        fromINIT();

        // check one-safetyness
        if (atRECEIVE()) {
            NonOneSafePetriNetError *r = new NonOneSafePetriNetError(*this);
            r->setPort(_iport_decl__start_aipd);
            return *r;
        }

        // update output places
        toRECEIVE();

        // record the index of the latest executed transition
        __previous = 1;
// // From Generated code. FIXME: we should give java location.



        
#ifndef NDEBUG
        something_happened = true;
#endif
    } else if ((&_iport_decl_pv__start_aipd == &portValue) && _transguard__2) {
        // check consistency (enabledness, port values, ...)
        assert(_iport_decl__start_aipd.hasPortValue());
        assert(&_iport_decl__start_aipd.portValue() == &portValue);

        // check at most one transitions is executed
        assert(!something_happened);

        // the transition should be enabled by places
        assert(atINIT());

        // update input places
        fromINIT();

        // check one-safetyness
        if (atSEND()) {
            NonOneSafePetriNetError *r = new NonOneSafePetriNetError(*this);
            r->setPort(_iport_decl__start_aipd);
            return *r;
        }

        // update output places
        toSEND();

        // record the index of the latest executed transition
        __previous = 2;
// // From Generated code. FIXME: we should give java location.



        
#ifndef NDEBUG
        something_happened = true;
#endif
    } else if ((&_iport_decl_pv__recv_aipd == &portValue) && _transguard__3) {
        // check consistency (enabledness, port values, ...)
        assert(_iport_decl__recv_aipd.hasPortValue());
        assert(&_iport_decl__recv_aipd.portValue() == &portValue);

        // check at most one transitions is executed
        assert(!something_happened);

        // the transition should be enabled by places
        assert(atRECEIVE());

        // update input places
        fromRECEIVE();

        // check one-safetyness
        if (atTHEN()) {
            NonOneSafePetriNetError *r = new NonOneSafePetriNetError(*this);
            r->setPort(_iport_decl__recv_aipd);
            return *r;
        }

        // update output places
        toTHEN();

        // record the index of the latest executed transition
        __previous = 3;
// // From Generated code. FIXME: we should give java location.



        
#ifndef NDEBUG
        something_happened = true;
#endif
    } else if ((&_iport_decl_pv__then_aipd == &portValue) && _transguard__4) {
        // check consistency (enabledness, port values, ...)
        assert(_iport_decl__then_aipd.hasPortValue());
        assert(&_iport_decl__then_aipd.portValue() == &portValue);

        // check at most one transitions is executed
        assert(!something_happened);

        // the transition should be enabled by places
        assert(atTHEN());

        // update input places
        fromTHEN();

        // check one-safetyness
        if (atSEND()) {
            NonOneSafePetriNetError *r = new NonOneSafePetriNetError(*this);
            r->setPort(_iport_decl__then_aipd);
            return *r;
        }

        // update output places
        toSEND();

        // record the index of the latest executed transition
        __previous = 4;
// // From Generated code. FIXME: we should give java location.



        
#ifndef NDEBUG
        something_happened = true;
#endif
    } else if ((&_iport_decl_pv__send_aipd == &portValue) && _transguard__5) {
        // check consistency (enabledness, port values, ...)
        assert(_iport_decl__send_aipd.hasPortValue());
        assert(&_iport_decl__send_aipd.portValue() == &portValue);

        // check at most one transitions is executed
        assert(!something_happened);

        // the transition should be enabled by places
        assert(atSEND());

        // update input places
        fromSEND();

        // check one-safetyness
        if (atRECEIVE()) {
            NonOneSafePetriNetError *r = new NonOneSafePetriNetError(*this);
            r->setPort(_iport_decl__send_aipd);
            return *r;
        }

        // update output places
        toRECEIVE();

        // record the index of the latest executed transition
        __previous = 5;
// // From Generated code. FIXME: we should give java location.



        
#ifndef NDEBUG
        something_happened = true;
#endif
    }
    if (ret->type() != NO_ERROR) return *ret;

    // check that at least one transition has been executed
    assert(something_happened);

    // execute internal transitions
    ret = &executeInternalTransitions();

    if (ret->type() != NO_ERROR) return *ret;

    return update();
}

BipError& AT__TeaStoreVariation__ServerMachine_xcore::execute(AtomExternalPort &port) {
   BipError *ret = &BipError::NoError;

#ifndef NDEBUG
    bool something_happened = false;
#endif

    if (ret->type() != NO_ERROR) return *ret;

    // check that at least one transition has been executed
    assert(something_happened);

    // execute internal transitions
    ret = &executeInternalTransitions();

    if (ret->type() != NO_ERROR) return *ret;

    return update();
}

BipError& AT__TeaStoreVariation__ServerMachine_xcore::initialize() {
    BipError *ret = &BipError::NoError;
    
    // reset status of ports
    _iport_decl__start_aipd.clearPortValue();
    _iport_decl__then_aipd.clearPortValue();
    _iport_decl__send_aipd.clearPortValue();
    _iport_decl__recv_aipd.clearPortValue();

    // reset status of transitions
    _transguard__1 = false;
    _transguard__2 = false;
    _transguard__3 = false;
    _transguard__4 = false;
    _transguard__5 = false;

    // initialize to empty marking
    for (unsigned int idx = 0; idx < bvector_size; idx++){
        __statesbv[idx] = 0;
    }

    // marking must be initialized to empty
    assert((!atINIT()) && (!atRECEIVE()) && (!atTHEN()) && (!atSEND()));

    // update initial places
    toINIT();

    // record the index of the latest executed transition
    __previous = 0;




    if (ret->type() != NO_ERROR) return *ret;

    // execute (initial) internal transitions
    ret = &executeInternalTransitions();

    if (ret->type() != NO_ERROR) return *ret;

    return update();
}

string AT__TeaStoreVariation__ServerMachine_xcore::toString() const {
    ostringstream oss;
    bool first=true;
    if (atINIT()) {
      if (!first) oss << ", ";
      else {
        first = false;
        oss << "at ";
      }
      oss << "INIT";
    }
    if (atRECEIVE()) {
      if (!first) oss << ", ";
      else {
        first = false;
        oss << "at ";
      }
      oss << "RECEIVE";
    }
    if (atTHEN()) {
      if (!first) oss << ", ";
      else {
        first = false;
        oss << "at ";
      }
      oss << "THEN";
    }
    if (atSEND()) {
      if (!first) oss << ", ";
      else {
        first = false;
        oss << "at ";
      }
      oss << "SEND";
    }

    if (first) first = false;
    else oss << std::endl;
    oss << "starts=" << _comp_param__starts;
    if (first) first = false;
    else oss << std::endl;
    oss << "wpServed_aidd=" << _id__wpServed_aidd;
    if (first) first = false;
    else oss << std::endl;
    oss << "maxNbData_aidd=" << _id__maxNbData_aidd;
    if (first) first = false;
    else oss << std::endl;
    oss << "fromInternet_aidd=" << _id__fromInternet_aidd;
    if (first) first = false;
    else oss << std::endl;
    oss << "httpResponse_aidd=" << _id__httpResponse_aidd;
    if (first) first = false;
    else oss << std::endl;
    oss << "currentRequest_aidd=" << _id__currentRequest_aidd;
    if (first) first = false;
    else oss << std::endl;
    oss << "requestFound_aidd=" << _id__requestFound_aidd;
    if (first) first = false;
    else oss << std::endl;
    oss << "requestList_aidd=" << _id__requestList_aidd;
    if (first) first = false;
    else oss << std::endl;
    oss << "nbDataToOutput_aidd=" << _id__nbDataToOutput_aidd;
    if (first) first = false;
    else oss << std::endl;
    oss << "userIDToOutput_aidd=" << _id__userIDToOutput_aidd;
    if (first) first = false;
    else oss << std::endl;
    oss << "userAuthToOutput_aidd=" << _id__userAuthToOutput_aidd;
    if (first) first = false;
    else oss << std::endl;
    oss << "userAuth_aidd=" << _id__userAuth_aidd;
    if (first) first = false;
    else oss << std::endl;
    oss << "nbData_aidd=" << _id__nbData_aidd;
    if (first) first = false;
    else oss << std::endl;
    oss << "userID_aidd=" << _id__userID_aidd;
    if (first) first = false;
    else oss << std::endl;
    oss << "fromServerToInternet_aidd=" << _id__fromServerToInternet_aidd;

    return oss.str(); 
}

BipError& AT__TeaStoreVariation__ServerMachine_xcore::update() {
    BipError *ret = &BipError::NoError;

    

    return *ret;
}

BipError &AT__TeaStoreVariation__ServerMachine_xcore::executeInternalTransitions() {
    BipError &ret = BipError::NoError;

    // used to record the enabled internal transition
    int __enabled_internal = 0;

    do {
        // recompute enabled internal transitions
        __enabled_internal = 0;


        // execute the enabled internal transition if exist
        if (__enabled_internal != 0) {
            switch (__enabled_internal) {

              default:
                assert(false);
            }
        }
    } while (__enabled_internal != 0);

    return ret;
}

AT__TeaStoreVariation__ServerMachine_xcore::~AT__TeaStoreVariation__ServerMachine_xcore() {
}
