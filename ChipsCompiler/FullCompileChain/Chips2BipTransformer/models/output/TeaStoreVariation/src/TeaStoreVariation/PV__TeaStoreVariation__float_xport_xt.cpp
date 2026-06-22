#include <TeaStoreVariation/PV__TeaStoreVariation__float_xport_xt.hpp>

#include <iostream>
#include <sstream>

PV__TeaStoreVariation__float_xport_xt::PV__TeaStoreVariation__float_xport_xt(chips_float &_m_v0) : PortValue(),  m_v0(_m_v0) {
}

string PV__TeaStoreVariation__float_xport_xt::toString() const {
    ostringstream oss;

    oss << "v0=" << m_v0 << ';';
    return oss.str();
}

PV__TeaStoreVariation__float_xport_xt::~PV__TeaStoreVariation__float_xport_xt() {
}


