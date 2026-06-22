#ifndef INCLUDE_TEASTOREVARIATION_ATOMIPORT____TEASTOREVARIATION____BOOLBOOLINTINT__XPORT__XT_HPP_
#define INCLUDE_TEASTOREVARIATION_ATOMIPORT____TEASTOREVARIATION____BOOLBOOLINTINT__XPORT__XT_HPP_

#include <AtomInternalPort.hpp>

#include <TeaStoreVariation/PT__TeaStoreVariation__boolboolintint_xport_xt.hpp>
#include <TeaStoreVariation/PV__TeaStoreVariation__boolboolintint_xport_xt.hpp>

class AtomIPort__TeaStoreVariation__boolboolintint_xport_xt : public AtomInternalPort {
public:
    AtomIPort__TeaStoreVariation__boolboolintint_xport_xt(const string &name);
    virtual ~AtomIPort__TeaStoreVariation__boolboolintint_xport_xt();

    PortValue &portValue() const;
    bool hasPortValue() const;
    void setPortValue(PortValue &portValue);
    void clearPortValue();

    bool isEnabled() const;
    void setIsEnabled(bool b);
    bool isDisabledByPriorities() const;
    void setIsDisabledByPriorities(bool b);

protected:
    PV__TeaStoreVariation__boolboolintint_xport_xt *mPortValue;

private:
    bool mIsEnabled;
    bool mIsDisabledByPriorities;
}; 

inline
PortValue &AtomIPort__TeaStoreVariation__boolboolintint_xport_xt::portValue() const {
    return *mPortValue;
}

inline
bool AtomIPort__TeaStoreVariation__boolboolintint_xport_xt::hasPortValue() const {
    return mPortValue != NULL;
}

inline
void AtomIPort__TeaStoreVariation__boolboolintint_xport_xt::setPortValue(PortValue &portValue) {
    assert(dynamic_cast<PV__TeaStoreVariation__boolboolintint_xport_xt *>(&portValue) != NULL);
    mPortValue = static_cast<PV__TeaStoreVariation__boolboolintint_xport_xt *> (&portValue);
}
inline
void AtomIPort__TeaStoreVariation__boolboolintint_xport_xt::clearPortValue() {
    mPortValue = NULL;
}

inline
bool AtomIPort__TeaStoreVariation__boolboolintint_xport_xt::isEnabled() const {
    return mIsEnabled;
}

inline
void AtomIPort__TeaStoreVariation__boolboolintint_xport_xt::setIsEnabled(bool b) {
    mIsEnabled = b;
}

inline
bool AtomIPort__TeaStoreVariation__boolboolintint_xport_xt::isDisabledByPriorities() const {
    return mIsDisabledByPriorities;
}

inline
void AtomIPort__TeaStoreVariation__boolboolintint_xport_xt::setIsDisabledByPriorities(bool b) {
    mIsDisabledByPriorities = b;
}

#endif // INCLUDE_TEASTOREVARIATION_ATOMIPORT____TEASTOREVARIATION____BOOLBOOLINTINT__XPORT__XT_HPP_
