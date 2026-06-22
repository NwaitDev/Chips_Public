#ifndef TEASTOREVARIATION_AT____TEASTOREVARIATION____INT__XCONSTANT__XT_HPP_
#define TEASTOREVARIATION_AT____TEASTOREVARIATION____INT__XCONSTANT__XT_HPP_

// // From Generated code. FIXME: we should give java location.
// include package "master" header
#include <TeaStoreVariation.hpp>

#include <Atom.hpp>


#include <TeaStoreVariation/AtomIPort__TeaStoreVariation__int_xport_xt.hpp>


#include <TeaStoreVariation/AtomEPort__TeaStoreVariation__int_xport_xt.hpp>

#include <TeaStoreVariation/PV__TeaStoreVariation__int_xport_xt.hpp>



class AT__TeaStoreVariation__int_xconstant_xt : public Atom {
private:
   // internal ports & associated port values
    AtomIPort__TeaStoreVariation__int_xport_xt &_iport_decl__output_aipd;
    PV__TeaStoreVariation__int_xport_xt _iport_decl_pv__output_aipd;

    // exported ports
    AtomEPort__TeaStoreVariation__int_xport_xt &_eport_decl__output_aepd;
public:
    AT__TeaStoreVariation__int_xconstant_xt(const string &name , AtomIPort__TeaStoreVariation__int_xport_xt &_iport_decl__output_aipd
                             
                             , AtomEPort__TeaStoreVariation__int_xport_xt &_eport_decl__output_aepd
                             
                             );
    virtual ~AT__TeaStoreVariation__int_xconstant_xt();

    virtual BipError& execute(PortValue &portValue);
    virtual BipError& execute(AtomExternalPort &portValue);
    virtual BipError& initialize();
    virtual string toString() const;

protected:
    BipError& update();

    BipError& executeInternalTransitions();
    BipError& checkInvariants();

    const static size_t bvector_size = 1/(8*sizeof(int))+((1%(8*sizeof(int))) > 0 ? 1 : 0);
    int __statesbv[ bvector_size ];

    // component data declarations
    chips_int _id__int_value_aidd;

    // enabledness of transitions
    bool _transguard__1;

    // index of the latest executed transition
    int __previous;

    bool atDATA_SENDING() const;
    bool toDATA_SENDING();
    bool fromDATA_SENDING();
};

#endif // TEASTOREVARIATION_AT____TEASTOREVARIATION____INT__XCONSTANT__XT_HPP_
