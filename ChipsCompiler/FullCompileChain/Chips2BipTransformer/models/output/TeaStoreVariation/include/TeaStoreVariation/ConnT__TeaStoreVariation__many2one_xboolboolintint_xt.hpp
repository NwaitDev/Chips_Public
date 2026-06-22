#ifndef TEASTOREVARIATION_CONNT____TEASTOREVARIATION____MANY2ONE__XBOOLBOOLINTINT__XT_HPP_
#define TEASTOREVARIATION_CONNT____TEASTOREVARIATION____MANY2ONE__XBOOLBOOLINTINT__XT_HPP_

// // From Generated code. FIXME: we should give java location.
// include package "master" header
#include <TeaStoreVariation.hpp>

#include <Connector.hpp>
#include <Interaction.hpp>
#include <PortValue.hpp>

#if __cplusplus >= 201103L
#include <atomic>
#endif


#include <TeaStoreVariation/QPR__TeaStoreVariation__boolboolintint_xport_xt.hpp>
#include <TeaStoreVariation/ConnPort__TeaStoreVariation__boolboolintint_xport_xt.hpp>
#include <TeaStoreVariation/InterV__TeaStoreVariation__many2one_xboolboolintint_xt.hpp>

class ConnT__TeaStoreVariation__many2one_xboolboolintint_xt : public Connector {
public:
    ConnT__TeaStoreVariation__many2one_xboolboolintint_xt(const string &name, QPR__TeaStoreVariation__boolboolintint_xport_xt &p0_cppd, QPR__TeaStoreVariation__boolboolintint_xport_xt &p1_cppd, QPR__TeaStoreVariation__boolboolintint_xport_xt &p2_cppd, QPR__TeaStoreVariation__boolboolintint_xport_xt &p3_cppd, ConnPort__TeaStoreVariation__boolboolintint_xport_xt &r_exported_port);
    virtual ~ConnT__TeaStoreVariation__many2one_xboolboolintint_xt();

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
    QPR__TeaStoreVariation__boolboolintint_xport_xt &p0_cppd;
    QPR__TeaStoreVariation__boolboolintint_xport_xt &p1_cppd;
    QPR__TeaStoreVariation__boolboolintint_xport_xt &p2_cppd;
    QPR__TeaStoreVariation__boolboolintint_xport_xt &p3_cppd;

    ConnPort__TeaStoreVariation__boolboolintint_xport_xt &r_exported_port;

    // Interactions
    // build for p0_cppd,p1_cppd,p2_cppd,p3_cppd
    Inter__TeaStoreVariation__many2one_xboolboolintint_xt *_i__p0_cppd_p1_cppd_p2_cppd_p3_cppd;



    mutable vector<Interaction *> definedInteractions;
};
#endif // TEASTOREVARIATION_CONNT____TEASTOREVARIATION____MANY2ONE__XBOOLBOOLINTINT__XT_HPP_
