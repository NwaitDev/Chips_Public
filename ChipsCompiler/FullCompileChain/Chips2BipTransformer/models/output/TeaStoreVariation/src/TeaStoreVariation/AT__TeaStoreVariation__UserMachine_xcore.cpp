// // From Generated code. FIXME: we should give java location.

#include <TeaStoreVariation/AT__TeaStoreVariation__UserMachine_xcore.hpp>

#include <iostream>
#include <sstream>

#include <CycleInAtomPrioritiesError.hpp>
#include <NonDeterministicPetriNetError.hpp>
#include <NonOneSafePetriNetError.hpp>
#include <AtomInvariantViolationError.hpp>


bool AT__TeaStoreVariation__UserMachine_xcore::atINIT () const {
    return __statesbv[ 0/(8*sizeof(int))] & 1<< (0%(8*sizeof(int)));
}

bool AT__TeaStoreVariation__UserMachine_xcore::toINIT () {
    if (atINIT()) return false;
    __statesbv[ 0/(8*sizeof(int))] |= 1<< (0%(8*sizeof(int)));
    return true;
}

bool AT__TeaStoreVariation__UserMachine_xcore::fromINIT () {
    if (!atINIT()) return false;
    __statesbv[ 0/(8*sizeof(int))] &= ~(1<< (0%(8*sizeof(int))));
    return true;
}

bool AT__TeaStoreVariation__UserMachine_xcore::atRECEIVE () const {
    return __statesbv[ 1/(8*sizeof(int))] & 1<< (1%(8*sizeof(int)));
}

bool AT__TeaStoreVariation__UserMachine_xcore::toRECEIVE () {
    if (atRECEIVE()) return false;
    __statesbv[ 1/(8*sizeof(int))] |= 1<< (1%(8*sizeof(int)));
    return true;
}

bool AT__TeaStoreVariation__UserMachine_xcore::fromRECEIVE () {
    if (!atRECEIVE()) return false;
    __statesbv[ 1/(8*sizeof(int))] &= ~(1<< (1%(8*sizeof(int))));
    return true;
}

bool AT__TeaStoreVariation__UserMachine_xcore::atTHEN () const {
    return __statesbv[ 2/(8*sizeof(int))] & 1<< (2%(8*sizeof(int)));
}

bool AT__TeaStoreVariation__UserMachine_xcore::toTHEN () {
    if (atTHEN()) return false;
    __statesbv[ 2/(8*sizeof(int))] |= 1<< (2%(8*sizeof(int)));
    return true;
}

bool AT__TeaStoreVariation__UserMachine_xcore::fromTHEN () {
    if (!atTHEN()) return false;
    __statesbv[ 2/(8*sizeof(int))] &= ~(1<< (2%(8*sizeof(int))));
    return true;
}

bool AT__TeaStoreVariation__UserMachine_xcore::atSEND () const {
    return __statesbv[ 3/(8*sizeof(int))] & 1<< (3%(8*sizeof(int)));
}

bool AT__TeaStoreVariation__UserMachine_xcore::toSEND () {
    if (atSEND()) return false;
    __statesbv[ 3/(8*sizeof(int))] |= 1<< (3%(8*sizeof(int)));
    return true;
}

bool AT__TeaStoreVariation__UserMachine_xcore::fromSEND () {
    if (!atSEND()) return false;
    __statesbv[ 3/(8*sizeof(int))] &= ~(1<< (3%(8*sizeof(int))));
    return true;
}

bool AT__TeaStoreVariation__UserMachine_xcore::atREADCTX () const {
    return __statesbv[ 4/(8*sizeof(int))] & 1<< (4%(8*sizeof(int)));
}

bool AT__TeaStoreVariation__UserMachine_xcore::toREADCTX () {
    if (atREADCTX()) return false;
    __statesbv[ 4/(8*sizeof(int))] |= 1<< (4%(8*sizeof(int)));
    return true;
}

bool AT__TeaStoreVariation__UserMachine_xcore::fromREADCTX () {
    if (!atREADCTX()) return false;
    __statesbv[ 4/(8*sizeof(int))] &= ~(1<< (4%(8*sizeof(int))));
    return true;
}

bool AT__TeaStoreVariation__UserMachine_xcore::atWRITECTX () const {
    return __statesbv[ 5/(8*sizeof(int))] & 1<< (5%(8*sizeof(int)));
}

bool AT__TeaStoreVariation__UserMachine_xcore::toWRITECTX () {
    if (atWRITECTX()) return false;
    __statesbv[ 5/(8*sizeof(int))] |= 1<< (5%(8*sizeof(int)));
    return true;
}

bool AT__TeaStoreVariation__UserMachine_xcore::fromWRITECTX () {
    if (!atWRITECTX()) return false;
    __statesbv[ 5/(8*sizeof(int))] &= ~(1<< (5%(8*sizeof(int))));
    return true;
}

AT__TeaStoreVariation__UserMachine_xcore::AT__TeaStoreVariation__UserMachine_xcore(const string &name , AtomIPort__TeaStoreVariation__port_xt &_iport_decl__start_aipd, AtomIPort__TeaStoreVariation__port_xt &_iport_decl__then_aipd, AtomIPort__TeaStoreVariation__int_xport_xt &_iport_decl__send_aipd, AtomIPort__TeaStoreVariation__intintintintint_xport_xt &_iport_decl__recv_aipd, AtomIPort__TeaStoreVariation__int_xport_xt &_iport_decl__read_ctx_aipd, AtomIPort__TeaStoreVariation__int_xport_xt &_iport_decl__write_ctx_aipd
                         
                         , AtomEPort__TeaStoreVariation__int_xport_xt &_eport_decl__send_aepd, AtomEPort__TeaStoreVariation__intintintintint_xport_xt &_eport_decl__recv_aepd, AtomEPort__TeaStoreVariation__int_xport_xt &_eport_decl__read_ctx_aepd, AtomEPort__TeaStoreVariation__int_xport_xt &_eport_decl__write_ctx_aepd
                         
                         , bool _comp_param__starts) :  ComponentItf(name, ATOM), Atom(name) , _iport_decl__start_aipd(_iport_decl__start_aipd), _iport_decl_pv__start_aipd(), _iport_decl__then_aipd(_iport_decl__then_aipd), _iport_decl_pv__then_aipd(), _iport_decl__send_aipd(_iport_decl__send_aipd), _iport_decl_pv__send_aipd(_id__fromUserToInternet_aidd), _iport_decl__recv_aipd(_iport_decl__recv_aipd), _iport_decl_pv__recv_aipd(_id__startTime_aidd, _id__endTime_aidd, _id__id_aidd, _id__maxNbData_aidd, _id__httpResponse_aidd), _iport_decl__read_ctx_aipd(_iport_decl__read_ctx_aipd), _iport_decl_pv__read_ctx_aipd(), _iport_decl__write_ctx_aipd(_iport_decl__write_ctx_aipd), _iport_decl_pv__write_ctx_aipd(_id__computerID_aidd), _eport_decl__send_aepd(_eport_decl__send_aepd), _eport_decl__recv_aepd(_eport_decl__recv_aepd), _eport_decl__read_ctx_aepd(_eport_decl__read_ctx_aepd), _eport_decl__write_ctx_aepd(_eport_decl__write_ctx_aepd), _comp_param__starts(_comp_param__starts), _transguard__1(false), _transguard__2(false), _transguard__3(false), _transguard__4(false), _transguard__5(false), _transguard__6(false), _transguard__7(false), __previous(-1) {
    this->addInternalPort(_iport_decl__start_aipd);

    // link data internal to internal port
    this->addInternalPort(_iport_decl__then_aipd);

    // link data internal to internal port
    this->addInternalPort(_iport_decl__send_aipd);

    // link data internal to internal port
    this->addInternalPort(_iport_decl__recv_aipd);

    // link data internal to internal port
    this->addInternalPort(_iport_decl__read_ctx_aipd);

    // link data internal to internal port
    this->addInternalPort(_iport_decl__write_ctx_aipd);
    // export port
    this->addPort(_eport_decl__send_aepd);
    this->addPort(_eport_decl__recv_aepd);
    this->addPort(_eport_decl__read_ctx_aepd);
    this->addPort(_eport_decl__write_ctx_aepd);
}

BipError& AT__TeaStoreVariation__UserMachine_xcore::execute(PortValue &portValue) {
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
        if (atREADCTX()) {
            NonOneSafePetriNetError *r = new NonOneSafePetriNetError(*this);
            r->setPort(_iport_decl__recv_aipd);
            return *r;
        }

        // update output places
        toREADCTX();

        // record the index of the latest executed transition
        __previous = 3;
// // From Generated code. FIXME: we should give java location.



        
#ifndef NDEBUG
        something_happened = true;
#endif
    } else if ((&_iport_decl_pv__read_ctx_aipd == &portValue) && _transguard__4) {
        // check consistency (enabledness, port values, ...)
        assert(_iport_decl__read_ctx_aipd.hasPortValue());
        assert(&_iport_decl__read_ctx_aipd.portValue() == &portValue);

        // check at most one transitions is executed
        assert(!something_happened);

        // the transition should be enabled by places
        assert(atREADCTX());

        // update input places
        fromREADCTX();

        // check one-safetyness
        if (atTHEN()) {
            NonOneSafePetriNetError *r = new NonOneSafePetriNetError(*this);
            r->setPort(_iport_decl__read_ctx_aipd);
            return *r;
        }

        // update output places
        toTHEN();

        // record the index of the latest executed transition
        __previous = 4;
// // From Generated code. FIXME: we should give java location.



        
#ifndef NDEBUG
        something_happened = true;
#endif
    } else if ((&_iport_decl_pv__then_aipd == &portValue) && _transguard__5) {
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
        if (atWRITECTX()) {
            NonOneSafePetriNetError *r = new NonOneSafePetriNetError(*this);
            r->setPort(_iport_decl__then_aipd);
            return *r;
        }

        // update output places
        toWRITECTX();

        // record the index of the latest executed transition
        __previous = 5;
// // From Generated code. FIXME: we should give java location.



        
#ifndef NDEBUG
        something_happened = true;
#endif
    } else if ((&_iport_decl_pv__write_ctx_aipd == &portValue) && _transguard__6) {
        // check consistency (enabledness, port values, ...)
        assert(_iport_decl__write_ctx_aipd.hasPortValue());
        assert(&_iport_decl__write_ctx_aipd.portValue() == &portValue);

        // check at most one transitions is executed
        assert(!something_happened);

        // the transition should be enabled by places
        assert(atWRITECTX());

        // update input places
        fromWRITECTX();

        // check one-safetyness
        if (atSEND()) {
            NonOneSafePetriNetError *r = new NonOneSafePetriNetError(*this);
            r->setPort(_iport_decl__write_ctx_aipd);
            return *r;
        }

        // update output places
        toSEND();

        // record the index of the latest executed transition
        __previous = 6;
// // From Generated code. FIXME: we should give java location.



        
#ifndef NDEBUG
        something_happened = true;
#endif
    } else if ((&_iport_decl_pv__send_aipd == &portValue) && _transguard__7) {
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
        __previous = 7;
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

BipError& AT__TeaStoreVariation__UserMachine_xcore::execute(AtomExternalPort &port) {
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

BipError& AT__TeaStoreVariation__UserMachine_xcore::initialize() {
    BipError *ret = &BipError::NoError;
    
    // reset status of ports
    _iport_decl__start_aipd.clearPortValue();
    _iport_decl__then_aipd.clearPortValue();
    _iport_decl__send_aipd.clearPortValue();
    _iport_decl__recv_aipd.clearPortValue();
    _iport_decl__read_ctx_aipd.clearPortValue();
    _iport_decl__write_ctx_aipd.clearPortValue();

    // reset status of transitions
    _transguard__1 = false;
    _transguard__2 = false;
    _transguard__3 = false;
    _transguard__4 = false;
    _transguard__5 = false;
    _transguard__6 = false;
    _transguard__7 = false;

    // initialize to empty marking
    for (unsigned int idx = 0; idx < bvector_size; idx++){
        __statesbv[idx] = 0;
    }

    // marking must be initialized to empty
    assert((!atINIT()) && (!atRECEIVE()) && (!atTHEN()) && (!atSEND()) && (!atREADCTX()) && (!atWRITECTX()));

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

string AT__TeaStoreVariation__UserMachine_xcore::toString() const {
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
    if (atREADCTX()) {
      if (!first) oss << ", ";
      else {
        first = false;
        oss << "at ";
      }
      oss << "READCTX";
    }
    if (atWRITECTX()) {
      if (!first) oss << ", ";
      else {
        first = false;
        oss << "at ";
      }
      oss << "WRITECTX";
    }

    if (first) first = false;
    else oss << std::endl;
    oss << "starts=" << _comp_param__starts;
    if (first) first = false;
    else oss << std::endl;
    oss << "startTime_aidd=" << _id__startTime_aidd;
    if (first) first = false;
    else oss << std::endl;
    oss << "endTime_aidd=" << _id__endTime_aidd;
    if (first) first = false;
    else oss << std::endl;
    oss << "id_aidd=" << _id__id_aidd;
    if (first) first = false;
    else oss << std::endl;
    oss << "maxNbData_aidd=" << _id__maxNbData_aidd;
    if (first) first = false;
    else oss << std::endl;
    oss << "httpResponse_aidd=" << _id__httpResponse_aidd;
    if (first) first = false;
    else oss << std::endl;
    oss << "computerID_aidd=" << _id__computerID_aidd;
    if (first) first = false;
    else oss << std::endl;
    oss << "active_aidd=" << _id__active_aidd;
    if (first) first = false;
    else oss << std::endl;
    oss << "waiting_aidd=" << _id__waiting_aidd;
    if (first) first = false;
    else oss << std::endl;
    oss << "time_aidd=" << _id__time_aidd;
    if (first) first = false;
    else oss << std::endl;
    oss << "requiresAuth_aidd=" << _id__requiresAuth_aidd;
    if (first) first = false;
    else oss << std::endl;
    oss << "newPage_aidd=" << _id__newPage_aidd;
    if (first) first = false;
    else oss << std::endl;
    oss << "currentRequest_aidd=" << _id__currentRequest_aidd;
    if (first) first = false;
    else oss << std::endl;
    oss << "httpRequest_aidd=" << _id__httpRequest_aidd;
    if (first) first = false;
    else oss << std::endl;
    oss << "lastRequest_aidd=" << _id__lastRequest_aidd;
    if (first) first = false;
    else oss << std::endl;
    oss << "fromUserToInternet_aidd=" << _id__fromUserToInternet_aidd;

    return oss.str(); 
}

BipError& AT__TeaStoreVariation__UserMachine_xcore::update() {
    BipError *ret = &BipError::NoError;

    // update status of internal/external ports w.r.t. transitions
    // reset status of port read_ctx_aipd
    this->_iport_decl__read_ctx_aipd.setIsEnabled(false);
    
    _transguard__4 = (atREADCTX()
    // // From Generated code. FIXME: we should give java location.
                && (true));
    
    if (_transguard__4) {
        if (_iport_decl__read_ctx_aipd.isEnabled()) {
            NonDeterministicPetriNetError *r = new NonDeterministicPetriNetError(*this);
            r->setPort(_iport_decl__read_ctx_aipd);
        
            return *r;
        }
        
        _iport_decl__read_ctx_aipd.setIsEnabled(true);
    }
    
    // reset status of port start_aipd
    this->_iport_decl__start_aipd.setIsEnabled(false);
    
    _transguard__1 = (atINIT()
    // // From Generated code. FIXME: we should give java location.
                && (true));
    
    if (_transguard__1) {
        if (_iport_decl__start_aipd.isEnabled()) {
            NonDeterministicPetriNetError *r = new NonDeterministicPetriNetError(*this);
            r->setPort(_iport_decl__start_aipd);
        
            return *r;
        }
        
        _iport_decl__start_aipd.setIsEnabled(true);
    }
    _transguard__2 = (atINIT()
    // // From Generated code. FIXME: we should give java location.
                && (true));
    
    if (_transguard__2) {
        if (_iport_decl__start_aipd.isEnabled()) {
            NonDeterministicPetriNetError *r = new NonDeterministicPetriNetError(*this);
            r->setPort(_iport_decl__start_aipd);
        
            return *r;
        }
        
        _iport_decl__start_aipd.setIsEnabled(true);
    }
    
    // reset status of port recv_aipd
    this->_iport_decl__recv_aipd.setIsEnabled(false);
    
    _transguard__3 = (atRECEIVE()
    // // From Generated code. FIXME: we should give java location.
                && (true));
    
    if (_transguard__3) {
        if (_iport_decl__recv_aipd.isEnabled()) {
            NonDeterministicPetriNetError *r = new NonDeterministicPetriNetError(*this);
            r->setPort(_iport_decl__recv_aipd);
        
            return *r;
        }
        
        _iport_decl__recv_aipd.setIsEnabled(true);
    }
    
    // reset status of port then_aipd
    this->_iport_decl__then_aipd.setIsEnabled(false);
    
    _transguard__5 = (atTHEN()
    // // From Generated code. FIXME: we should give java location.
                && (true));
    
    if (_transguard__5) {
        if (_iport_decl__then_aipd.isEnabled()) {
            NonDeterministicPetriNetError *r = new NonDeterministicPetriNetError(*this);
            r->setPort(_iport_decl__then_aipd);
        
            return *r;
        }
        
        _iport_decl__then_aipd.setIsEnabled(true);
    }
    
    // reset status of port write_ctx_aipd
    this->_iport_decl__write_ctx_aipd.setIsEnabled(false);
    
    _transguard__6 = (atWRITECTX()
    // // From Generated code. FIXME: we should give java location.
                && (true));
    
    if (_transguard__6) {
        if (_iport_decl__write_ctx_aipd.isEnabled()) {
            NonDeterministicPetriNetError *r = new NonDeterministicPetriNetError(*this);
            r->setPort(_iport_decl__write_ctx_aipd);
        
            return *r;
        }
        
        _iport_decl__write_ctx_aipd.setIsEnabled(true);
    }
    
    // reset status of port send_aipd
    this->_iport_decl__send_aipd.setIsEnabled(false);
    
    _transguard__7 = (atSEND()
    // // From Generated code. FIXME: we should give java location.
                && (true));
    
    if (_transguard__7) {
        if (_iport_decl__send_aipd.isEnabled()) {
            NonDeterministicPetriNetError *r = new NonDeterministicPetriNetError(*this);
            r->setPort(_iport_decl__send_aipd);
        
            return *r;
        }
        
        _iport_decl__send_aipd.setIsEnabled(true);
    }
    // recompute modified priority paths
    
    // applies priorities to port start_aipd
    
    // recompute modified priority paths
    
    // applies priorities to port then_aipd
    
    // recompute modified priority paths
    
    // applies priorities to port send_aipd
    
    // recompute modified priority paths
    
    // applies priorities to port recv_aipd
    
    // recompute modified priority paths
    
    // applies priorities to port read_ctx_aipd
    
    // recompute modified priority paths
    
    // applies priorities to port write_ctx_aipd
    
    // update port value of start_aipd
    if (this->_iport_decl__start_aipd.isEnabled() && !this->_iport_decl__start_aipd.isDisabledByPriorities()) {
        this->_iport_decl__start_aipd.setPortValue(_iport_decl_pv__start_aipd);
    }
    else {
        this->_iport_decl__start_aipd.clearPortValue();
    }
    
    // update port value of then_aipd
    if (this->_iport_decl__then_aipd.isEnabled() && !this->_iport_decl__then_aipd.isDisabledByPriorities()) {
        this->_iport_decl__then_aipd.setPortValue(_iport_decl_pv__then_aipd);
    }
    else {
        this->_iport_decl__then_aipd.clearPortValue();
    }
    
    // update port value of send_aipd
    if (this->_iport_decl__send_aipd.isEnabled() && !this->_iport_decl__send_aipd.isDisabledByPriorities()) {
        this->_iport_decl__send_aipd.setPortValue(_iport_decl_pv__send_aipd);
    }
    else {
        this->_iport_decl__send_aipd.clearPortValue();
    }
    
    // update port value of recv_aipd
    if (this->_iport_decl__recv_aipd.isEnabled() && !this->_iport_decl__recv_aipd.isDisabledByPriorities()) {
        this->_iport_decl__recv_aipd.setPortValue(_iport_decl_pv__recv_aipd);
    }
    else {
        this->_iport_decl__recv_aipd.clearPortValue();
    }
    
    // update port value of read_ctx_aipd
    if (this->_iport_decl__read_ctx_aipd.isEnabled() && !this->_iport_decl__read_ctx_aipd.isDisabledByPriorities()) {
        this->_iport_decl__read_ctx_aipd.setPortValue(_iport_decl_pv__read_ctx_aipd);
    }
    else {
        this->_iport_decl__read_ctx_aipd.clearPortValue();
    }
    
    // update port value of write_ctx_aipd
    if (this->_iport_decl__write_ctx_aipd.isEnabled() && !this->_iport_decl__write_ctx_aipd.isDisabledByPriorities()) {
        this->_iport_decl__write_ctx_aipd.setPortValue(_iport_decl_pv__write_ctx_aipd);
    }
    else {
        this->_iport_decl__write_ctx_aipd.clearPortValue();
    }
    
    // force recomputation of connectors involving send_aepd
    _eport_decl__send_aepd.setIsReset(true);
    
    // recompute port values of send_aepd from scratch
    this->_eport_decl__send_aepd.portValues().clear();
    
    // check port value of send_aipd exported by send_aepd
    if (this->_iport_decl__send_aipd.hasPortValue()) {
        this->_eport_decl__send_aepd.addPortValue(_iport_decl_pv__send_aipd);
    }
    
    // force recomputation of connectors involving recv_aepd
    _eport_decl__recv_aepd.setIsReset(true);
    
    // recompute port values of recv_aepd from scratch
    this->_eport_decl__recv_aepd.portValues().clear();
    
    // check port value of recv_aipd exported by recv_aepd
    if (this->_iport_decl__recv_aipd.hasPortValue()) {
        this->_eport_decl__recv_aepd.addPortValue(_iport_decl_pv__recv_aipd);
    }
    
    // force recomputation of connectors involving read_ctx_aepd
    _eport_decl__read_ctx_aepd.setIsReset(true);
    
    // recompute port values of read_ctx_aepd from scratch
    this->_eport_decl__read_ctx_aepd.portValues().clear();
    
    // check port value of read_ctx_aipd exported by read_ctx_aepd
    if (this->_iport_decl__read_ctx_aipd.hasPortValue()) {
        this->_eport_decl__read_ctx_aepd.addPortValue(_iport_decl_pv__read_ctx_aipd);
    }
    
    // force recomputation of connectors involving write_ctx_aepd
    _eport_decl__write_ctx_aepd.setIsReset(true);
    
    // recompute port values of write_ctx_aepd from scratch
    this->_eport_decl__write_ctx_aepd.portValues().clear();
    
    // check port value of write_ctx_aipd exported by write_ctx_aepd
    if (this->_iport_decl__write_ctx_aipd.hasPortValue()) {
        this->_eport_decl__write_ctx_aepd.addPortValue(_iport_decl_pv__write_ctx_aipd);
    }

    return *ret;
}

BipError &AT__TeaStoreVariation__UserMachine_xcore::executeInternalTransitions() {
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

AT__TeaStoreVariation__UserMachine_xcore::~AT__TeaStoreVariation__UserMachine_xcore() {
}
