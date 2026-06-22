#ifndef INCLUDE_TEASTOREVARIATION_INTER____TEASTOREVARIATION____ONE2MANY__XINT__XT_HPP_
#define INCLUDE_TEASTOREVARIATION_INTER____TEASTOREVARIATION____ONE2MANY__XINT__XT_HPP_

#include <Interaction.hpp>
#include <Connector.hpp>

#include <bitset>

class Port;
class ConnT__TeaStoreVariation__one2many_xint_xt;

class PT__TeaStoreVariation__int_xport_xt;

class Inter__TeaStoreVariation__one2many_xint_xt :  public Interaction {
public:
    virtual ~Inter__TeaStoreVariation__one2many_xint_xt();

    // Implementation for get/set declared pure virtual in interface
    virtual const vector<Port *> &ports() const;
    virtual bool hasPorts() const;
    virtual void addPort(Port &port);
    virtual void removePort(Port &port);

    Inter__TeaStoreVariation__one2many_xint_xt(const ConnT__TeaStoreVariation__one2many_xint_xt &connector);
    Inter__TeaStoreVariation__one2many_xint_xt(const ConnT__TeaStoreVariation__one2many_xint_xt &connector, const vector<Port *> &ports);
    Inter__TeaStoreVariation__one2many_xint_xt(const ConnT__TeaStoreVariation__one2many_xint_xt &connector, bool p0_cppd);

    virtual void recycle();
    void recycle(const vector<Port *> &ports);

    bool operator<=(const Interaction &interaction) const;
    bool operator==(const Interaction &interaction) const;
    bool operator!=(const Interaction &interaction) const;
    bool operator<(const Interaction &interaction) const;
    bool nonEmptyIntersection(const Interaction &interaction) const;

    bool isDefined() const;
    bool hasSubDefined() const;

protected:
    // Implementation for get/set declared pure virtual in interface
    virtual vector<Port *> &ports();
    void refreshPorts() const ;
    mutable bool port_vector_fresh;
    mutable vector<Port *> mPorts;

    bitset<1> involvedPorts;

    mutable bool defined;
    mutable bool refresh_defined;

private:
    vector<Port *>::size_type findPort(const Port *p) const;
    void commonRecycle(const vector<Port *> &ports);
    bool en(size_t index) const;

    static const bitset<1> predefined;
};

inline
vector<Port *>::size_type Inter__TeaStoreVariation__one2many_xint_xt::findPort(const Port *p) const {
    vector<Port *>::size_type idx;

    idx = 0;
    for (vector<QuotedPortReference *>::const_iterator i = connector().ports().begin();
         i != connector().ports().end();
         i++, idx++) {
         if (p == &((*i)->port())) {
             break;
         }
    }
    assert(idx < connector().ports().size()); // means we couldn't find the corresponding port.
    return idx;
}

inline bool Inter__TeaStoreVariation__one2many_xint_xt::en(size_t index) const {
    return involvedPorts.test(index);
}

inline bool Inter__TeaStoreVariation__one2many_xint_xt::isDefined() const {
    if (refresh_defined) {
        refresh_defined = false;
        defined = involvedPorts == predefined;
    }
    return defined;
}

inline bool Inter__TeaStoreVariation__one2many_xint_xt::hasSubDefined() const {
    return isDefined();
}

inline
bool Inter__TeaStoreVariation__one2many_xint_xt::hasPorts() const {
    return involvedPorts.any();
}

inline
void Inter__TeaStoreVariation__one2many_xint_xt::addPort(Port &port){
    const vector<Port *>::size_type post_shift = findPort(&port);

    if (!(involvedPorts.test(post_shift))) {
        involvedPorts.set(post_shift);
        port_vector_fresh = false;
        refresh_defined = true;
    }
}

inline
void Inter__TeaStoreVariation__one2many_xint_xt::removePort(Port &port){
    const vector<Port *>::size_type post_shift = findPort(&port);

    if (involvedPorts.test(post_shift)) {
        involvedPorts.reset(post_shift);
        port_vector_fresh = false;
        refresh_defined = true;
    }
}

inline
bool Inter__TeaStoreVariation__one2many_xint_xt::operator!=(const Interaction &interaction) const {
    return ! (*this == interaction);
}

inline
bool Inter__TeaStoreVariation__one2many_xint_xt::nonEmptyIntersection(const Interaction &interaction) const {
    bool ret = false;

    // check if interactions are from the same connector
    if (&connector() == &interaction.connector()) {
        assert(dynamic_cast<const Inter__TeaStoreVariation__one2many_xint_xt *>(&interaction) != NULL);
        const Inter__TeaStoreVariation__one2many_xint_xt *other = static_cast<const Inter__TeaStoreVariation__one2many_xint_xt *>(&interaction);
        ret = ((involvedPorts & other->involvedPorts).any());
    }
    return ret;
}

#endif // INCLUDE_TEASTOREVARIATION_INTER____TEASTOREVARIATION____ONE2MANY__XINT__XT_HPP_
