#ifndef TEASTOREVARIATION_AT____TEASTOREVARIATION____PIDCONTROLLER__XCORE_HPP_
#define TEASTOREVARIATION_AT____TEASTOREVARIATION____PIDCONTROLLER__XCORE_HPP_

// // From Generated code. FIXME: we should give java location.
// include package "master" header
#include <TeaStoreVariation.hpp>

#include <Atom.hpp>


#include <TeaStoreVariation/AtomIPort__TeaStoreVariation__port_xt.hpp>
#include <TeaStoreVariation/AtomIPort__TeaStoreVariation__boolfloatfloat_xport_xt.hpp>
#include <TeaStoreVariation/AtomIPort__TeaStoreVariation__int_xport_xt.hpp>


#include <TeaStoreVariation/AtomEPort__TeaStoreVariation__boolfloatfloat_xport_xt.hpp>
#include <TeaStoreVariation/AtomEPort__TeaStoreVariation__int_xport_xt.hpp>

#include <TeaStoreVariation/PV__TeaStoreVariation__port_xt.hpp>
#include <TeaStoreVariation/PV__TeaStoreVariation__int_xport_xt.hpp>
#include <TeaStoreVariation/PV__TeaStoreVariation__boolfloatfloat_xport_xt.hpp>



class AT__TeaStoreVariation__PidController_xcore : public Atom {
private:
   // internal ports & associated port values
    AtomIPort__TeaStoreVariation__port_xt &_iport_decl__start_aipd;
    PV__TeaStoreVariation__port_xt _iport_decl_pv__start_aipd;
    AtomIPort__TeaStoreVariation__port_xt &_iport_decl__then_aipd;
    PV__TeaStoreVariation__port_xt _iport_decl_pv__then_aipd;
    AtomIPort__TeaStoreVariation__int_xport_xt &_iport_decl__send_aipd;
    PV__TeaStoreVariation__int_xport_xt _iport_decl_pv__send_aipd;
    AtomIPort__TeaStoreVariation__boolfloatfloat_xport_xt &_iport_decl__recv_aipd;
    PV__TeaStoreVariation__boolfloatfloat_xport_xt _iport_decl_pv__recv_aipd;

    // exported ports
    AtomEPort__TeaStoreVariation__int_xport_xt &_eport_decl__send_aepd;
    AtomEPort__TeaStoreVariation__boolfloatfloat_xport_xt &_eport_decl__recv_aepd;
public:
    AT__TeaStoreVariation__PidController_xcore(const string &name , AtomIPort__TeaStoreVariation__port_xt &_iport_decl__start_aipd, AtomIPort__TeaStoreVariation__port_xt &_iport_decl__then_aipd, AtomIPort__TeaStoreVariation__int_xport_xt &_iport_decl__send_aipd, AtomIPort__TeaStoreVariation__boolfloatfloat_xport_xt &_iport_decl__recv_aipd
                             
                             , AtomEPort__TeaStoreVariation__int_xport_xt &_eport_decl__send_aepd, AtomEPort__TeaStoreVariation__boolfloatfloat_xport_xt &_eport_decl__recv_aepd
                             
                             , bool _comp_param__starts);
    virtual ~AT__TeaStoreVariation__PidController_xcore();

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
    chips_bool _id__enabled_aidd;
    chips_float _id__requested__time_aidd;
    chips_float _id__resulting__time_aidd;
    chips_float _id__derivative_aidd;
    chips_float _id__integral_aidd;
    chips_float _id__error_aidd;
    chips_float _id__dt_aidd;
    chips_float _id__p_aidd;
    chips_float _id__i_aidd;
    chips_float _id__d_aidd;
    chips_int _id__knob__value_aidd;
    chips_int _id__min__knob__value_aidd;
    chips_int _id__max__knob__value_aidd;
    chips_int _id__knob_aidd;

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

#endif // TEASTOREVARIATION_AT____TEASTOREVARIATION____PIDCONTROLLER__XCORE_HPP_
