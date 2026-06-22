#include <TeaStoreVariation/PV__TeaStoreVariation__boolint_xport_xt.hpp>

#include <iostream>
#include <sstream>

PV__TeaStoreVariation__boolint_xport_xt::PV__TeaStoreVariation__boolint_xport_xt(chips_bool &_m_v0, chips_int &_m_v1) : PortValue(),  m_v0(_m_v0),  m_v1(_m_v1) {
}

string PV__TeaStoreVariation__boolint_xport_xt::toString() const {
    ostringstream oss;

    oss << "v0=" << m_v0 << ';';
    oss << "v1=" << m_v1 << ';';
    return oss.str();
}

PV__TeaStoreVariation__boolint_xport_xt::~PV__TeaStoreVariation__boolint_xport_xt() {
}


