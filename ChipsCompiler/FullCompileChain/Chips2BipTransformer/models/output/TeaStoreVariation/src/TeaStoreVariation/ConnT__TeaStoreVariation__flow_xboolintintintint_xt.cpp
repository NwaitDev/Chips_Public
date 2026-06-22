// // From Generated code. FIXME: we should give java location.

#include <TeaStoreVariation/ConnT__TeaStoreVariation__flow_xboolintintintint_xt.hpp>

#include <TeaStoreVariation/PV__TeaStoreVariation__boolintintintint_xport_xt.hpp>


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

static inline PV__TeaStoreVariation__boolintintintint_xport_xt * get_s(const QPR__TeaStoreVariation__boolintintintint_xport_xt & qpr, const InterV__TeaStoreVariation__flow_xboolintintintint_xt &civ){
  return dynamic_cast<PV__TeaStoreVariation__boolintintintint_xport_xt *>(getPortValue(qpr, civ));
}
static inline PV__TeaStoreVariation__boolintintintint_xport_xt * get_r(const QPR__TeaStoreVariation__boolintintintint_xport_xt & qpr, const InterV__TeaStoreVariation__flow_xboolintintintint_xt &civ){
  return dynamic_cast<PV__TeaStoreVariation__boolintintintint_xport_xt *>(getPortValue(qpr, civ));
}


ConnT__TeaStoreVariation__flow_xboolintintintint_xt::ConnT__TeaStoreVariation__flow_xboolintintintint_xt(const string &name, QPR__TeaStoreVariation__boolintintintint_xport_xt &s, QPR__TeaStoreVariation__boolintintintint_xport_xt &r) : Connector(name), s(s), r(r) {
    this->addPort(s);
    this->addPort(r);

    // Interactions
    _i__s_r = new Inter__TeaStoreVariation__flow_xboolintintintint_xt(*this, true, true);
}

ConnT__TeaStoreVariation__flow_xboolintintintint_xt::~ConnT__TeaStoreVariation__flow_xboolintintintint_xt() {

    // Interactions
    delete _i__s_r;
    for (vector<Interaction *>::const_iterator interactionIt = definedInteractions.begin() ;
         interactionIt != definedInteractions.end() ;
         ++interactionIt) {
        delete *interactionIt;
    }
    definedInteractions.clear();
}

PortValue &ConnT__TeaStoreVariation__flow_xboolintintintint_xt::up(const InteractionValue &interactionValue) const {
    // THIS SHOULD *NEVER* HAPPEN.
    assert(false);

    // to avoid warnings
    PortValue *pv = NULL;

    return *pv;
}

void ConnT__TeaStoreVariation__flow_xboolintintintint_xt::down(InteractionValue &interactionValue) const {
    assert(dynamic_cast<const InterV__TeaStoreVariation__flow_xboolintintintint_xt *>(&interactionValue) != NULL);
    const Inter__TeaStoreVariation__flow_xboolintintintint_xt *c_interaction __attribute__((unused)) = static_cast<const Inter__TeaStoreVariation__flow_xboolintintintint_xt *>(&(interactionValue.interaction()));
    const InterV__TeaStoreVariation__flow_xboolintintintint_xt *c_interaction_v __attribute__((unused)) = static_cast<const InterV__TeaStoreVariation__flow_xboolintintintint_xt *>(&interactionValue);
    if(*c_interaction == *_i__s_r) {
    // // From Generated code. FIXME: we should give java location.
        get_r(r, *c_interaction_v)->set_v0(get_s(s, *c_interaction_v)->get_v0());
    // // From Generated code. FIXME: we should give java location.
        get_r(r, *c_interaction_v)->set_v1(get_s(s, *c_interaction_v)->get_v1());
    // // From Generated code. FIXME: we should give java location.
        get_r(r, *c_interaction_v)->set_v2(get_s(s, *c_interaction_v)->get_v2());
    // // From Generated code. FIXME: we should give java location.
        get_r(r, *c_interaction_v)->set_v3(get_s(s, *c_interaction_v)->get_v3());
    // // From Generated code. FIXME: we should give java location.
        get_r(r, *c_interaction_v)->set_v4(get_s(s, *c_interaction_v)->get_v4());
    }
}

void ConnT__TeaStoreVariation__flow_xboolintintintint_xt::down(InteractionValue &interactionValue, PortValue &portValue) const {
    // You should *never* reach this. Calling this method denotes an error in
    // scheduling (the down(interactionvalue) should have been used
    assert(false);
}

Interaction &ConnT__TeaStoreVariation__flow_xboolintintintint_xt::createInteraction() const{
    Inter__TeaStoreVariation__flow_xboolintintintint_xt *ret = NULL;

    ret = new Inter__TeaStoreVariation__flow_xboolintintintint_xt(*this);

    return *ret;
}

Interaction &ConnT__TeaStoreVariation__flow_xboolintintintint_xt::createInteraction(const vector<Port *> &ports) const{
  Inter__TeaStoreVariation__flow_xboolintintintint_xt *ret = NULL;

    ret = new Inter__TeaStoreVariation__flow_xboolintintintint_xt(*this, ports);

    return *ret;
}

InteractionValue &ConnT__TeaStoreVariation__flow_xboolintintintint_xt::createInteractionValue(const Interaction &interaction, const vector<PortValue *> &values) const {
    InterV__TeaStoreVariation__flow_xboolintintintint_xt *ret = NULL;

    ret = new InterV__TeaStoreVariation__flow_xboolintintintint_xt(*this, interaction, values);

    return *ret;
}

void ConnT__TeaStoreVariation__flow_xboolintintintint_xt::releaseInteraction(Interaction &interaction) const {
    delete &interaction;
}

void ConnT__TeaStoreVariation__flow_xboolintintintint_xt::releaseInteractionValue(InteractionValue &interactionValue) const {
    delete &interactionValue;
}

bool ConnT__TeaStoreVariation__flow_xboolintintintint_xt::guard(const InteractionValue &interactionValue) const {
    assert(dynamic_cast<const InterV__TeaStoreVariation__flow_xboolintintintint_xt *>(&interactionValue) != NULL);
    const InterV__TeaStoreVariation__flow_xboolintintintint_xt *c_interaction_v __attribute__((unused)) = static_cast<const InterV__TeaStoreVariation__flow_xboolintintintint_xt *>(&interactionValue);
    const Inter__TeaStoreVariation__flow_xboolintintintint_xt *c_interaction __attribute__((unused)) = &(c_interaction_v->mInteraction);
    if(*c_interaction == *_i__s_r){
// // From Generated code. FIXME: we should give java location.

        return true;
    }

    // default to true. May not be the wisest choice.
    return true;
}

const vector<Interaction*>& ConnT__TeaStoreVariation__flow_xboolintintintint_xt::interactions() const {
  if (definedInteractions.empty()) {
    definedInteractions.push_back(new Inter__TeaStoreVariation__flow_xboolintintintint_xt(*this, true, true));
  }

  // check that the number of defined interactions is correct
  assert(definedInteractions.size() == 1);

  return definedInteractions;
}
