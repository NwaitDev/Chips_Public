#ifndef INCLUDE_TEASTOREVARIATION_QPR____TEASTOREVARIATION____PORT__XT_HPP_
#define INCLUDE_TEASTOREVARIATION_QPR____TEASTOREVARIATION____PORT__XT_HPP_

#include <QuotedPortReference.hpp>

#include <TeaStoreVariation/PT__TeaStoreVariation__port_xt.hpp>

class QPR__TeaStoreVariation__port_xt : public QuotedPortReference {
public:
    QPR__TeaStoreVariation__port_xt(PT__TeaStoreVariation__port_xt &port, const bool &trigger);
    virtual ~QPR__TeaStoreVariation__port_xt();
}; 

#endif // INCLUDE_TEASTOREVARIATION_QPR____TEASTOREVARIATION____PORT__XT_HPP_
