// // From Generated code. FIXME: we should give java location.

#include <TeaStoreVariation/AT__TeaStoreVariation__int_xbuffer_xt.hpp>

#include <iostream>
#include <sstream>

#include <CycleInAtomPrioritiesError.hpp>
#include <NonDeterministicPetriNetError.hpp>
#include <NonOneSafePetriNetError.hpp>
#include <AtomInvariantViolationError.hpp>


bool AT__TeaStoreVariation__int_xbuffer_xt::atDATA_RECEIVING () const {
    return __statesbv[ 0/(8*sizeof(int))] & 1<< (0%(8*sizeof(int)));
}

bool AT__TeaStoreVariation__int_xbuffer_xt::toDATA_RECEIVING () {
    if (atDATA_RECEIVING()) return false;
    __statesbv[ 0/(8*sizeof(int))] |= 1<< (0%(8*sizeof(int)));
    return true;
}

bool AT__TeaStoreVariation__int_xbuffer_xt::fromDATA_RECEIVING () {
    if (!atDATA_RECEIVING()) return false;
    __statesbv[ 0/(8*sizeof(int))] &= ~(1<< (0%(8*sizeof(int))));
    return true;
}

bool AT__TeaStoreVariation__int_xbuffer_xt::atDATA_SENDING () const {
    return __statesbv[ 1/(8*sizeof(int))] & 1<< (1%(8*sizeof(int)));
}

bool AT__TeaStoreVariation__int_xbuffer_xt::toDATA_SENDING () {
    if (atDATA_SENDING()) return false;
    __statesbv[ 1/(8*sizeof(int))] |= 1<< (1%(8*sizeof(int)));
    return true;
}

bool AT__TeaStoreVariation__int_xbuffer_xt::fromDATA_SENDING () {
    if (!atDATA_SENDING()) return false;
    __statesbv[ 1/(8*sizeof(int))] &= ~(1<< (1%(8*sizeof(int))));
    return true;
}

AT__TeaStoreVariation__int_xbuffer_xt::AT__TeaStoreVariation__int_xbuffer_xt(const string &name , AtomIPort__TeaStoreVariation__int_xport_xt &_iport_decl__in, AtomIPort__TeaStoreVariation__int_xport_xt &_iport_decl__out
                         
                         , AtomEPort__TeaStoreVariation__int_xport_xt &_eport_decl__exp_in, AtomEPort__TeaStoreVariation__int_xport_xt &_eport_decl__exp_out
                         
                         ) :  ComponentItf(name, ATOM), Atom(name) , _iport_decl__in(_iport_decl__in), _iport_decl_pv__in(), _iport_decl__out(_iport_decl__out), _iport_decl_pv__out(_id__int_data), _eport_decl__exp_in(_eport_decl__exp_in), _eport_decl__exp_out(_eport_decl__exp_out), _transguard__1(false), _transguard__2(false), __previous(-1) {
    this->addInternalPort(_iport_decl__in);

    // link data internal to internal port
    this->addInternalPort(_iport_decl__out);
    // export port
    this->addPort(_eport_decl__exp_in);
    this->addPort(_eport_decl__exp_out);
}

BipError& AT__TeaStoreVariation__int_xbuffer_xt::execute(PortValue &portValue) {
    BipError *ret = &BipError::NoError;

#ifndef NDEBUG
    bool something_happened = false;
#endif

    // find the right transitions to execute
    if ((&_iport_decl_pv__out == &portValue) && _transguard__1) {
        // check consistency (enabledness, port values, ...)
        assert(_iport_decl__out.hasPortValue());
        assert(&_iport_decl__out.portValue() == &portValue);

        // check at most one transitions is executed
        assert(!something_happened);

        // the transition should be enabled by places
        assert(atDATA_SENDING());

        // update input places
        fromDATA_SENDING();

        // check one-safetyness
        if (atDATA_RECEIVING()) {
            NonOneSafePetriNetError *r = new NonOneSafePetriNetError(*this);
            r->setPort(_iport_decl__out);
            return *r;
        }

        // update output places
        toDATA_RECEIVING();

        // record the index of the latest executed transition
        __previous = 1;
// // From Generated code. FIXME: we should give java location.



        
#ifndef NDEBUG
        something_happened = true;
#endif
    } else if ((&_iport_decl_pv__in == &portValue) && _transguard__2) {
        // check consistency (enabledness, port values, ...)
        assert(_iport_decl__in.hasPortValue());
        assert(&_iport_decl__in.portValue() == &portValue);

        // check at most one transitions is executed
        assert(!something_happened);

        // the transition should be enabled by places
        assert(atDATA_RECEIVING());

        // update input places
        fromDATA_RECEIVING();

        // check one-safetyness
        if (atDATA_SENDING()) {
            NonOneSafePetriNetError *r = new NonOneSafePetriNetError(*this);
            r->setPort(_iport_decl__in);
            return *r;
        }

        // update output places
        toDATA_SENDING();

        // record the index of the latest executed transition
        __previous = 2;
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

BipError& AT__TeaStoreVariation__int_xbuffer_xt::execute(AtomExternalPort &port) {
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

BipError& AT__TeaStoreVariation__int_xbuffer_xt::initialize() {
    BipError *ret = &BipError::NoError;
    
    // reset status of ports
    _iport_decl__in.clearPortValue();
    _iport_decl__out.clearPortValue();

    // reset status of transitions
    _transguard__1 = false;
    _transguard__2 = false;

    // initialize to empty marking
    for (unsigned int idx = 0; idx < bvector_size; idx++){
        __statesbv[idx] = 0;
    }

    // marking must be initialized to empty
    assert((!atDATA_RECEIVING()) && (!atDATA_SENDING()));

    // update initial places
    toDATA_RECEIVING();

    // record the index of the latest executed transition
    __previous = 0;




    if (ret->type() != NO_ERROR) return *ret;

    // execute (initial) internal transitions
    ret = &executeInternalTransitions();

    if (ret->type() != NO_ERROR) return *ret;

    return update();
}

string AT__TeaStoreVariation__int_xbuffer_xt::toString() const {
    ostringstream oss;
    bool first=true;
    if (atDATA_RECEIVING()) {
      if (!first) oss << ", ";
      else {
        first = false;
        oss << "at ";
      }
      oss << "DATA_RECEIVING";
    }
    if (atDATA_SENDING()) {
      if (!first) oss << ", ";
      else {
        first = false;
        oss << "at ";
      }
      oss << "DATA_SENDING";
    }

    if (first) first = false;
    else oss << std::endl;
    oss << "int_data=" << _id__int_data;

    return oss.str(); 
}

BipError& AT__TeaStoreVariation__int_xbuffer_xt::update() {
    BipError *ret = &BipError::NoError;

    // update status of internal/external ports w.r.t. transitions
    // reset status of port in
    this->_iport_decl__in.setIsEnabled(false);
    
    _transguard__2 = (atDATA_RECEIVING()
    
                );
    
    if (_transguard__2) {
        if (_iport_decl__in.isEnabled()) {
            NonDeterministicPetriNetError *r = new NonDeterministicPetriNetError(*this);
            r->setPort(_iport_decl__in);
        
            return *r;
        }
        
        _iport_decl__in.setIsEnabled(true);
    }
    
    // reset status of port out
    this->_iport_decl__out.setIsEnabled(false);
    
    _transguard__1 = (atDATA_SENDING()
    
                );
    
    if (_transguard__1) {
        if (_iport_decl__out.isEnabled()) {
            NonDeterministicPetriNetError *r = new NonDeterministicPetriNetError(*this);
            r->setPort(_iport_decl__out);
        
            return *r;
        }
        
        _iport_decl__out.setIsEnabled(true);
    }
    // recompute modified priority paths
    
    // applies priorities to port in
    
    // recompute modified priority paths
    
    // applies priorities to port out
    
    // update port value of in
    if (this->_iport_decl__in.isEnabled() && !this->_iport_decl__in.isDisabledByPriorities()) {
        this->_iport_decl__in.setPortValue(_iport_decl_pv__in);
    }
    else {
        this->_iport_decl__in.clearPortValue();
    }
    
    // update port value of out
    if (this->_iport_decl__out.isEnabled() && !this->_iport_decl__out.isDisabledByPriorities()) {
        this->_iport_decl__out.setPortValue(_iport_decl_pv__out);
    }
    else {
        this->_iport_decl__out.clearPortValue();
    }
    
    // force recomputation of connectors involving exp_in
    _eport_decl__exp_in.setIsReset(true);
    
    // recompute port values of exp_in from scratch
    this->_eport_decl__exp_in.portValues().clear();
    
    // check port value of in exported by exp_in
    if (this->_iport_decl__in.hasPortValue()) {
        this->_eport_decl__exp_in.addPortValue(_iport_decl_pv__in);
    }
    
    // force recomputation of connectors involving exp_out
    _eport_decl__exp_out.setIsReset(true);
    
    // recompute port values of exp_out from scratch
    this->_eport_decl__exp_out.portValues().clear();
    
    // check port value of out exported by exp_out
    if (this->_iport_decl__out.hasPortValue()) {
        this->_eport_decl__exp_out.addPortValue(_iport_decl_pv__out);
    }

    return *ret;
}

BipError &AT__TeaStoreVariation__int_xbuffer_xt::executeInternalTransitions() {
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

AT__TeaStoreVariation__int_xbuffer_xt::~AT__TeaStoreVariation__int_xbuffer_xt() {
}
