#include <TeaStoreVariation/PV__TeaStoreVariation__int_xport_xt.hpp>

#include <iostream>
#include <sstream>

PV__TeaStoreVariation__int_xport_xt::PV__TeaStoreVariation__int_xport_xt(chips_int &_m_v0) : PortValue(),  m_v0(_m_v0) {
}

string PV__TeaStoreVariation__int_xport_xt::toString() const {
    ostringstream oss;

    oss << "v0=" << m_v0 << ';';
    return oss.str();
}

PV__TeaStoreVariation__int_xport_xt::~PV__TeaStoreVariation__int_xport_xt() {
}


