#include <TeaStoreVariation/PV__TeaStoreVariation__boolboolfloatintint_xport_xt.hpp>

#include <iostream>
#include <sstream>

PV__TeaStoreVariation__boolboolfloatintint_xport_xt::PV__TeaStoreVariation__boolboolfloatintint_xport_xt(chips_bool &_m_v0, chips_bool &_m_v1, chips_float &_m_v2, chips_int &_m_v3, chips_int &_m_v4) : PortValue(),  m_v0(_m_v0),  m_v1(_m_v1),  m_v2(_m_v2),  m_v3(_m_v3),  m_v4(_m_v4) {
}

string PV__TeaStoreVariation__boolboolfloatintint_xport_xt::toString() const {
    ostringstream oss;

    oss << "v0=" << m_v0 << ';';
    oss << "v1=" << m_v1 << ';';
    oss << "v2=" << m_v2 << ';';
    oss << "v3=" << m_v3 << ';';
    oss << "v4=" << m_v4 << ';';
    return oss.str();
}

PV__TeaStoreVariation__boolboolfloatintint_xport_xt::~PV__TeaStoreVariation__boolboolfloatintint_xport_xt() {
}


