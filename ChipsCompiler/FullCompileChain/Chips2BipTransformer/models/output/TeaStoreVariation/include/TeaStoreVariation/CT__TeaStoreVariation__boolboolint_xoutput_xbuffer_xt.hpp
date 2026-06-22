#ifndef TEASTOREVARIATION_CT____TEASTOREVARIATION____BOOLBOOLINT__XOUTPUT__XBUFFER__XT_HPP_
#define TEASTOREVARIATION_CT____TEASTOREVARIATION____BOOLBOOLINT__XOUTPUT__XBUFFER__XT_HPP_

// // From Generated code. FIXME: we should give java location.
// include package "master" header
#include <TeaStoreVariation.hpp>

#include <Compound.hpp>


// for component types
#include <TeaStoreVariation/AT__TeaStoreVariation__bool_xbuffer_xt.hpp>
#include <TeaStoreVariation/AT__TeaStoreVariation__int_xbuffer_xt.hpp>

// for connector types
#include </ConnT__java__lang__Object@98025e0__many2one_xboolboolint_xt.hpp>

// for exported ports
#include <TeaStoreVariation/CpndEPort__TeaStoreVariation__bool_xport_xt.hpp>
#include <TeaStoreVariation/CpndEPort__TeaStoreVariation__int_xport_xt.hpp>
#include <TeaStoreVariation/CpndEPort__TeaStoreVariation__boolboolint_xport_xt.hpp>


class CT__TeaStoreVariation__boolboolint_xoutput_xbuffer_xt : public Compound {
public:
    CT__TeaStoreVariation__boolboolint_xoutput_xbuffer_xt (const string &name, AT__TeaStoreVariation__bool_xbuffer_xt &_comp_decl__reqAuth_bd, AT__TeaStoreVariation__bool_xbuffer_xt &_comp_decl__isNewPage_bd, AT__TeaStoreVariation__int_xbuffer_xt &_comp_decl__idToRespondTo_bd
                                  , ConnT__java__lang__Object@98025e0__many2one_xboolboolint_xt &_conn_decl__boolboolint_input_connector
                                  
                                  , CpndEPort__TeaStoreVariation__bool_xport_xt &_eport_decl__reqAuth_exout_cepd, CpndEPort__TeaStoreVariation__bool_xport_xt &_eport_decl__isNewPage_exout_cepd, CpndEPort__TeaStoreVariation__int_xport_xt &_eport_decl__idToRespondTo_exout_cepd, CpndEPort__TeaStoreVariation__boolboolint_xport_xt &_eport_decl__one_cepd
                                  
                                  
    
    );
    virtual ~CT__TeaStoreVariation__boolboolint_xoutput_xbuffer_xt();


private:

    // SubComponent decls
    AT__TeaStoreVariation__bool_xbuffer_xt &_comp_decl__reqAuth_bd;
    AT__TeaStoreVariation__bool_xbuffer_xt &_comp_decl__isNewPage_bd;
    AT__TeaStoreVariation__int_xbuffer_xt &_comp_decl__idToRespondTo_bd;

    // connector decls
    ConnT__java__lang__Object@98025e0__many2one_xboolboolint_xt &_conn_decl__boolboolint_input_connector;

    // export port decl
    CpndEPort__TeaStoreVariation__bool_xport_xt &_eport_decl__reqAuth_exout_cepd;
    CpndEPort__TeaStoreVariation__bool_xport_xt &_eport_decl__isNewPage_exout_cepd;
    CpndEPort__TeaStoreVariation__int_xport_xt &_eport_decl__idToRespondTo_exout_cepd;
    CpndEPort__TeaStoreVariation__boolboolint_xport_xt &_eport_decl__one_cepd;
};



#endif // TEASTOREVARIATION_CT____TEASTOREVARIATION____BOOLBOOLINT__XOUTPUT__XBUFFER__XT_HPP_
