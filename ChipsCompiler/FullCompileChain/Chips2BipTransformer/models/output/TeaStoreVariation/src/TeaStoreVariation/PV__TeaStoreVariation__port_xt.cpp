#include <TeaStoreVariation/PV__TeaStoreVariation__port_xt.hpp>

#include <iostream>
#include <sstream>

PV__TeaStoreVariation__port_xt::PV__TeaStoreVariation__port_xt() : PortValue() {
}

string PV__TeaStoreVariation__port_xt::toString() const {
    ostringstream oss;

    return oss.str();
}

PV__TeaStoreVariation__port_xt::~PV__TeaStoreVariation__port_xt() {
}


