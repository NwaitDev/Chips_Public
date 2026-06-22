#ifndef INCLUDE_TEASTOREVARIATION_INTERV____TEASTOREVARIATION____FLOW__XBOOLINTINTINT__XT_HPP_
#define INCLUDE_TEASTOREVARIATION_INTERV____TEASTOREVARIATION____FLOW__XBOOLINTINTINT__XT_HPP_


#include <TeaStoreVariation/Inter__TeaStoreVariation__flow_xboolintintint_xt.hpp>

class Port;
class PortValue;
class ConnT__TeaStoreVariation__flow_xboolintintint_xt;

class InterV__TeaStoreVariation__flow_xboolintintint_xt : public InteractionValue {
public:
    virtual ~InterV__TeaStoreVariation__flow_xboolintintint_xt();

    // getters for references (declared pure virtual in interface)
    virtual const Interaction &interaction() const { return mInteraction; }
    virtual const vector<PortValue *> &portValues() const;
    virtual bool hasPortValues() const;

    // specific operations
    const vector<Port *> &ports() const { return mInteraction.ports(); }

    // Only allow the connector to call the ctor here (see createInteractionValue() method)
    friend class ConnT__TeaStoreVariation__flow_xboolintintint_xt;

protected:
    InterV__TeaStoreVariation__flow_xboolintintint_xt(const ConnT__TeaStoreVariation__flow_xboolintintint_xt &connector, const Interaction& interaction, const vector<PortValue *> &values);
    Inter__TeaStoreVariation__flow_xboolintintint_xt mInteraction;
    vector<PortValue *> &portValues();
    vector<PortValue *> mPortValues;

    void commonRecycle(const Interaction& interaction, const vector<PortValue *> &values);


}; 

inline
const vector<PortValue *> &InterV__TeaStoreVariation__flow_xboolintintint_xt::portValues() const {
    return this->mPortValues;
}

inline
bool InterV__TeaStoreVariation__flow_xboolintintint_xt::hasPortValues() const {
    return (!this->mPortValues.empty());
}

inline
vector<PortValue *> &InterV__TeaStoreVariation__flow_xboolintintint_xt::portValues() {
    return mPortValues;
}

#endif // INCLUDE_TEASTOREVARIATION_INTERV____TEASTOREVARIATION____FLOW__XBOOLINTINTINT__XT_HPP_
