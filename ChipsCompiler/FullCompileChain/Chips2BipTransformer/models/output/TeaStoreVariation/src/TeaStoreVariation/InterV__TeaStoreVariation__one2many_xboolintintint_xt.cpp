
#include <TeaStoreVariation/InterV__TeaStoreVariation__one2many_xboolintintint_xt.hpp>
#include <TeaStoreVariation/ConnT__TeaStoreVariation__one2many_xboolintintint_xt.hpp>

InterV__TeaStoreVariation__one2many_xboolintintint_xt::InterV__TeaStoreVariation__one2many_xboolintintint_xt(const ConnT__TeaStoreVariation__one2many_xboolintintint_xt &connector, const Interaction& interaction, const vector<PortValue *> &values) :
        InteractionValue(),
        mInteraction(connector, interaction.ports()),
        mExportedPortValue(_id__v0, _id__v1, _id__v2, _id__v3) {
    this->mPortValues.reserve(4);
    commonRecycle(interaction, values);
}


void InterV__TeaStoreVariation__one2many_xboolintintint_xt::commonRecycle(const Interaction& interaction, const vector<PortValue *> &values) {
	this->mPortValues.clear();
    for (vector<PortValue *>::const_iterator valueIt = values.begin() ;
         valueIt != values.end() ;
         ++valueIt) {
        this->mPortValues.push_back(*valueIt);
    }
}


InterV__TeaStoreVariation__one2many_xboolintintint_xt::~InterV__TeaStoreVariation__one2many_xboolintintint_xt(){
}


