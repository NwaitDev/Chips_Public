
#include <TeaStoreVariation/InterV__TeaStoreVariation__many2one_xintint_xt.hpp>
#include <TeaStoreVariation/ConnT__TeaStoreVariation__many2one_xintint_xt.hpp>

InterV__TeaStoreVariation__many2one_xintint_xt::InterV__TeaStoreVariation__many2one_xintint_xt(const ConnT__TeaStoreVariation__many2one_xintint_xt &connector, const Interaction& interaction, const vector<PortValue *> &values) :
        InteractionValue(),
        mInteraction(connector, interaction.ports()),
        mExportedPortValue(_id__v0, _id__v1) {
    this->mPortValues.reserve(2);
    commonRecycle(interaction, values);
}


void InterV__TeaStoreVariation__many2one_xintint_xt::commonRecycle(const Interaction& interaction, const vector<PortValue *> &values) {
	this->mPortValues.clear();
    for (vector<PortValue *>::const_iterator valueIt = values.begin() ;
         valueIt != values.end() ;
         ++valueIt) {
        this->mPortValues.push_back(*valueIt);
    }
}


InterV__TeaStoreVariation__many2one_xintint_xt::~InterV__TeaStoreVariation__many2one_xintint_xt(){
}


