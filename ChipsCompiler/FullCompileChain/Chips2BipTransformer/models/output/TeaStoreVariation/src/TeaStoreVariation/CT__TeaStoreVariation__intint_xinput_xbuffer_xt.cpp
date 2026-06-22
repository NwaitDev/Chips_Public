// // From Generated code. FIXME: we should give java location.

#include <TeaStoreVariation/CT__TeaStoreVariation__intint_xinput_xbuffer_xt.hpp>

CT__TeaStoreVariation__intint_xinput_xbuffer_xt::CT__TeaStoreVariation__intint_xinput_xbuffer_xt (const string &name, AT__TeaStoreVariation__int_xbuffer_xt &_comp_decl__requestedData_bd, AT__TeaStoreVariation__int_xbuffer_xt &_comp_decl__cacheSize_bd
                              , ConnT__TeaStoreVariation__many2one_xintint_xt &_conn_decl__intint_input_connector
                              
                              , CpndEPort__TeaStoreVariation__int_xport_xt &_eport_decl__requestedData_exin_cepd, CpndEPort__TeaStoreVariation__int_xport_xt &_eport_decl__cacheSize_exin_cepd, CpndEPort__TeaStoreVariation__intint_xport_xt &_eport_decl__one_cepd
                              
                              

) : ComponentItf(name, COMPOUND), Compound(name), _comp_decl__requestedData_bd(_comp_decl__requestedData_bd), _comp_decl__cacheSize_bd(_comp_decl__cacheSize_bd), _conn_decl__intint_input_connector(_conn_decl__intint_input_connector), _eport_decl__requestedData_exin_cepd(_eport_decl__requestedData_exin_cepd), _eport_decl__cacheSize_exin_cepd(_eport_decl__cacheSize_exin_cepd), _eport_decl__one_cepd(_eport_decl__one_cepd) {
    this->addComponent(_comp_decl__requestedData_bd);
    this->addComponent(_comp_decl__cacheSize_bd);
    this->addConnector(_conn_decl__intint_input_connector);
    this->addPort(_eport_decl__requestedData_exin_cepd);
    this->addPort(_eport_decl__cacheSize_exin_cepd);
    this->addPort(_eport_decl__one_cepd);
}

CT__TeaStoreVariation__intint_xinput_xbuffer_xt::~CT__TeaStoreVariation__intint_xinput_xbuffer_xt() {
}
