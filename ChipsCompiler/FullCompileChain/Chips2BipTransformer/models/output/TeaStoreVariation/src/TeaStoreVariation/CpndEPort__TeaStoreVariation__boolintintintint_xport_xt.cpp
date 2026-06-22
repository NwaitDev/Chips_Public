#include <TeaStoreVariation/CpndEPort__TeaStoreVariation__boolintintintint_xport_xt.hpp>

#include <TeaStoreVariation/PV__TeaStoreVariation__boolintintintint_xport_xt.hpp>

CpndEPort__TeaStoreVariation__boolintintintint_xport_xt::CpndEPort__TeaStoreVariation__boolintintintint_xport_xt(const string &name) :
    PortItf(name, COMPOUND_EXPORT),
    Port(name, COMPOUND_EXPORT),
    CompoundExportPort(name),
    PT__TeaStoreVariation__boolintintintint_xport_xt(name, COMPOUND_EXPORT) {
}

CpndEPort__TeaStoreVariation__boolintintintint_xport_xt::~CpndEPort__TeaStoreVariation__boolintintintint_xport_xt() {
}
