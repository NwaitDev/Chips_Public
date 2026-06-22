#ifndef INCLUDE_TEASTOREVARIATION_CPNDEPORT____TEASTOREVARIATION____BOOLBOOLINT__XPORT__XT_HPP_
#define INCLUDE_TEASTOREVARIATION_CPNDEPORT____TEASTOREVARIATION____BOOLBOOLINT__XPORT__XT_HPP_

#include <CompoundExportPort.hpp>

#include <TeaStoreVariation/PT__TeaStoreVariation__boolboolint_xport_xt.hpp>

class CpndEPort__TeaStoreVariation__boolboolint_xport_xt :
    public virtual Port,
    public CompoundExportPort,
    public PT__TeaStoreVariation__boolboolint_xport_xt {
public:
    CpndEPort__TeaStoreVariation__boolboolint_xport_xt(const string &name);
    virtual ~CpndEPort__TeaStoreVariation__boolboolint_xport_xt();
}; 

#endif // INCLUDE_TEASTOREVARIATION_CPNDEPORT____TEASTOREVARIATION____BOOLBOOLINT__XPORT__XT_HPP_
