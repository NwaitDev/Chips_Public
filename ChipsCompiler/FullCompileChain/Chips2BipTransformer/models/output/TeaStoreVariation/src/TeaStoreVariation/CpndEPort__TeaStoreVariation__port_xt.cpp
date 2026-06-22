#include <TeaStoreVariation/CpndEPort__TeaStoreVariation__port_xt.hpp>

#include <TeaStoreVariation/PV__TeaStoreVariation__port_xt.hpp>

CpndEPort__TeaStoreVariation__port_xt::CpndEPort__TeaStoreVariation__port_xt(const string &name) :
    PortItf(name, COMPOUND_EXPORT),
    Port(name, COMPOUND_EXPORT),
    CompoundExportPort(name),
    PT__TeaStoreVariation__port_xt(name, COMPOUND_EXPORT) {
}

CpndEPort__TeaStoreVariation__port_xt::~CpndEPort__TeaStoreVariation__port_xt() {
}
