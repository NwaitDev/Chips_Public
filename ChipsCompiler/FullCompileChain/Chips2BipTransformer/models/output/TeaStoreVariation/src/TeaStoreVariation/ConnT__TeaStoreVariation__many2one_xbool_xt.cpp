// // From Generated code. FIXME: we should give java location.

#include <TeaStoreVariation/ConnT__TeaStoreVariation__many2one_xbool_xt.hpp>

#include <TeaStoreVariation/PV__TeaStoreVariation__bool_xport_xt.hpp>

// for exported port.
#include <TeaStoreVariation/PV__TeaStoreVariation__bool_xport_xt.hpp>
#include <TeaStoreVariation/PV__TeaStoreVariation__bool_xport_xt.hpp>
#include <TeaStoreVariation/PT__TeaStoreVariation__bool_xport_xt.hpp>

static inline PortValue * getPortValue(const QuotedPortReference & qpr, const InteractionValue &civ){
    Port &p = qpr.port();
    vector<Port *>::size_type idx = 0;
    for (vector<Port *>::const_iterator i = civ.ports().begin();
         i != civ.ports().end();
         i++, idx++){
        if (&p == *i) break;
    }
    assert (idx < civ.ports().size()); // means we couldn't find corresponding port value 
    return civ.portValues()[idx];
}

static inline PV__TeaStoreVariation__bool_xport_xt * get_p0_cppd(const QPR__TeaStoreVariation__bool_xport_xt & qpr, const InterV__TeaStoreVariation__many2one_xbool_xt &civ){
  return dynamic_cast<PV__TeaStoreVariation__bool_xport_xt *>(getPortValue(qpr, civ));
}


ConnT__TeaStoreVariation__many2one_xbool_xt::ConnT__TeaStoreVariation__many2one_xbool_xt(const string &name, QPR__TeaStoreVariation__bool_xport_xt &p0_cppd, ConnPort__TeaStoreVariation__bool_xport_xt &r_exported_port) : Connector(name), p0_cppd(p0_cppd), r_exported_port(r_exported_port) {
    this->addPort(p0_cppd);
    this->setExportedPort(r_exported_port);

    // Interactions
    _i__p0_cppd = new Inter__TeaStoreVariation__many2one_xbool_xt(*this, true);
}

ConnT__TeaStoreVariation__many2one_xbool_xt::~ConnT__TeaStoreVariation__many2one_xbool_xt() {

    // Interactions
    delete _i__p0_cppd;
    for (vector<Interaction *>::const_iterator interactionIt = definedInteractions.begin() ;
         interactionIt != definedInteractions.end() ;
         ++interactionIt) {
        delete *interactionIt;
    }
    definedInteractions.clear();
}

PortValue &ConnT__TeaStoreVariation__many2one_xbool_xt::up(const InteractionValue &interactionValue) const {
    assert(dynamic_cast<const InterV__TeaStoreVariation__many2one_xbool_xt *>(&interactionValue) != NULL);
    const InterV__TeaStoreVariation__many2one_xbool_xt *c_interaction_v __attribute__((unused)) = static_cast<const InterV__TeaStoreVariation__many2one_xbool_xt *>(&interactionValue);
    const Inter__TeaStoreVariation__many2one_xbool_xt *c_interaction __attribute__((unused)) = &(c_interaction_v->mInteraction);
    PV__TeaStoreVariation__bool_xport_xt *cpv __attribute__((unused))= &(c_interaction_v->mExportedPortValue);
    
    // first
    if(*c_interaction == *_i__p0_cppd) {
        c_interaction_v->cset_v0(get_p0_cppd(p0_cppd, *c_interaction_v)->get_v0());
    }
    return *cpv;
}

void ConnT__TeaStoreVariation__many2one_xbool_xt::down(InteractionValue &interactionValue) const {
    // You should *never* reach this. Calling this method denotes an error in
    // scheduling (the down(interactionvalue, portvalue) should have been used)
    assert(false);
}

void ConnT__TeaStoreVariation__many2one_xbool_xt::down(InteractionValue &interactionValue, PortValue &portValue) const {
    assert(dynamic_cast<PV__TeaStoreVariation__bool_xport_xt *>(&portValue) != NULL);
    PV__TeaStoreVariation__bool_xport_xt *cpv __attribute__((unused))= static_cast<PV__TeaStoreVariation__bool_xport_xt *>(&portValue);
    
}

Interaction &ConnT__TeaStoreVariation__many2one_xbool_xt::createInteraction() const{
    Inter__TeaStoreVariation__many2one_xbool_xt *ret = NULL;

    ret = new Inter__TeaStoreVariation__many2one_xbool_xt(*this);

    return *ret;
}

Interaction &ConnT__TeaStoreVariation__many2one_xbool_xt::createInteraction(const vector<Port *> &ports) const{
  Inter__TeaStoreVariation__many2one_xbool_xt *ret = NULL;

    ret = new Inter__TeaStoreVariation__many2one_xbool_xt(*this, ports);

    return *ret;
}

InteractionValue &ConnT__TeaStoreVariation__many2one_xbool_xt::createInteractionValue(const Interaction &interaction, const vector<PortValue *> &values) const {
    InterV__TeaStoreVariation__many2one_xbool_xt *ret = NULL;

    ret = new InterV__TeaStoreVariation__many2one_xbool_xt(*this, interaction, values);

    return *ret;
}

void ConnT__TeaStoreVariation__many2one_xbool_xt::releaseInteraction(Interaction &interaction) const {
    delete &interaction;
}

void ConnT__TeaStoreVariation__many2one_xbool_xt::releaseInteractionValue(InteractionValue &interactionValue) const {
    delete &interactionValue;
}

bool ConnT__TeaStoreVariation__many2one_xbool_xt::guard(const InteractionValue &interactionValue) const {
    assert(dynamic_cast<const InterV__TeaStoreVariation__many2one_xbool_xt *>(&interactionValue) != NULL);
    const InterV__TeaStoreVariation__many2one_xbool_xt *c_interaction_v __attribute__((unused)) = static_cast<const InterV__TeaStoreVariation__many2one_xbool_xt *>(&interactionValue);
    const Inter__TeaStoreVariation__many2one_xbool_xt *c_interaction __attribute__((unused)) = &(c_interaction_v->mInteraction);
    if(*c_interaction == *_i__p0_cppd){
// // From Generated code. FIXME: we should give java location.

        return true;
    }

    // default to true. May not be the wisest choice.
    return true;
}

const vector<Interaction*>& ConnT__TeaStoreVariation__many2one_xbool_xt::interactions() const {
  if (definedInteractions.empty()) {
    definedInteractions.push_back(new Inter__TeaStoreVariation__many2one_xbool_xt(*this, true));
  }

  // check that the number of defined interactions is correct
  assert(definedInteractions.size() == 1);

  return definedInteractions;
}
