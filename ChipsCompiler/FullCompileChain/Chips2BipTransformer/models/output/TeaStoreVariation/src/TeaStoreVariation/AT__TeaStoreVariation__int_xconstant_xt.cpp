// // From Generated code. FIXME: we should give java location.

#include <TeaStoreVariation/AT__TeaStoreVariation__int_xconstant_xt.hpp>

#include <iostream>
#include <sstream>

#include <CycleInAtomPrioritiesError.hpp>
#include <NonDeterministicPetriNetError.hpp>
#include <NonOneSafePetriNetError.hpp>
#include <AtomInvariantViolationError.hpp>


bool AT__TeaStoreVariation__int_xconstant_xt::atDATA_SENDING () const {
    return __statesbv[ 0/(8*sizeof(int))] & 1<< (0%(8*sizeof(int)));
}

bool AT__TeaStoreVariation__int_xconstant_xt::toDATA_SENDING () {
    if (atDATA_SENDING()) return false;
    __statesbv[ 0/(8*sizeof(int))] |= 1<< (0%(8*sizeof(int)));
    return true;
}

bool AT__TeaStoreVariation__int_xconstant_xt::fromDATA_SENDING () {
    if (!atDATA_SENDING()) return false;
    __statesbv[ 0/(8*sizeof(int))] &= ~(1<< (0%(8*sizeof(int))));
    return true;
}

AT__TeaStoreVariation__int_xconstant_xt::AT__TeaStoreVariation__int_xconstant_xt(const string &name , AtomIPort__TeaStoreVariation__int_xport_xt &_iport_decl__output_aipd
                         
                         , AtomEPort__TeaStoreVariation__int_xport_xt &_eport_decl__output_aepd
                         
                         ) :  ComponentItf(name, ATOM), Atom(name) , _iport_decl__output_aipd(_iport_decl__output_aipd), _iport_decl_pv__output_aipd(_id__int_value_aidd), _eport_decl__output_aepd(_eport_decl__output_aepd), _transguard__1(false), __previous(-1) {
    this->addInternalPort(_iport_decl__output_aipd);
    // export port
    this->addPort(_eport_decl__output_aepd);
}

BipError& AT__TeaStoreVariation__int_xconstant_xt::execute(PortValue &portValue) {
    BipError *ret = &BipError::NoError;

#ifndef NDEBUG
    bool something_happened = false;
#endif

    // find the right transitions to execute
    if ((&_iport_decl_pv__output_aipd == &portValue) && _transguard__1) {
        // check consistency (enabledness, port values, ...)
        assert(_iport_decl__output_aipd.hasPortValue());
        assert(&_iport_decl__output_aipd.portValue() == &portValue);

        // check at most one transitions is executed
        assert(!something_happened);

        // the transition should be enabled by places
        assert(atDATA_SENDING());

        // update input places
        fromDATA_SENDING();

        // check one-safetyness
        if (atDATA_SENDING()) {
            NonOneSafePetriNetError *r = new NonOneSafePetriNetError(*this);
            r->setPort(_iport_decl__output_aipd);
            return *r;
        }

        // update output places
        toDATA_SENDING();

        // record the index of the latest executed transition
        __previous = 1;
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

BipError& AT__TeaStoreVariation__int_xconstant_xt::execute(AtomExternalPort &port) {
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

BipError& AT__TeaStoreVariation__int_xconstant_xt::initialize() {
    BipError *ret = &BipError::NoError;
    
    // reset status of ports
    _iport_decl__output_aipd.clearPortValue();

    // reset status of transitions
    _transguard__1 = false;

    // initialize to empty marking
    for (unsigned int idx = 0; idx < bvector_size; idx++){
        __statesbv[idx] = 0;
    }

    // marking must be initialized to empty
    assert((!atDATA_SENDING()));

    // update initial places
    toDATA_SENDING();

    // record the index of the latest executed transition
    __previous = 0;




    if (ret->type() != NO_ERROR) return *ret;

    // execute (initial) internal transitions
    ret = &executeInternalTransitions();

    if (ret->type() != NO_ERROR) return *ret;

    return update();
}

string AT__TeaStoreVariation__int_xconstant_xt::toString() const {
    ostringstream oss;
    bool first=true;
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
    oss << "int_value_aidd=" << _id__int_value_aidd;

    return oss.str(); 
}

BipError& AT__TeaStoreVariation__int_xconstant_xt::update() {
    BipError *ret = &BipError::NoError;

    // update status of internal/external ports w.r.t. transitions
    // reset status of port output_aipd
    this->_iport_decl__output_aipd.setIsEnabled(false);
    
    _transguard__1 = (atDATA_SENDING()
    
                );
    
    if (_transguard__1) {
        if (_iport_decl__output_aipd.isEnabled()) {
            NonDeterministicPetriNetError *r = new NonDeterministicPetriNetError(*this);
            r->setPort(_iport_decl__output_aipd);
        
            return *r;
        }
        
        _iport_decl__output_aipd.setIsEnabled(true);
    }
    // recompute modified priority paths
    
    // applies priorities to port output_aipd
    
    // update port value of output_aipd
    if (this->_iport_decl__output_aipd.isEnabled() && !this->_iport_decl__output_aipd.isDisabledByPriorities()) {
        this->_iport_decl__output_aipd.setPortValue(_iport_decl_pv__output_aipd);
    }
    else {
        this->_iport_decl__output_aipd.clearPortValue();
    }
    
    // force recomputation of connectors involving output_aepd
    _eport_decl__output_aepd.setIsReset(true);
    
    // recompute port values of output_aepd from scratch
    this->_eport_decl__output_aepd.portValues().clear();
    
    // check port value of output_aipd exported by output_aepd
    if (this->_iport_decl__output_aipd.hasPortValue()) {
        this->_eport_decl__output_aepd.addPortValue(_iport_decl_pv__output_aipd);
    }

    return *ret;
}

BipError &AT__TeaStoreVariation__int_xconstant_xt::executeInternalTransitions() {
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

AT__TeaStoreVariation__int_xconstant_xt::~AT__TeaStoreVariation__int_xconstant_xt() {
}
