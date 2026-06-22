#ifndef INCLUDE_TEASTOREVARIATION_ATOMEXTERNALPORT____TEASTOREVARIATION____INTINTINTINTINT__XPORT__XT_HPP_
#define INCLUDE_TEASTOREVARIATION_ATOMEXTERNALPORT____TEASTOREVARIATION____INTINTINTINTINT__XPORT__XT_HPP_

#include <AtomExternalPort.hpp>

#include <TeaStoreVariation/PT__TeaStoreVariation__intintintintint_xport_xt.hpp>

class AtomExternalPort__TeaStoreVariation__intintintintint_xport_xt : public AtomExternalPort {
public:
    AtomExternalPort__TeaStoreVariation__intintintintint_xport_xt(const string &name, const EventConsumptionPolicy &policy);
    virtual ~AtomExternalPort__TeaStoreVariation__intintintintint_xport_xt();

    virtual void initialize() { }
    virtual bool hasEvent() const { return false; }
    virtual void popEvent() { }
    virtual void purgeEvents() { }

    virtual chips_int &lastEvent_get_v0() { return m_v0; }
    virtual chips_int &lastEvent_get_v1() { return m_v1; }
    virtual chips_int &lastEvent_get_v2() { return m_v2; }
    virtual chips_int &lastEvent_get_v3() { return m_v3; }
    virtual chips_int &lastEvent_get_v4() { return m_v4; }

protected:
    chips_int m_v0;
    chips_int m_v1;
    chips_int m_v2;
    chips_int m_v3;
    chips_int m_v4;

private:
};

#endif // INCLUDE_TEASTOREVARIATION_ATOMEXTERNALPORT____TEASTOREVARIATION____INTINTINTINTINT__XPORT__XT_HPP_
