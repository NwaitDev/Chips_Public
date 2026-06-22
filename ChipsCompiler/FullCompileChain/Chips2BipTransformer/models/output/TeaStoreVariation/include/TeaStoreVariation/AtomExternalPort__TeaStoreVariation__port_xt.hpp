#ifndef INCLUDE_TEASTOREVARIATION_ATOMEXTERNALPORT____TEASTOREVARIATION____PORT__XT_HPP_
#define INCLUDE_TEASTOREVARIATION_ATOMEXTERNALPORT____TEASTOREVARIATION____PORT__XT_HPP_

#include <AtomExternalPort.hpp>

#include <TeaStoreVariation/PT__TeaStoreVariation__port_xt.hpp>

class AtomExternalPort__TeaStoreVariation__port_xt : public AtomExternalPort {
public:
    AtomExternalPort__TeaStoreVariation__port_xt(const string &name, const EventConsumptionPolicy &policy);
    virtual ~AtomExternalPort__TeaStoreVariation__port_xt();

    virtual void initialize() { }
    virtual bool hasEvent() const { return false; }
    virtual void popEvent() { }
    virtual void purgeEvents() { }


protected:

private:
};

#endif // INCLUDE_TEASTOREVARIATION_ATOMEXTERNALPORT____TEASTOREVARIATION____PORT__XT_HPP_
