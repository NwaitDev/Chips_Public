// // From Generated code. FIXME: we should give java location.

#include <TeaStoreVariation/CT__TeaStoreVariation__boolboolint_xoutput_xbuffer_xt.hpp>

CT__TeaStoreVariation__boolboolint_xoutput_xbuffer_xt::CT__TeaStoreVariation__boolboolint_xoutput_xbuffer_xt (const string &name, AT__TeaStoreVariation__bool_xbuffer_xt &_comp_decl__reqAuth_bd, AT__TeaStoreVariation__bool_xbuffer_xt &_comp_decl__isNewPage_bd, AT__TeaStoreVariation__int_xbuffer_xt &_comp_decl__idToRespondTo_bd
                              , ConnT__java__lang__Object@98025e0__many2one_xboolboolint_xt &_conn_decl__boolboolint_input_connector
                              
                              , CpndEPort__TeaStoreVariation__bool_xport_xt &_eport_decl__reqAuth_exout_cepd, CpndEPort__TeaStoreVariation__bool_xport_xt &_eport_decl__isNewPage_exout_cepd, CpndEPort__TeaStoreVariation__int_xport_xt &_eport_decl__idToRespondTo_exout_cepd, CpndEPort__TeaStoreVariation__boolboolint_xport_xt &_eport_decl__one_cepd
                              
                              

) : ComponentItf(name, COMPOUND), Compound(name), _comp_decl__reqAuth_bd(_comp_decl__reqAuth_bd), _comp_decl__isNewPage_bd(_comp_decl__isNewPage_bd), _comp_decl__idToRespondTo_bd(_comp_decl__idToRespondTo_bd), _conn_decl__boolboolint_input_connector(_conn_decl__boolboolint_input_connector), _eport_decl__reqAuth_exout_cepd(_eport_decl__reqAuth_exout_cepd), _eport_decl__isNewPage_exout_cepd(_eport_decl__isNewPage_exout_cepd), _eport_decl__idToRespondTo_exout_cepd(_eport_decl__idToRespondTo_exout_cepd), _eport_decl__one_cepd(_eport_decl__one_cepd) {
    this->addComponent(_comp_decl__reqAuth_bd);
    this->addComponent(_comp_decl__isNewPage_bd);
    this->addComponent(_comp_decl__idToRespondTo_bd);
    this->addConnector(_conn_decl__boolboolint_input_connector);
    this->addPort(_eport_decl__reqAuth_exout_cepd);
    this->addPort(_eport_decl__isNewPage_exout_cepd);
    this->addPort(_eport_decl__idToRespondTo_exout_cepd);
    this->addPort(_eport_decl__one_cepd);
}

CT__TeaStoreVariation__boolboolint_xoutput_xbuffer_xt::~CT__TeaStoreVariation__boolboolint_xoutput_xbuffer_xt() {
}
