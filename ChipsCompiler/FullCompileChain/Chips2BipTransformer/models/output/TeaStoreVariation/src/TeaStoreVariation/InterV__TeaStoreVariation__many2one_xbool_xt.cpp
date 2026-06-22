
#include <TeaStoreVariation/InterV__TeaStoreVariation__many2one_xbool_xt.hpp>
#include <TeaStoreVariation/ConnT__TeaStoreVariation__many2one_xbool_xt.hpp>

InterV__TeaStoreVariation__many2one_xbool_xt::InterV__TeaStoreVariation__many2one_xbool_xt(const ConnT__TeaStoreVariation__many2one_xbool_xt &connector, const Interaction& interaction, const vector<PortValue *> &values) :
        InteractionValue(),
        mInteraction(connector, interaction.ports()),
        mExportedPortValue(_id__v0) {
    this->mPortValues.reserve(1);
    commonRecycle(interaction, values);
}


void InterV__TeaStoreVariation__many2one_xbool_xt::commonRecycle(const Interaction& interaction, const vector<PortValue *> &values) {
	this->mPortValues.clear();
    for (vector<PortValue *>::const_iterator valueIt = values.begin() ;
         valueIt != values.end() ;
         ++valueIt) {
        this->mPortValues.push_back(*valueIt);
    }
}


InterV__TeaStoreVariation__many2one_xbool_xt::~InterV__TeaStoreVariation__many2one_xbool_xt(){
}


