// // From Generated code. FIXME: we should give java location.

#include <TeaStoreVariation/CT__TeaStoreVariation__int_xoutput_xbuffer_xt.hpp>

CT__TeaStoreVariation__int_xoutput_xbuffer_xt::CT__TeaStoreVariation__int_xoutput_xbuffer_xt (const string &name, AT__TeaStoreVariation__int_xbuffer_xt &_comp_decl__knob_bd
                              , ConnT____many2one_xint_xt &_conn_decl__int_input_connector
                              
                              , CpndEPort__TeaStoreVariation__int_xport_xt &_eport_decl__knob_exout_cepd, CpndEPort__TeaStoreVariation__int_xport_xt &_eport_decl__one_cepd
                              
                              

) : ComponentItf(name, COMPOUND), Compound(name), _comp_decl__knob_bd(_comp_decl__knob_bd), _conn_decl__int_input_connector(_conn_decl__int_input_connector), _eport_decl__knob_exout_cepd(_eport_decl__knob_exout_cepd), _eport_decl__one_cepd(_eport_decl__one_cepd) {
    this->addComponent(_comp_decl__knob_bd);
    this->addConnector(_conn_decl__int_input_connector);
    this->addPort(_eport_decl__knob_exout_cepd);
    this->addPort(_eport_decl__one_cepd);
}

CT__TeaStoreVariation__int_xoutput_xbuffer_xt::~CT__TeaStoreVariation__int_xoutput_xbuffer_xt() {
}
