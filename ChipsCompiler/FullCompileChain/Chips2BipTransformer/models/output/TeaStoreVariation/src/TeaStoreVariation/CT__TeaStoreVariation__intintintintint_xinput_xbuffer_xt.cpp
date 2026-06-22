// // From Generated code. FIXME: we should give java location.

#include <TeaStoreVariation/CT__TeaStoreVariation__intintintintint_xinput_xbuffer_xt.hpp>

CT__TeaStoreVariation__intintintintint_xinput_xbuffer_xt::CT__TeaStoreVariation__intintintintint_xinput_xbuffer_xt (const string &name, AT__TeaStoreVariation__int_xbuffer_xt &_comp_decl__startTime_bd, AT__TeaStoreVariation__int_xbuffer_xt &_comp_decl__endTime_bd, AT__TeaStoreVariation__int_xbuffer_xt &_comp_decl__id_bd, AT__TeaStoreVariation__int_xbuffer_xt &_comp_decl__maxNbData_bd, AT__TeaStoreVariation__int_xbuffer_xt &_comp_decl__httpResponse_bd
                              , ConnT__TeaStoreVariation__many2one_xintintintintint_xt &_conn_decl__intintintintint_input_connector
                              
                              , CpndEPort__TeaStoreVariation__int_xport_xt &_eport_decl__startTime_exin_cepd, CpndEPort__TeaStoreVariation__int_xport_xt &_eport_decl__endTime_exin_cepd, CpndEPort__TeaStoreVariation__int_xport_xt &_eport_decl__id_exin_cepd, CpndEPort__TeaStoreVariation__int_xport_xt &_eport_decl__maxNbData_exin_cepd, CpndEPort__TeaStoreVariation__int_xport_xt &_eport_decl__httpResponse_exin_cepd, CpndEPort__TeaStoreVariation__intintintintint_xport_xt &_eport_decl__one_cepd
                              
                              

) : ComponentItf(name, COMPOUND), Compound(name), _comp_decl__startTime_bd(_comp_decl__startTime_bd), _comp_decl__endTime_bd(_comp_decl__endTime_bd), _comp_decl__id_bd(_comp_decl__id_bd), _comp_decl__maxNbData_bd(_comp_decl__maxNbData_bd), _comp_decl__httpResponse_bd(_comp_decl__httpResponse_bd), _conn_decl__intintintintint_input_connector(_conn_decl__intintintintint_input_connector), _eport_decl__startTime_exin_cepd(_eport_decl__startTime_exin_cepd), _eport_decl__endTime_exin_cepd(_eport_decl__endTime_exin_cepd), _eport_decl__id_exin_cepd(_eport_decl__id_exin_cepd), _eport_decl__maxNbData_exin_cepd(_eport_decl__maxNbData_exin_cepd), _eport_decl__httpResponse_exin_cepd(_eport_decl__httpResponse_exin_cepd), _eport_decl__one_cepd(_eport_decl__one_cepd) {
    this->addComponent(_comp_decl__startTime_bd);
    this->addComponent(_comp_decl__endTime_bd);
    this->addComponent(_comp_decl__id_bd);
    this->addComponent(_comp_decl__maxNbData_bd);
    this->addComponent(_comp_decl__httpResponse_bd);
    this->addConnector(_conn_decl__intintintintint_input_connector);
    this->addPort(_eport_decl__startTime_exin_cepd);
    this->addPort(_eport_decl__endTime_exin_cepd);
    this->addPort(_eport_decl__id_exin_cepd);
    this->addPort(_eport_decl__maxNbData_exin_cepd);
    this->addPort(_eport_decl__httpResponse_exin_cepd);
    this->addPort(_eport_decl__one_cepd);
}

CT__TeaStoreVariation__intintintintint_xinput_xbuffer_xt::~CT__TeaStoreVariation__intintintintint_xinput_xbuffer_xt() {
}
