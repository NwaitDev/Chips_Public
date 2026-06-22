#ifndef INCLUDE_TEASTOREVARIATION_ATOMEPORT____TEASTOREVARIATION____BOOL__XPORT__XT_HPP_
#define INCLUDE_TEASTOREVARIATION_ATOMEPORT____TEASTOREVARIATION____BOOL__XPORT__XT_HPP_

#include <AtomExportPort.hpp>
#include <TeaStoreVariation/AtomIPort__TeaStoreVariation__bool_xport_xt.hpp>

#include <TeaStoreVariation/PT__TeaStoreVariation__bool_xport_xt.hpp>

class AtomEPort__TeaStoreVariation__bool_xport_xt :
    public virtual Port,
    public AtomExportPort,
    public PT__TeaStoreVariation__bool_xport_xt {
public:
    AtomEPort__TeaStoreVariation__bool_xport_xt(const string &name, bool hasEarlyUpdate);
    virtual ~AtomEPort__TeaStoreVariation__bool_xport_xt();
    virtual void addInternalPort(AtomIPort__TeaStoreVariation__bool_xport_xt &p);

    virtual vector<PortValue *> &portValues();
    virtual const vector<PortValue *> &portValues() const;
    virtual bool hasPortValues() const;
    virtual void addPortValue(PortValue &port);
    virtual void clearPortValues();

    virtual bool isReset() const;
    void setIsReset(bool b);

protected:
// Getting messy to store actual type and return more abstract one (thanks to vector template...)
//    vector<PV__TeaStoreVariation__bool_xport_xt *> mPortValues;
    vector<PortValue *> mPortValues;
    bool mIsReset;
}; 


inline
void AtomEPort__TeaStoreVariation__bool_xport_xt::addInternalPort(AtomIPort__TeaStoreVariation__bool_xport_xt &p) {
    AtomExportPort::addInternalPort(p);
}

inline
vector<PortValue *> &AtomEPort__TeaStoreVariation__bool_xport_xt::portValues() {
    return mPortValues;
}

inline
const vector<PortValue *> &AtomEPort__TeaStoreVariation__bool_xport_xt::portValues() const {
    return mPortValues;
}

inline
bool AtomEPort__TeaStoreVariation__bool_xport_xt::hasPortValues() const {
    return !mPortValues.empty();
}

inline
void AtomEPort__TeaStoreVariation__bool_xport_xt::addPortValue(PortValue &port) {
    mPortValues.push_back(&port);
}

inline
void AtomEPort__TeaStoreVariation__bool_xport_xt::clearPortValues() {
    mPortValues.clear();
}

inline
bool AtomEPort__TeaStoreVariation__bool_xport_xt::isReset() const {
    return mIsReset;
}

inline
void AtomEPort__TeaStoreVariation__bool_xport_xt::setIsReset(bool b) {
    mIsReset = b;
}
#endif // INCLUDE_TEASTOREVARIATION_ATOMEPORT____TEASTOREVARIATION____BOOL__XPORT__XT_HPP_
