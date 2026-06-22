#ifndef INCLUDE_TEASTOREVARIATION_PV____TEASTOREVARIATION____BOOL__XPORT__XT_HPP_
#define INCLUDE_TEASTOREVARIATION_PV____TEASTOREVARIATION____BOOL__XPORT__XT_HPP_

#include <PortValue.hpp>

#include <TeaStoreVariation/PT__TeaStoreVariation__bool_xport_xt.hpp>

class PV__TeaStoreVariation__bool_xport_xt : public PortValue {
public:
    PV__TeaStoreVariation__bool_xport_xt(chips_bool &_m_v0);
    virtual ~PV__TeaStoreVariation__bool_xport_xt();

    virtual string toString() const;


    // get/set for data.
    const chips_bool& get_v0() const;
    chips_bool& get_v0();
    void set_v0(const chips_bool &_m_v0);

private:
    // data fields from Port type.
    chips_bool &m_v0;
}; 



    // get/set for data.
inline
const chips_bool& PV__TeaStoreVariation__bool_xport_xt::get_v0() const {
    return m_v0;
}
inline
chips_bool& PV__TeaStoreVariation__bool_xport_xt::get_v0() {
    return m_v0;
}
inline
void PV__TeaStoreVariation__bool_xport_xt::set_v0(const chips_bool &_m_v0) {
    m_v0 = _m_v0;
}


#endif // INCLUDE_TEASTOREVARIATION_PV____TEASTOREVARIATION____BOOL__XPORT__XT_HPP_
