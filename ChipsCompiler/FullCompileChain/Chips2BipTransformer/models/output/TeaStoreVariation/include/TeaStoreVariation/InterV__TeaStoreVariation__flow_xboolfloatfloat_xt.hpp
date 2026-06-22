#ifndef INCLUDE_TEASTOREVARIATION_INTERV____TEASTOREVARIATION____FLOW__XBOOLFLOATFLOAT__XT_HPP_
#define INCLUDE_TEASTOREVARIATION_INTERV____TEASTOREVARIATION____FLOW__XBOOLFLOATFLOAT__XT_HPP_


#include <TeaStoreVariation/Inter__TeaStoreVariation__flow_xboolfloatfloat_xt.hpp>

class Port;
class PortValue;
class ConnT__TeaStoreVariation__flow_xboolfloatfloat_xt;

class InterV__TeaStoreVariation__flow_xboolfloatfloat_xt : public InteractionValue {
public:
    virtual ~InterV__TeaStoreVariation__flow_xboolfloatfloat_xt();

    // getters for references (declared pure virtual in interface)
    virtual const Interaction &interaction() const { return mInteraction; }
    virtual const vector<PortValue *> &portValues() const;
    virtual bool hasPortValues() const;

    // specific operations
    const vector<Port *> &ports() const { return mInteraction.ports(); }

    // Only allow the connector to call the ctor here (see createInteractionValue() method)
    friend class ConnT__TeaStoreVariation__flow_xboolfloatfloat_xt;

protected:
    InterV__TeaStoreVariation__flow_xboolfloatfloat_xt(const ConnT__TeaStoreVariation__flow_xboolfloatfloat_xt &connector, const Interaction& interaction, const vector<PortValue *> &values);
    Inter__TeaStoreVariation__flow_xboolfloatfloat_xt mInteraction;
    vector<PortValue *> &portValues();
    vector<PortValue *> mPortValues;

    void commonRecycle(const Interaction& interaction, const vector<PortValue *> &values);


}; 

inline
const vector<PortValue *> &InterV__TeaStoreVariation__flow_xboolfloatfloat_xt::portValues() const {
    return this->mPortValues;
}

inline
bool InterV__TeaStoreVariation__flow_xboolfloatfloat_xt::hasPortValues() const {
    return (!this->mPortValues.empty());
}

inline
vector<PortValue *> &InterV__TeaStoreVariation__flow_xboolfloatfloat_xt::portValues() {
    return mPortValues;
}

#endif // INCLUDE_TEASTOREVARIATION_INTERV____TEASTOREVARIATION____FLOW__XBOOLFLOATFLOAT__XT_HPP_
