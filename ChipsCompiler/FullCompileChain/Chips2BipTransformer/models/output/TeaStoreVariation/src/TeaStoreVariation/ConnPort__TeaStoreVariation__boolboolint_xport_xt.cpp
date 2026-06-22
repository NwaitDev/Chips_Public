#include <TeaStoreVariation/ConnPort__TeaStoreVariation__boolboolint_xport_xt.hpp>

ConnPort__TeaStoreVariation__boolboolint_xport_xt::ConnPort__TeaStoreVariation__boolboolint_xport_xt(const string &name) : 
    PortItf(name, CONNECTOR_EXPORT),
    Port(name, CONNECTOR_EXPORT),
    ConnectorExportPort(name),
    PT__TeaStoreVariation__boolboolint_xport_xt(name, CONNECTOR_EXPORT) {
}

ConnPort__TeaStoreVariation__boolboolint_xport_xt::~ConnPort__TeaStoreVariation__boolboolint_xport_xt() {
}
