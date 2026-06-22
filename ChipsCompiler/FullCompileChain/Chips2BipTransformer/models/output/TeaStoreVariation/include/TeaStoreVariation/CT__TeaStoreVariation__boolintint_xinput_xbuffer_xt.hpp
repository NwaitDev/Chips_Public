#ifndef TEASTOREVARIATION_CT____TEASTOREVARIATION____BOOLINTINT__XINPUT__XBUFFER__XT_HPP_
#define TEASTOREVARIATION_CT____TEASTOREVARIATION____BOOLINTINT__XINPUT__XBUFFER__XT_HPP_

// // From Generated code. FIXME: we should give java location.
// include package "master" header
#include <TeaStoreVariation.hpp>

#include <Compound.hpp>


// for component types
#include <TeaStoreVariation/AT__TeaStoreVariation__bool_xbuffer_xt.hpp>
#include <TeaStoreVariation/AT__TeaStoreVariation__int_xbuffer_xt.hpp>

// for connector types
#include <TeaStoreVariation/ConnT__TeaStoreVariation__many2one_xboolintint_xt.hpp>

// for exported ports
#include <TeaStoreVariation/CpndEPort__TeaStoreVariation__bool_xport_xt.hpp>
#include <TeaStoreVariation/CpndEPort__TeaStoreVariation__boolintint_xport_xt.hpp>
#include <TeaStoreVariation/CpndEPort__TeaStoreVariation__int_xport_xt.hpp>


class CT__TeaStoreVariation__boolintint_xinput_xbuffer_xt : public Compound {
public:
    CT__TeaStoreVariation__boolintint_xinput_xbuffer_xt (const string &name, AT__TeaStoreVariation__bool_xbuffer_xt &_comp_decl__isAuthenticated_bd, AT__TeaStoreVariation__int_xbuffer_xt &_comp_decl__nbData_bd, AT__TeaStoreVariation__int_xbuffer_xt &_comp_decl__requestID_bd
                                  , ConnT__TeaStoreVariation__many2one_xboolintint_xt &_conn_decl__boolintint_input_connector
                                  
                                  , CpndEPort__TeaStoreVariation__bool_xport_xt &_eport_decl__isAuthenticated_exin_cepd, CpndEPort__TeaStoreVariation__int_xport_xt &_eport_decl__nbData_exin_cepd, CpndEPort__TeaStoreVariation__int_xport_xt &_eport_decl__requestID_exin_cepd, CpndEPort__TeaStoreVariation__boolintint_xport_xt &_eport_decl__one_cepd
                                  
                                  
    
    );
    virtual ~CT__TeaStoreVariation__boolintint_xinput_xbuffer_xt();


private:

    // SubComponent decls
    AT__TeaStoreVariation__bool_xbuffer_xt &_comp_decl__isAuthenticated_bd;
    AT__TeaStoreVariation__int_xbuffer_xt &_comp_decl__nbData_bd;
    AT__TeaStoreVariation__int_xbuffer_xt &_comp_decl__requestID_bd;

    // connector decls
    ConnT__TeaStoreVariation__many2one_xboolintint_xt &_conn_decl__boolintint_input_connector;

    // export port decl
    CpndEPort__TeaStoreVariation__bool_xport_xt &_eport_decl__isAuthenticated_exin_cepd;
    CpndEPort__TeaStoreVariation__int_xport_xt &_eport_decl__nbData_exin_cepd;
    CpndEPort__TeaStoreVariation__int_xport_xt &_eport_decl__requestID_exin_cepd;
    CpndEPort__TeaStoreVariation__boolintint_xport_xt &_eport_decl__one_cepd;
};



#endif // TEASTOREVARIATION_CT____TEASTOREVARIATION____BOOLINTINT__XINPUT__XBUFFER__XT_HPP_
