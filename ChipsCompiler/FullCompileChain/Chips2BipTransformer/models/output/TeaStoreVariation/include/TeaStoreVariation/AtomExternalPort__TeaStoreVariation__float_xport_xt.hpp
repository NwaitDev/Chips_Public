#ifndef INCLUDE_TEASTOREVARIATION_ATOMEXTERNALPORT____TEASTOREVARIATION____FLOAT__XPORT__XT_HPP_
#define INCLUDE_TEASTOREVARIATION_ATOMEXTERNALPORT____TEASTOREVARIATION____FLOAT__XPORT__XT_HPP_

#include <AtomExternalPort.hpp>

#include <TeaStoreVariation/PT__TeaStoreVariation__float_xport_xt.hpp>

class AtomExternalPort__TeaStoreVariation__float_xport_xt : public AtomExternalPort {
public:
    AtomExternalPort__TeaStoreVariation__float_xport_xt(const string &name, const EventConsumptionPolicy &policy);
    virtual ~AtomExternalPort__TeaStoreVariation__float_xport_xt();

    virtual void initialize() { }
    virtual bool hasEvent() const { return false; }
    virtual void popEvent() { }
    virtual void purgeEvents() { }

    virtual chips_float &lastEvent_get_v0() { return m_v0; }

protected:
    chips_float m_v0;

private:
};

#endif // INCLUDE_TEASTOREVARIATION_ATOMEXTERNALPORT____TEASTOREVARIATION____FLOAT__XPORT__XT_HPP_
