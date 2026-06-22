
#include <TeaStoreVariation/AtomEPort__TeaStoreVariation__port_xt.hpp>
#include <TeaStoreVariation/PV__TeaStoreVariation__port_xt.hpp>

AtomEPort__TeaStoreVariation__port_xt::AtomEPort__TeaStoreVariation__port_xt(const string &name, bool hasEarlyUpdate) :
    PortItf(name, ATOM_EXPORT),
    Port(name, ATOM_EXPORT),
    AtomExportPort(name, hasEarlyUpdate),
    PT__TeaStoreVariation__port_xt(name, ATOM_EXPORT),
    mIsReset(false) {
}

AtomEPort__TeaStoreVariation__port_xt::~AtomEPort__TeaStoreVariation__port_xt(){
}
