#include <TeaStoreVariation/AtomIPort__TeaStoreVariation__port_xt.hpp>

AtomIPort__TeaStoreVariation__port_xt::AtomIPort__TeaStoreVariation__port_xt(const string &name) : AtomInternalPort(name),
    mIsEnabled(false),
    mIsDisabledByPriorities(false) {
}

AtomIPort__TeaStoreVariation__port_xt::~AtomIPort__TeaStoreVariation__port_xt() {
}
