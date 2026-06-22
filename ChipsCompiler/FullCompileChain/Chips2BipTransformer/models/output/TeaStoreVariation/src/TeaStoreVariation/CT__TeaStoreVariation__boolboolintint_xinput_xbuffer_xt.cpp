// // From Generated code. FIXME: we should give java location.

#include <TeaStoreVariation/CT__TeaStoreVariation__boolboolintint_xinput_xbuffer_xt.hpp>

CT__TeaStoreVariation__boolboolintint_xinput_xbuffer_xt::CT__TeaStoreVariation__boolboolintint_xinput_xbuffer_xt (const string &name, AT__TeaStoreVariation__bool_xbuffer_xt &_comp_decl__redirection_bd, AT__TeaStoreVariation__bool_xbuffer_xt &_comp_decl__cacheResponse_bd, AT__TeaStoreVariation__int_xbuffer_xt &_comp_decl__userID_bd, AT__TeaStoreVariation__int_xbuffer_xt &_comp_decl__dataQty_bd
                              , ConnT__TeaStoreVariation__many2one_xboolboolintint_xt &_conn_decl__boolboolintint_input_connector
                              
                              , CpndEPort__TeaStoreVariation__bool_xport_xt &_eport_decl__redirection_exin_cepd, CpndEPort__TeaStoreVariation__bool_xport_xt &_eport_decl__cacheResponse_exin_cepd, CpndEPort__TeaStoreVariation__int_xport_xt &_eport_decl__userID_exin_cepd, CpndEPort__TeaStoreVariation__int_xport_xt &_eport_decl__dataQty_exin_cepd, CpndEPort__TeaStoreVariation__boolboolintint_xport_xt &_eport_decl__one_cepd
                              
                              

) : ComponentItf(name, COMPOUND), Compound(name), _comp_decl__redirection_bd(_comp_decl__redirection_bd), _comp_decl__cacheResponse_bd(_comp_decl__cacheResponse_bd), _comp_decl__userID_bd(_comp_decl__userID_bd), _comp_decl__dataQty_bd(_comp_decl__dataQty_bd), _conn_decl__boolboolintint_input_connector(_conn_decl__boolboolintint_input_connector), _eport_decl__redirection_exin_cepd(_eport_decl__redirection_exin_cepd), _eport_decl__cacheResponse_exin_cepd(_eport_decl__cacheResponse_exin_cepd), _eport_decl__userID_exin_cepd(_eport_decl__userID_exin_cepd), _eport_decl__dataQty_exin_cepd(_eport_decl__dataQty_exin_cepd), _eport_decl__one_cepd(_eport_decl__one_cepd) {
    this->addComponent(_comp_decl__redirection_bd);
    this->addComponent(_comp_decl__cacheResponse_bd);
    this->addComponent(_comp_decl__userID_bd);
    this->addComponent(_comp_decl__dataQty_bd);
    this->addConnector(_conn_decl__boolboolintint_input_connector);
    this->addPort(_eport_decl__redirection_exin_cepd);
    this->addPort(_eport_decl__cacheResponse_exin_cepd);
    this->addPort(_eport_decl__userID_exin_cepd);
    this->addPort(_eport_decl__dataQty_exin_cepd);
    this->addPort(_eport_decl__one_cepd);
}

CT__TeaStoreVariation__boolboolintint_xinput_xbuffer_xt::~CT__TeaStoreVariation__boolboolintint_xinput_xbuffer_xt() {
}
