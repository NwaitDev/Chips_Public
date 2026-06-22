
#include <TeaStoreVariation/InterV__TeaStoreVariation__flow_xboolintintint_xt.hpp>
#include <TeaStoreVariation/ConnT__TeaStoreVariation__flow_xboolintintint_xt.hpp>

InterV__TeaStoreVariation__flow_xboolintintint_xt::InterV__TeaStoreVariation__flow_xboolintintint_xt(const ConnT__TeaStoreVariation__flow_xboolintintint_xt &connector, const Interaction& interaction, const vector<PortValue *> &values) :
        InteractionValue(),
        mInteraction(connector, interaction.ports()) {
    this->mPortValues.reserve(2);
    commonRecycle(interaction, values);
}


void InterV__TeaStoreVariation__flow_xboolintintint_xt::commonRecycle(const Interaction& interaction, const vector<PortValue *> &values) {
	this->mPortValues.clear();
    for (vector<PortValue *>::const_iterator valueIt = values.begin() ;
         valueIt != values.end() ;
         ++valueIt) {
        this->mPortValues.push_back(*valueIt);
    }
}


InterV__TeaStoreVariation__flow_xboolintintint_xt::~InterV__TeaStoreVariation__flow_xboolintintint_xt(){
}


