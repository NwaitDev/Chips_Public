#ifndef TEASTOREVARIATION_CONNT____TEASTOREVARIATION____FLOW__XBOOLINTINTINTINT__XT_HPP_
#define TEASTOREVARIATION_CONNT____TEASTOREVARIATION____FLOW__XBOOLINTINTINTINT__XT_HPP_

// // From Generated code. FIXME: we should give java location.
// include package "master" header
#include <TeaStoreVariation.hpp>

#include <Connector.hpp>
#include <Interaction.hpp>
#include <PortValue.hpp>

#if __cplusplus >= 201103L
#include <atomic>
#endif


#include <TeaStoreVariation/QPR__TeaStoreVariation__boolintintintint_xport_xt.hpp>
#include <TeaStoreVariation/InterV__TeaStoreVariation__flow_xboolintintintint_xt.hpp>

class ConnT__TeaStoreVariation__flow_xboolintintintint_xt : public Connector {
public:
    ConnT__TeaStoreVariation__flow_xboolintintintint_xt(const string &name, QPR__TeaStoreVariation__boolintintintint_xport_xt &s, QPR__TeaStoreVariation__boolintintintint_xport_xt &r);
    virtual ~ConnT__TeaStoreVariation__flow_xboolintintintint_xt();

    virtual PortValue &up(const InteractionValue &interactionValue) const;
    virtual void down(InteractionValue &interactionValue) const;
    virtual void down(InteractionValue &interactionValue, PortValue &portValue) const;

    virtual Interaction &createInteraction() const;
    virtual Interaction &createInteraction(const vector<Port *> &ports) const;
    virtual void releaseInteraction(Interaction &interaction) const;

    virtual InteractionValue &createInteractionValue(const Interaction &interactionValue, const vector<PortValue *> &values) const;
    virtual void releaseInteractionValue(InteractionValue &interactionValue) const;

    virtual bool guard(const InteractionValue &interactionValue) const;
    virtual const vector<Interaction *> &interactions() const;
    virtual bool canUpOnlyMaximalInteractions() const {
        return false;
    }

private:
    QPR__TeaStoreVariation__boolintintintint_xport_xt &s;
    QPR__TeaStoreVariation__boolintintintint_xport_xt &r;


    // Interactions
    // build for s,r
    Inter__TeaStoreVariation__flow_xboolintintintint_xt *_i__s_r;



    mutable vector<Interaction *> definedInteractions;
};
#endif // TEASTOREVARIATION_CONNT____TEASTOREVARIATION____FLOW__XBOOLINTINTINTINT__XT_HPP_
