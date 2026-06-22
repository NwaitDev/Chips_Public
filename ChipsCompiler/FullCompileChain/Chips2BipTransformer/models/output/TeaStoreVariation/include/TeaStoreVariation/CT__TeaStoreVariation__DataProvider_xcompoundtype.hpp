#ifndef TEASTOREVARIATION_CT____TEASTOREVARIATION____DATAPROVIDER__XCOMPOUNDTYPE_HPP_
#define TEASTOREVARIATION_CT____TEASTOREVARIATION____DATAPROVIDER__XCOMPOUNDTYPE_HPP_

// // From Generated code. FIXME: we should give java location.
// include package "master" header
#include <TeaStoreVariation.hpp>

#include <Compound.hpp>


// for component types
#include <TeaStoreVariation/CT__TeaStoreVariation__boolboolintint_xinput_xbuffer_xt.hpp>
#include <TeaStoreVariation/AT__TeaStoreVariation__DataProvider_xcore.hpp>
#include <TeaStoreVariation/CT__TeaStoreVariation__boolboolfloatintint_xoutput_xbuffer_xt.hpp>

// for connector types
#include <TeaStoreVariation/ConnT__TeaStoreVariation__flow_xboolboolfloatintint_xt.hpp>
#include <TeaStoreVariation/ConnT__TeaStoreVariation__flow_xboolboolintint_xt.hpp>


class CT__TeaStoreVariation__DataProvider_xcompoundtype : public Compound {
public:
    CT__TeaStoreVariation__DataProvider_xcompoundtype (const string &name, AT__TeaStoreVariation__DataProvider_xcore &_comp_decl__core
    ,
    CT__TeaStoreVariation__boolboolintint_xinput_xbuffer_xt &_comp_decl__DataProvider_input_buffer_buffercompounddecl, CT__TeaStoreVariation__boolboolfloatintint_xoutput_xbuffer_xt &_comp_decl__DataProvider_output_buffer_buffercompounddecl
                                  , ConnT__TeaStoreVariation__flow_xboolboolintint_xt &_conn_decl__input__to__core_cd, ConnT__TeaStoreVariation__flow_xboolboolfloatintint_xt &_conn_decl__core__to__output_cd
                                  
                                  
                                  
                                  , chips_bool _comp_param__starts_componentdataparameterdeclaration
    
    );
    virtual ~CT__TeaStoreVariation__DataProvider_xcompoundtype();


private:

    // SubComponent decls
    AT__TeaStoreVariation__DataProvider_xcore &_comp_decl__core;
    CT__TeaStoreVariation__boolboolintint_xinput_xbuffer_xt &_comp_decl__DataProvider_input_buffer_buffercompounddecl;
    CT__TeaStoreVariation__boolboolfloatintint_xoutput_xbuffer_xt &_comp_decl__DataProvider_output_buffer_buffercompounddecl;

    // connector decls
    ConnT__TeaStoreVariation__flow_xboolboolintint_xt &_conn_decl__input__to__core_cd;
    ConnT__TeaStoreVariation__flow_xboolboolfloatintint_xt &_conn_decl__core__to__output_cd;

    // component data parameters, read-only
    const chips_bool _comp_param__starts_componentdataparameterdeclaration;
};



#endif // TEASTOREVARIATION_CT____TEASTOREVARIATION____DATAPROVIDER__XCOMPOUNDTYPE_HPP_
