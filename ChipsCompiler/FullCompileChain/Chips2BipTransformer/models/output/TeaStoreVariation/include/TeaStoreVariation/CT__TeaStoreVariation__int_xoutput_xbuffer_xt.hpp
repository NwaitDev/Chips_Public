#ifndef TEASTOREVARIATION_CT____TEASTOREVARIATION____INT__XOUTPUT__XBUFFER__XT_HPP_
#define TEASTOREVARIATION_CT____TEASTOREVARIATION____INT__XOUTPUT__XBUFFER__XT_HPP_

// // From Generated code. FIXME: we should give java location.
// include package "master" header
#include <TeaStoreVariation.hpp>

#include <Compound.hpp>


// for component types
#include <TeaStoreVariation/AT__TeaStoreVariation__int_xbuffer_xt.hpp>

// for connector types
#include </ConnT____many2one_xint_xt.hpp>

// for exported ports
#include <TeaStoreVariation/CpndEPort__TeaStoreVariation__int_xport_xt.hpp>


class CT__TeaStoreVariation__int_xoutput_xbuffer_xt : public Compound {
public:
    CT__TeaStoreVariation__int_xoutput_xbuffer_xt (const string &name, AT__TeaStoreVariation__int_xbuffer_xt &_comp_decl__knob_bd
                                  , ConnT____many2one_xint_xt &_conn_decl__int_input_connector
                                  
                                  , CpndEPort__TeaStoreVariation__int_xport_xt &_eport_decl__knob_exout_cepd, CpndEPort__TeaStoreVariation__int_xport_xt &_eport_decl__one_cepd
                                  
                                  
    
    );
    virtual ~CT__TeaStoreVariation__int_xoutput_xbuffer_xt();


private:

    // SubComponent decls
    AT__TeaStoreVariation__int_xbuffer_xt &_comp_decl__knob_bd;

    // connector decls
    ConnT____many2one_xint_xt &_conn_decl__int_input_connector;

    // export port decl
    CpndEPort__TeaStoreVariation__int_xport_xt &_eport_decl__knob_exout_cepd;
    CpndEPort__TeaStoreVariation__int_xport_xt &_eport_decl__one_cepd;
};



#endif // TEASTOREVARIATION_CT____TEASTOREVARIATION____INT__XOUTPUT__XBUFFER__XT_HPP_
