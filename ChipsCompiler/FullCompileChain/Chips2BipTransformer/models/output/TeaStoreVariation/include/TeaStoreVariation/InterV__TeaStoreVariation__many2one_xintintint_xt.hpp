#ifndef INCLUDE_TEASTOREVARIATION_INTERV____TEASTOREVARIATION____MANY2ONE__XINTINTINT__XT_HPP_
#define INCLUDE_TEASTOREVARIATION_INTERV____TEASTOREVARIATION____MANY2ONE__XINTINTINT__XT_HPP_


#include <TeaStoreVariation/Inter__TeaStoreVariation__many2one_xintintint_xt.hpp>
// port values for exported port.
#include <TeaStoreVariation/PV__TeaStoreVariation__intintint_xport_xt.hpp>

class Port;
class PortValue;
class ConnT__TeaStoreVariation__many2one_xintintint_xt;

class InterV__TeaStoreVariation__many2one_xintintint_xt : public InteractionValue {
public:
    virtual ~InterV__TeaStoreVariation__many2one_xintintint_xt();

    // getters for references (declared pure virtual in interface)
    virtual const Interaction &interaction() const { return mInteraction; }
    virtual const vector<PortValue *> &portValues() const;
    virtual bool hasPortValues() const;

    // specific operations
    const vector<Port *> &ports() const { return mInteraction.ports(); }

    // Only allow the connector to call the ctor here (see createInteractionValue() method)
    friend class ConnT__TeaStoreVariation__many2one_xintintint_xt;

    // getters for data
    chips_int& cget_v0() const;
    chips_int& cget_v1() const;
    chips_int& cget_v2() const;

    // setters for non const data
    void cset_v0(chips_int __id__v0) const;
    void cset_v1(chips_int __id__v1) const;
    void cset_v2(chips_int __id__v2) const;

protected:
    InterV__TeaStoreVariation__many2one_xintintint_xt(const ConnT__TeaStoreVariation__many2one_xintintint_xt &connector, const Interaction& interaction, const vector<PortValue *> &values);
    Inter__TeaStoreVariation__many2one_xintintint_xt mInteraction;
    vector<PortValue *> &portValues();
    vector<PortValue *> mPortValues;

    void commonRecycle(const Interaction& interaction, const vector<PortValue *> &values);


    // non exported data
    mutable chips_int _id__v0;
    mutable chips_int _id__v1;
    mutable chips_int _id__v2;
    // port value used to store values of data exported through the exported port
    mutable PV__TeaStoreVariation__intintint_xport_xt mExportedPortValue;
}; 

inline
const vector<PortValue *> &InterV__TeaStoreVariation__many2one_xintintint_xt::portValues() const {
    return this->mPortValues;
}

inline
bool InterV__TeaStoreVariation__many2one_xintintint_xt::hasPortValues() const {
    return (!this->mPortValues.empty());
}

inline
vector<PortValue *> &InterV__TeaStoreVariation__many2one_xintintint_xt::portValues() {
    return mPortValues;
}


    // get/set for non exported data
inline
chips_int& InterV__TeaStoreVariation__many2one_xintintint_xt::cget_v0() const {
    return _id__v0;
}
inline
void InterV__TeaStoreVariation__many2one_xintintint_xt::cset_v0(chips_int __id__v0) const {
    _id__v0 = __id__v0;
}

inline
chips_int& InterV__TeaStoreVariation__many2one_xintintint_xt::cget_v1() const {
    return _id__v1;
}
inline
void InterV__TeaStoreVariation__many2one_xintintint_xt::cset_v1(chips_int __id__v1) const {
    _id__v1 = __id__v1;
}

inline
chips_int& InterV__TeaStoreVariation__many2one_xintintint_xt::cget_v2() const {
    return _id__v2;
}
inline
void InterV__TeaStoreVariation__many2one_xintintint_xt::cset_v2(chips_int __id__v2) const {
    _id__v2 = __id__v2;
}
#endif // INCLUDE_TEASTOREVARIATION_INTERV____TEASTOREVARIATION____MANY2ONE__XINTINTINT__XT_HPP_
