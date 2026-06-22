#include <TeaStoreVariation/ConnPort__TeaStoreVariation__port_xt.hpp>

ConnPort__TeaStoreVariation__port_xt::ConnPort__TeaStoreVariation__port_xt(const string &name) : 
    PortItf(name, CONNECTOR_EXPORT),
    Port(name, CONNECTOR_EXPORT),
    ConnectorExportPort(name),
    PT__TeaStoreVariation__port_xt(name, CONNECTOR_EXPORT) {
}

ConnPort__TeaStoreVariation__port_xt::~ConnPort__TeaStoreVariation__port_xt() {
}
