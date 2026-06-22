
#include <TeaStoreVariation/Inter__TeaStoreVariation__flow_xintint_xt.hpp>
#include <TeaStoreVariation/ConnT__TeaStoreVariation__flow_xintint_xt.hpp>

const bitset<2> Inter__TeaStoreVariation__flow_xintint_xt::predefined(string("11"));

Inter__TeaStoreVariation__flow_xintint_xt::Inter__TeaStoreVariation__flow_xintint_xt(const ConnT__TeaStoreVariation__flow_xintint_xt &connector) : Interaction(connector) {
    involvedPorts.reset();
    port_vector_fresh = true;
    defined = false;
    refresh_defined = false;
    mPorts.reserve(2);
}

Inter__TeaStoreVariation__flow_xintint_xt::Inter__TeaStoreVariation__flow_xintint_xt(const ConnT__TeaStoreVariation__flow_xintint_xt &connector, bool s, bool r) : Interaction(connector) {
    involvedPorts.reset();

    defined = true;
    refresh_defined = false;
	port_vector_fresh = false;

    involvedPorts.set(0, s);
    involvedPorts.set(1, r);

    defined = s && r;
    mPorts.reserve(2);
}

Inter__TeaStoreVariation__flow_xintint_xt::Inter__TeaStoreVariation__flow_xintint_xt(const ConnT__TeaStoreVariation__flow_xintint_xt &connector, const vector<Port *> &ports) : Interaction(connector), port_vector_fresh(false) {
    commonRecycle(ports);
    mPorts.reserve(2);
}

Inter__TeaStoreVariation__flow_xintint_xt::~Inter__TeaStoreVariation__flow_xintint_xt(){
}

// This one is 'const' but its only role
// is to set mPorts correctly (ie. its only role is to modify the object)
void Inter__TeaStoreVariation__flow_xintint_xt::refreshPorts() const {
    const vector<QuotedPortReference *> &parent_ports = this->connector().ports();
    mPorts.clear();
    mPorts.reserve(2);

    if (involvedPorts.test(0)) {
         mPorts.push_back(&(parent_ports[0]->port()));
    }
    if (involvedPorts.test(1)) {
         mPorts.push_back(&(parent_ports[1]->port()));
    }
    port_vector_fresh = true;
}

vector<Port*>& Inter__TeaStoreVariation__flow_xintint_xt::ports() {
    if (!port_vector_fresh){
        refreshPorts();
    }

    return mPorts;
}

const vector<Port *> & Inter__TeaStoreVariation__flow_xintint_xt::ports() const {
    if (!port_vector_fresh){
        refreshPorts();
    }

    return mPorts;
}

bool Inter__TeaStoreVariation__flow_xintint_xt::operator==(const Interaction &interaction) const {
    bool ret = false;

    // check if interaction values are from the same connector
    if (&connector() == &interaction.connector()) {
        assert(dynamic_cast<const Inter__TeaStoreVariation__flow_xintint_xt *>(&interaction) != NULL);
        const Inter__TeaStoreVariation__flow_xintint_xt *other = static_cast<const Inter__TeaStoreVariation__flow_xintint_xt *>(&interaction);
        ret = (involvedPorts == other->involvedPorts);
    }
    return ret;
}

bool Inter__TeaStoreVariation__flow_xintint_xt::operator<=(const Interaction &interaction) const {
    bool ret = false;

    // check if interaction values are from the same connector
    if (&connector() == &interaction.connector()) {
        assert(dynamic_cast<const Inter__TeaStoreVariation__flow_xintint_xt *>(&interaction) != NULL);
        const Inter__TeaStoreVariation__flow_xintint_xt *other = static_cast<const Inter__TeaStoreVariation__flow_xintint_xt *>(&interaction);
        ret = ((involvedPorts & other->involvedPorts) == involvedPorts);
    }

    return ret;
}

bool Inter__TeaStoreVariation__flow_xintint_xt::operator<(const Interaction &interaction) const {
    bool ret = false;

    // check if interaction values are from the same connector
    if (&connector() == &interaction.connector()) {
        assert(dynamic_cast<const Inter__TeaStoreVariation__flow_xintint_xt *>(&interaction) != NULL);
        const Inter__TeaStoreVariation__flow_xintint_xt *other = static_cast<const Inter__TeaStoreVariation__flow_xintint_xt *>(&interaction);
        ret = (((involvedPorts &  other->involvedPorts) == involvedPorts) &&
                (involvedPorts != other->involvedPorts));
    }

    return ret;
}

void Inter__TeaStoreVariation__flow_xintint_xt::recycle() {
    Interaction::recycle();
    mPorts.clear();
    port_vector_fresh = true;
    defined = false;
    refresh_defined = false;
    involvedPorts.reset();
}

void Inter__TeaStoreVariation__flow_xintint_xt::recycle(const vector<Port *> &ports) {
    Interaction::recycle();
    commonRecycle(ports);
}

void Inter__TeaStoreVariation__flow_xintint_xt::commonRecycle(const vector<Port *> &ports){
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
