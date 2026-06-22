#ifndef TEASTOREVARIATION_CT____TEASTOREVARIATION____SERVERMACHINE__XCOMPOUNDTYPE_HPP_
#define TEASTOREVARIATION_CT____TEASTOREVARIATION____SERVERMACHINE__XCOMPOUNDTYPE_HPP_

// // From Generated code. FIXME: we should give java location.
// include package "master" header
#include <TeaStoreVariation.hpp>

#include <Compound.hpp>


// for component types
#include <TeaStoreVariation/CT__TeaStoreVariation__intintint_xinput_xbuffer_xt.hpp>
#include <TeaStoreVariation/CT__TeaStoreVariation__boolintintint_xoutput_xbuffer_xt.hpp>
#include <TeaStoreVariation/AT__TeaStoreVariation__ServerMachine_xcore.hpp>

// for connector types
#include <TeaStoreVariation/ConnT__TeaStoreVariation__flow_xboolintintint_xt.hpp>
#include <TeaStoreVariation/ConnT__TeaStoreVariation__flow_xintintint_xt.hpp>


class CT__TeaStoreVariation__ServerMachine_xcompoundtype : public Compound {
public:
    CT__TeaStoreVariation__ServerMachine_xcompoundtype (const string &name, AT__TeaStoreVariation__ServerMachine_xcore &_comp_decl__core
    ,
    CT__TeaStoreVariation__intintint_xinput_xbuffer_xt &_comp_decl__ServerMachine_input_buffer_buffercompounddecl, CT__TeaStoreVariation__boolintintint_xoutput_xbuffer_xt &_comp_decl__ServerMachine_output_buffer_buffercompounddecl
                                  , ConnT__TeaStoreVariation__flow_xintintint_xt &_conn_decl__input__to__core_cd, ConnT__TeaStoreVariation__flow_xboolintintint_xt &_conn_decl__core__to__output_cd
                                  
                                  
                                  
                                  , chips_bool _comp_param__starts_componentdataparameterdeclaration
    
    );
    virtual ~CT__TeaStoreVariation__ServerMachine_xcompoundtype();


private:

    // SubComponent decls
    AT__TeaStoreVariation__ServerMachine_xcore &_comp_decl__core;
    CT__TeaStoreVariation__intintint_xinput_xbuffer_xt &_comp_decl__ServerMachine_input_buffer_buffercompounddecl;
    CT__TeaStoreVariation__boolintintint_xoutput_xbuffer_xt &_comp_decl__ServerMachine_output_buffer_buffercompounddecl;

    // connector decls
    ConnT__TeaStoreVariation__flow_xintintint_xt &_conn_decl__input__to__core_cd;
    ConnT__TeaStoreVariation__flow_xboolintintint_xt &_conn_decl__core__to__output_cd;

    // component data parameters, read-only
    const chips_bool _comp_param__starts_componentdataparameterdeclaration;
};



#endif // TEASTOREVARIATION_CT____TEASTOREVARIATION____SERVERMACHINE__XCOMPOUNDTYPE_HPP_
