// // From Generated code. FIXME: we should give java location.

#include <TeaStoreVariation/CT__TeaStoreVariation__boolintintint_xoutput_xbuffer_xt.hpp>

CT__TeaStoreVariation__boolintintint_xoutput_xbuffer_xt::CT__TeaStoreVariation__boolintintint_xoutput_xbuffer_xt (const string &name, AT__TeaStoreVariation__bool_xbuffer_xt &_comp_decl__userAuth_bd, AT__TeaStoreVariation__int_xbuffer_xt &_comp_decl__nbData_bd, AT__TeaStoreVariation__int_xbuffer_xt &_comp_decl__userID_bd, AT__TeaStoreVariation__int_xbuffer_xt &_comp_decl__fromServerToInternet_bd
                              , ConnT__java__lang__Object@98025e0__many2one_xboolintintint_xt &_conn_decl__boolintintint_input_connector
                              
                              , CpndEPort__TeaStoreVariation__bool_xport_xt &_eport_decl__userAuth_exout_cepd, CpndEPort__TeaStoreVariation__int_xport_xt &_eport_decl__nbData_exout_cepd, CpndEPort__TeaStoreVariation__int_xport_xt &_eport_decl__userID_exout_cepd, CpndEPort__TeaStoreVariation__int_xport_xt &_eport_decl__fromServerToInternet_exout_cepd, CpndEPort__TeaStoreVariation__boolintintint_xport_xt &_eport_decl__one_cepd
                              
                              

) : ComponentItf(name, COMPOUND), Compound(name), _comp_decl__userAuth_bd(_comp_decl__userAuth_bd), _comp_decl__nbData_bd(_comp_decl__nbData_bd), _comp_decl__userID_bd(_comp_decl__userID_bd), _comp_decl__fromServerToInternet_bd(_comp_decl__fromServerToInternet_bd), _conn_decl__boolintintint_input_connector(_conn_decl__boolintintint_input_connector), _eport_decl__userAuth_exout_cepd(_eport_decl__userAuth_exout_cepd), _eport_decl__nbData_exout_cepd(_eport_decl__nbData_exout_cepd), _eport_decl__userID_exout_cepd(_eport_decl__userID_exout_cepd), _eport_decl__fromServerToInternet_exout_cepd(_eport_decl__fromServerToInternet_exout_cepd), _eport_decl__one_cepd(_eport_decl__one_cepd) {
    this->addComponent(_comp_decl__userAuth_bd);
    this->addComponent(_comp_decl__nbData_bd);
    this->addComponent(_comp_decl__userID_bd);
    this->addComponent(_comp_decl__fromServerToInternet_bd);
    this->addConnector(_conn_decl__boolintintint_input_connector);
    this->addPort(_eport_decl__userAuth_exout_cepd);
    this->addPort(_eport_decl__nbData_exout_cepd);
    this->addPort(_eport_decl__userID_exout_cepd);
    this->addPort(_eport_decl__fromServerToInternet_exout_cepd);
    this->addPort(_eport_decl__one_cepd);
}

CT__TeaStoreVariation__boolintintint_xoutput_xbuffer_xt::~CT__TeaStoreVariation__boolintintint_xoutput_xbuffer_xt() {
}
