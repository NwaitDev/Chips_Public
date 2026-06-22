#ifndef INCLUDE_TEASTOREVARIATION_QPR____TEASTOREVARIATION____INT__XPORT__XT_HPP_
#define INCLUDE_TEASTOREVARIATION_QPR____TEASTOREVARIATION____INT__XPORT__XT_HPP_

#include <QuotedPortReference.hpp>

#include <TeaStoreVariation/PT__TeaStoreVariation__int_xport_xt.hpp>

class QPR__TeaStoreVariation__int_xport_xt : public QuotedPortReference {
public:
    QPR__TeaStoreVariation__int_xport_xt(PT__TeaStoreVariation__int_xport_xt &port, const bool &trigger);
    virtual ~QPR__TeaStoreVariation__int_xport_xt();
}; 

#endif // INCLUDE_TEASTOREVARIATION_QPR____TEASTOREVARIATION____INT__XPORT__XT_HPP_
