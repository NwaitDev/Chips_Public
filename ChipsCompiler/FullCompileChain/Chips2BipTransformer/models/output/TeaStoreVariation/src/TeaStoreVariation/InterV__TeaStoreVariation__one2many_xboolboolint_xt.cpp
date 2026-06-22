
#include <TeaStoreVariation/InterV__TeaStoreVariation__one2many_xboolboolint_xt.hpp>
#include <TeaStoreVariation/ConnT__TeaStoreVariation__one2many_xboolboolint_xt.hpp>

InterV__TeaStoreVariation__one2many_xboolboolint_xt::InterV__TeaStoreVariation__one2many_xboolboolint_xt(const ConnT__TeaStoreVariation__one2many_xboolboolint_xt &connector, const Interaction& interaction, const vector<PortValue *> &values) :
        InteractionValue(),
        mInteraction(connector, interaction.ports()),
        mExportedPortValue(_id__v0, _id__v1, _id__v2) {
    this->mPortValues.reserve(3);
    commonRecycle(interaction, values);
}


void InterV__TeaStoreVariation__one2many_xboolboolint_xt::commonRecycle(const Interaction& interaction, const vector<PortValue *> &values) {
	this->mPortValues.clear();
    for (vector<PortValue *>::const_iterator valueIt = values.begin() ;
         valueIt != values.end() ;
         ++valueIt) {
        this->mPortValues.push_back(*valueIt);
    }
}


InterV__TeaStoreVariation__one2many_xboolboolint_xt::~InterV__TeaStoreVariation__one2many_xboolboolint_xt(){
}


