
#include <TeaStoreVariation/InterV__TeaStoreVariation__flow_xint_xt.hpp>
#include <TeaStoreVariation/ConnT__TeaStoreVariation__flow_xint_xt.hpp>

InterV__TeaStoreVariation__flow_xint_xt::InterV__TeaStoreVariation__flow_xint_xt(const ConnT__TeaStoreVariation__flow_xint_xt &connector, const Interaction& interaction, const vector<PortValue *> &values) :
        InteractionValue(),
        mInteraction(connector, interaction.ports()) {
    this->mPortValues.reserve(2);
    commonRecycle(interaction, values);
}


void InterV__TeaStoreVariation__flow_xint_xt::commonRecycle(const Interaction& interaction, const vector<PortValue *> &values) {
	this->mPortValues.clear();
    for (vector<PortValue *>::const_iterator valueIt = values.begin() ;
         valueIt != values.end() ;
         ++valueIt) {
        this->mPortValues.push_back(*valueIt);
    }
}


InterV__TeaStoreVariation__flow_xint_xt::~InterV__TeaStoreVariation__flow_xint_xt(){
}


