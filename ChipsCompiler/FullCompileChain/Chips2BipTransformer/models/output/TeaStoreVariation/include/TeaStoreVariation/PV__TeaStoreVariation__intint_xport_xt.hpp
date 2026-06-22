#ifndef INCLUDE_TEASTOREVARIATION_PV____TEASTOREVARIATION____INTINT__XPORT__XT_HPP_
#define INCLUDE_TEASTOREVARIATION_PV____TEASTOREVARIATION____INTINT__XPORT__XT_HPP_

#include <PortValue.hpp>

#include <TeaStoreVariation/PT__TeaStoreVariation__intint_xport_xt.hpp>

class PV__TeaStoreVariation__intint_xport_xt : public PortValue {
public:
    PV__TeaStoreVariation__intint_xport_xt(chips_int &_m_v0, chips_int &_m_v1);
    virtual ~PV__TeaStoreVariation__intint_xport_xt();

    virtual string toString() const;


    // get/set for data.
    const chips_int& get_v0() const;
    chips_int& get_v0();
    void set_v0(const chips_int &_m_v0);

    const chips_int& get_v1() const;
    chips_int& get_v1();
    void set_v1(const chips_int &_m_v1);

private:
    // data fields from Port type.
    chips_int &m_v0;
    chips_int &m_v1;
}; 



    // get/set for data.
inline
const chips_int& PV__TeaStoreVariation__intint_xport_xt::get_v0() const {
    return m_v0;
}
inline
chips_int& PV__TeaStoreVariation__intint_xport_xt::get_v0() {
    return m_v0;
}
inline
void PV__TeaStoreVariation__intint_xport_xt::set_v0(const chips_int &_m_v0) {
    m_v0 = _m_v0;
}

inline
const chips_int& PV__TeaStoreVariation__intint_xport_xt::get_v1() const {
    return m_v1;
}
inline
chips_int& PV__TeaStoreVariation__intint_xport_xt::get_v1() {
    return m_v1;
}
inline
void PV__TeaStoreVariation__intint_xport_xt::set_v1(const chips_int &_m_v1) {
    m_v1 = _m_v1;
}


#endif // INCLUDE_TEASTOREVARIATION_PV____TEASTOREVARIATION____INTINT__XPORT__XT_HPP_
