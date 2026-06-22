#ifndef TEASTOREVARIATION_AT____TEASTOREVARIATION____CACHE__XCORE_HPP_
#define TEASTOREVARIATION_AT____TEASTOREVARIATION____CACHE__XCORE_HPP_

// // From Generated code. FIXME: we should give java location.
// include package "master" header
#include <TeaStoreVariation.hpp>

#include <Atom.hpp>


#include <TeaStoreVariation/AtomIPort__TeaStoreVariation__port_xt.hpp>
#include <TeaStoreVariation/AtomIPort__TeaStoreVariation__intint_xport_xt.hpp>
#include <TeaStoreVariation/AtomIPort__TeaStoreVariation__bool_xport_xt.hpp>


#include <TeaStoreVariation/AtomEPort__TeaStoreVariation__bool_xport_xt.hpp>
#include <TeaStoreVariation/AtomEPort__TeaStoreVariation__intint_xport_xt.hpp>

#include <TeaStoreVariation/PV__TeaStoreVariation__bool_xport_xt.hpp>
#include <TeaStoreVariation/PV__TeaStoreVariation__intint_xport_xt.hpp>
#include <TeaStoreVariation/PV__TeaStoreVariation__port_xt.hpp>



class AT__TeaStoreVariation__Cache_xcore : public Atom {
private:
   // internal ports & associated port values
    AtomIPort__TeaStoreVariation__port_xt &_iport_decl__start_aipd;
    PV__TeaStoreVariation__port_xt _iport_decl_pv__start_aipd;
    AtomIPort__TeaStoreVariation__port_xt &_iport_decl__then_aipd;
    PV__TeaStoreVariation__port_xt _iport_decl_pv__then_aipd;
    AtomIPort__TeaStoreVariation__bool_xport_xt &_iport_decl__send_aipd;
    PV__TeaStoreVariation__bool_xport_xt _iport_decl_pv__send_aipd;
    AtomIPort__TeaStoreVariation__intint_xport_xt &_iport_decl__recv_aipd;
    PV__TeaStoreVariation__intint_xport_xt _iport_decl_pv__recv_aipd;

    // exported ports
    AtomEPort__TeaStoreVariation__bool_xport_xt &_eport_decl__send_aepd;
    AtomEPort__TeaStoreVariation__intint_xport_xt &_eport_decl__recv_aepd;
public:
    AT__TeaStoreVariation__Cache_xcore(const string &name , AtomIPort__TeaStoreVariation__port_xt &_iport_decl__start_aipd, AtomIPort__TeaStoreVariation__port_xt &_iport_decl__then_aipd, AtomIPort__TeaStoreVariation__bool_xport_xt &_iport_decl__send_aipd, AtomIPort__TeaStoreVariation__intint_xport_xt &_iport_decl__recv_aipd
                             
                             , AtomEPort__TeaStoreVariation__bool_xport_xt &_eport_decl__send_aepd, AtomEPort__TeaStoreVariation__intint_xport_xt &_eport_decl__recv_aepd
                             
                             , bool _comp_param__starts);
    virtual ~AT__TeaStoreVariation__Cache_xcore();

    virtual BipError& execute(PortValue &portValue);
    virtual BipError& execute(AtomExternalPort &portValue);
    virtual BipError& initialize();
    virtual string toString() const;

protected:
    BipError& update();

    BipError& executeInternalTransitions();
    BipError& checkInvariants();

    const static size_t bvector_size = 4/(8*sizeof(int))+((4%(8*sizeof(int))) > 0 ? 1 : 0);
    int __statesbv[ bvector_size ];

    // component data declarations
    const bool _comp_param__starts;
    chips_int _id__requestedData_aidd;
    chips_int _id__cacheSize_aidd;
    chips_int _id__maxCacheSize_aidd;
    chips_int _id__minCacheSize_aidd;
    chips_int _id__cache_aidd;
    chips_int _id__newestDataIndex_aidd;
    chips_bool _id__found_aidd;
    chips_int _id__foundIndex_aidd;
    chips_bool _id__foundInCache_aidd;

    // enabledness of transitions
    bool _transguard__1;
    bool _transguard__2;
    bool _transguard__3;
    bool _transguard__4;
    bool _transguard__5;

    // index of the latest executed transition
    int __previous;

    bool atINIT() const;
    bool toINIT();
    bool fromINIT();
    bool atRECEIVE() const;
    bool toRECEIVE();
    bool fromRECEIVE();
    bool atTHEN() const;
    bool toTHEN();
    bool fromTHEN();
    bool atSEND() const;
    bool toSEND();
    bool fromSEND();
};

#endif // TEASTOREVARIATION_AT____TEASTOREVARIATION____CACHE__XCORE_HPP_
