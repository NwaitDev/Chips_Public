
#include <TeaStoreVariation/Inter__TeaStoreVariation__many2one_xbool_xt.hpp>
#include <TeaStoreVariation/ConnT__TeaStoreVariation__many2one_xbool_xt.hpp>

const bitset<1> Inter__TeaStoreVariation__many2one_xbool_xt::predefined(string("1"));

Inter__TeaStoreVariation__many2one_xbool_xt::Inter__TeaStoreVariation__many2one_xbool_xt(const ConnT__TeaStoreVariation__many2one_xbool_xt &connector) : Interaction(connector) {
    involvedPorts.reset();
    port_vector_fresh = true;
    defined = false;
    refresh_defined = false;
    mPorts.reserve(1);
}

Inter__TeaStoreVariation__many2one_xbool_xt::Inter__TeaStoreVariation__many2one_xbool_xt(const ConnT__TeaStoreVariation__many2one_xbool_xt &connector, bool p0_cppd) : Interaction(connector) {
    involvedPorts.reset();

    defined = true;
    refresh_defined = false;
	port_vector_fresh = false;

    involvedPorts.set(0, p0_cppd);

    defined = p0_cppd;
    mPorts.reserve(1);
}

Inter__TeaStoreVariation__many2one_xbool_xt::Inter__TeaStoreVariation__many2one_xbool_xt(const ConnT__TeaStoreVariation__many2one_xbool_xt &connector, const vector<Port *> &ports) : Interaction(connector), port_vector_fresh(false) {
    commonRecycle(ports);
    mPorts.reserve(1);
}

Inter__TeaStoreVariation__many2one_xbool_xt::~Inter__TeaStoreVariation__many2one_xbool_xt(){
}

// This one is 'const' but its only role
// is to set mPorts correctly (ie. its only role is to modify the object)
void Inter__TeaStoreVariation__many2one_xbool_xt::refreshPorts() const {
    const vector<QuotedPortReference *> &parent_ports = this->connector().ports();
    mPorts.clear();
    mPorts.reserve(1);

    if (involvedPorts.test(0)) {
         mPorts.push_back(&(parent_ports[0]->port()));
    }
    port_vector_fresh = true;
}

vector<Port*>& Inter__TeaStoreVariation__many2one_xbool_xt::ports() {
    if (!port_vector_fresh){
        refreshPorts();
    }

    return mPorts;
}

const vector<Port *> & Inter__TeaStoreVariation__many2one_xbool_xt::ports() const {
    if (!port_vector_fresh){
        refreshPorts();
    }

    return mPorts;
}

bool Inter__TeaStoreVariation__many2one_xbool_xt::operator==(const Interaction &interaction) const {
    bool ret = false;

    // check if interaction values are from the same connector
    if (&connector() == &interaction.connector()) {
        assert(dynamic_cast<const Inter__TeaStoreVariation__many2one_xbool_xt *>(&interaction) != NULL);
        const Inter__TeaStoreVariation__many2one_xbool_xt *other = static_cast<const Inter__TeaStoreVariation__many2one_xbool_xt *>(&interaction);
        ret = (involvedPorts == other->involvedPorts);
    }
    return ret;
}

bool Inter__TeaStoreVariation__many2one_xbool_xt::operator<=(const Interaction &interaction) const {
    bool ret = false;

    // check if interaction values are from the same connector
    if (&connector() == &interaction.connector()) {
        assert(dynamic_cast<const Inter__TeaStoreVariation__many2one_xbool_xt *>(&interaction) != NULL);
        const Inter__TeaStoreVariation__many2one_xbool_xt *other = static_cast<const Inter__TeaStoreVariation__many2one_xbool_xt *>(&interaction);
        ret = ((involvedPorts & other->involvedPorts) == involvedPorts);
    }

    return ret;
}

bool Inter__TeaStoreVariation__many2one_xbool_xt::operator<(const Interaction &interaction) const {
    bool ret = false;

    // check if interaction values are from the same connector
    if (&connector() == &interaction.connector()) {
        assert(dynamic_cast<const Inter__TeaStoreVariation__many2one_xbool_xt *>(&interaction) != NULL);
        const Inter__TeaStoreVariation__many2one_xbool_xt *other = static_cast<const Inter__TeaStoreVariation__many2one_xbool_xt *>(&interaction);
        ret = (((involvedPorts &  other->involvedPorts) == involvedPorts) &&
                (involvedPorts != other->involvedPorts));
    }

    return ret;
}

void Inter__TeaStoreVariation__many2one_xbool_xt::recycle() {
    Interaction::recycle();
    mPorts.clear();
    port_vector_fresh = true;
    defined = false;
    refresh_defined = false;
    involvedPorts.reset();
}

void Inter__TeaStoreVariation__many2one_xbool_xt::recycle(const vector<Port *> &ports) {
    Interaction::recycle();
    commonRecycle(ports);
}

void Inter__TeaStoreVariation__many2one_xbool_xt::commonRecycle(const vector<Port *> &ports){
    involvedPorts.reset();

    for (vector<Port *>::const_iterator portIt = ports.begin() ;
         portIt != ports.end() ;
         ++portIt) {
        const vector<Port *>::size_type post_shift = findPort(*portIt);

        involvedPorts.set(post_shift);
    }

    port_vector_fresh = false;
    refresh_defined = true;
}
