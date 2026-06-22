#ifndef INCLUDE_TEASTOREVARIATION_CONNPORT____TEASTOREVARIATION____BOOLBOOLFLOATINTINT__XPORT__XT_HPP_
#define INCLUDE_TEASTOREVARIATION_CONNPORT____TEASTOREVARIATION____BOOLBOOLFLOATINTINT__XPORT__XT_HPP_

#include <ConnectorExportPort.hpp>

#include <TeaStoreVariation/PT__TeaStoreVariation__boolboolfloatintint_xport_xt.hpp>

class ConnPort__TeaStoreVariation__boolboolfloatintint_xport_xt : public virtual Port,
                public ConnectorExportPort,
                public PT__TeaStoreVariation__boolboolfloatintint_xport_xt {
public:
    ConnPort__TeaStoreVariation__boolboolfloatintint_xport_xt(const string &name);
    virtual ~ConnPort__TeaStoreVariation__boolboolfloatintint_xport_xt();
}; 

#endif // INCLUDE_TEASTOREVARIATION_CONNPORT____TEASTOREVARIATION____BOOLBOOLFLOATINTINT__XPORT__XT_HPP_
