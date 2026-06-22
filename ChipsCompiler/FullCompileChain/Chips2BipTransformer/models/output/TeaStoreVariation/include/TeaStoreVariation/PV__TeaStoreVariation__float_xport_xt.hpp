#ifndef INCLUDE_TEASTOREVARIATION_PV____TEASTOREVARIATION____FLOAT__XPORT__XT_HPP_
#define INCLUDE_TEASTOREVARIATION_PV____TEASTOREVARIATION____FLOAT__XPORT__XT_HPP_

#include <PortValue.hpp>

#include <TeaStoreVariation/PT__TeaStoreVariation__float_xport_xt.hpp>

class PV__TeaStoreVariation__float_xport_xt : public PortValue {
public:
    PV__TeaStoreVariation__float_xport_xt(chips_float &_m_v0);
    virtual ~PV__TeaStoreVariation__float_xport_xt();

    virtual string toString() const;


    // get/set for data.
    const chips_float& get_v0() const;
    chips_float& get_v0();
    void set_v0(const chips_float &_m_v0);

private:
    // data fields from Port type.
    chips_float &m_v0;
}; 



    // get/set for data.
inline
const chips_float& PV__TeaStoreVariation__float_xport_xt::get_v0() const {
    return m_v0;
}
inline
chips_float& PV__TeaStoreVariation__float_xport_xt::get_v0() {
    return m_v0;
}
inline
void PV__TeaStoreVariation__float_xport_xt::set_v0(const chips_float &_m_v0) {
    m_v0 = _m_v0;
}


#endif // INCLUDE_TEASTOREVARIATION_PV____TEASTOREVARIATION____FLOAT__XPORT__XT_HPP_
