#ifndef INCLUDE_TEASTOREVARIATION_ATOMEXTERNALPORT____TEASTOREVARIATION____INT__XPORT__XT_HPP_
#define INCLUDE_TEASTOREVARIATION_ATOMEXTERNALPORT____TEASTOREVARIATION____INT__XPORT__XT_HPP_

#include <AtomExternalPort.hpp>

#include <TeaStoreVariation/PT__TeaStoreVariation__int_xport_xt.hpp>

class AtomExternalPort__TeaStoreVariation__int_xport_xt : public AtomExternalPort {
public:
    AtomExternalPort__TeaStoreVariation__int_xport_xt(const string &name, const EventConsumptionPolicy &policy);
    virtual ~AtomExternalPort__TeaStoreVariation__int_xport_xt();

    virtual void initialize() { }
    virtual bool hasEvent() const { return false; }
    virtual void popEvent() { }
    virtual void purgeEvents() { }

    virtual chips_int &lastEvent_get_v0() { return m_v0; }

protected:
    chips_int m_v0;

private:
};

#endif // INCLUDE_TEASTOREVARIATION_ATOMEXTERNALPORT____TEASTOREVARIATION____INT__XPORT__XT_HPP_
