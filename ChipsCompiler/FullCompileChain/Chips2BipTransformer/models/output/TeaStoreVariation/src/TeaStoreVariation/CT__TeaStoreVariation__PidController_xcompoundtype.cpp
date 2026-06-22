// // From Generated code. FIXME: we should give java location.

#include <TeaStoreVariation/CT__TeaStoreVariation__PidController_xcompoundtype.hpp>

CT__TeaStoreVariation__PidController_xcompoundtype::CT__TeaStoreVariation__PidController_xcompoundtype (const string &name, AT__TeaStoreVariation__PidController_xcore &_comp_decl__core
,
CT__TeaStoreVariation__boolfloatfloat_xinput_xbuffer_xt &_comp_decl__PidController_input_buffer_buffercompounddecl, CT__TeaStoreVariation__int_xoutput_xbuffer_xt &_comp_decl__PidController_output_buffer_buffercompounddecl
                              , ConnT__TeaStoreVariation__flow_xboolfloatfloat_xt &_conn_decl__input__to__core_cd, ConnT__TeaStoreVariation__flow_xint_xt &_conn_decl__core__to__output_cd
                              
                              
                              
                              , chips_bool _comp_param__starts_componentdataparameterdeclaration

) : ComponentItf(name, COMPOUND), Compound(name), _comp_decl__core(_comp_decl__core), _comp_decl__PidController_input_buffer_buffercompounddecl(_comp_decl__PidController_input_buffer_buffercompounddecl), _comp_decl__PidController_output_buffer_buffercompounddecl(_comp_decl__PidController_output_buffer_buffercompounddecl), _conn_decl__input__to__core_cd(_conn_decl__input__to__core_cd), _conn_decl__core__to__output_cd(_conn_decl__core__to__output_cd), _comp_param__starts_componentdataparameterdeclaration(_comp_param__starts_componentdataparameterdeclaration) {
    this->addComponent(_comp_decl__core);
    this->addComponent(_comp_decl__PidController_input_buffer_buffercompounddecl);
    this->addComponent(_comp_decl__PidController_output_buffer_buffercompounddecl);
    this->addConnector(_conn_decl__input__to__core_cd);
    this->addConnector(_conn_decl__core__to__output_cd);
}

CT__TeaStoreVariation__PidController_xcompoundtype::~CT__TeaStoreVariation__PidController_xcompoundtype() {
}
