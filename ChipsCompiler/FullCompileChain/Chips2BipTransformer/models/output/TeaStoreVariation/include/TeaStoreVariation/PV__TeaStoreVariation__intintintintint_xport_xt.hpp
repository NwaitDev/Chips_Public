#ifndef INCLUDE_TEASTOREVARIATION_PV____TEASTOREVARIATION____INTINTINTINTINT__XPORT__XT_HPP_
#define INCLUDE_TEASTOREVARIATION_PV____TEASTOREVARIATION____INTINTINTINTINT__XPORT__XT_HPP_

#include <PortValue.hpp>

#include <TeaStoreVariation/PT__TeaStoreVariation__intintintintint_xport_xt.hpp>

class PV__TeaStoreVariation__intintintintint_xport_xt : public PortValue {
public:
    PV__TeaStoreVariation__intintintintint_xport_xt(chips_int &_m_v0, chips_int &_m_v1, chips_int &_m_v2, chips_int &_m_v3, chips_int &_m_v4);
    virtual ~PV__TeaStoreVariation__intintintintint_xport_xt();

    virtual string toString() const;


    // get/set for data.
    const chips_int& get_v0() const;
    chips_int& get_v0();
    void set_v0(const chips_int &_m_v0);

    const chips_int& get_v1() const;
    chips_int& get_v1();
    void set_v1(const chips_int &_m_v1);

    const chips_int& get_v2() const;
    chips_int& get_v2();
    void set_v2(const chips_int &_m_v2);

    const chips_int& get_v3() const;
    chips_int& get_v3();
    void set_v3(const chips_int &_m_v3);

    const chips_int& get_v4() const;
    chips_int& get_v4();
    void set_v4(const chips_int &_m_v4);

private:
    // data fields from Port type.
    chips_int &m_v0;
    chips_int &m_v1;
    chips_int &m_v2;
    chips_int &m_v3;
    chips_int &m_v4;
}; 



    // get/set for data.
inline
const chips_int& PV__TeaStoreVariation__intintintintint_xport_xt::get_v0() const {
    return m_v0;
}
inline
chips_int& PV__TeaStoreVariation__intintintintint_xport_xt::get_v0() {
    return m_v0;
}
inline
void PV__TeaStoreVariation__intintintintint_xport_xt::set_v0(const chips_int &_m_v0) {
    m_v0 = _m_v0;
}

inline
const chips_int& PV__TeaStoreVariation__intintintintint_xport_xt::get_v1() const {
    return m_v1;
}
inline
chips_int& PV__TeaStoreVariation__intintintintint_xport_xt::get_v1() {
    return m_v1;
}
inline
void PV__TeaStoreVariation__intintintintint_xport_xt::set_v1(const chips_int &_m_v1) {
    m_v1 = _m_v1;
}

inline
const chips_int& PV__TeaStoreVariation__intintintintint_xport_xt::get_v2() const {
    return m_v2;
}
inline
chips_int& PV__TeaStoreVariation__intintintintint_xport_xt::get_v2() {
    return m_v2;
}
inline
void PV__TeaStoreVariation__intintintintint_xport_xt::set_v2(const chips_int &_m_v2) {
    m_v2 = _m_v2;
}

inline
const chips_int& PV__TeaStoreVariation__intintintintint_xport_xt::get_v3() const {
    return m_v3;
}
inline
chips_int& PV__TeaStoreVariation__intintintintint_xport_xt::get_v3() {
    return m_v3;
}
inline
void PV__TeaStoreVariation__intintintintint_xport_xt::set_v3(const chips_int &_m_v3) {
    m_v3 = _m_v3;
}

inline
const chips_int& PV__TeaStoreVariation__intintintintint_xport_xt::get_v4() const {
    return m_v4;
}
inline
chips_int& PV__TeaStoreVariation__intintintintint_xport_xt::get_v4() {
    return m_v4;
}
inline
void PV__TeaStoreVariation__intintintintint_xport_xt::set_v4(const chips_int &_m_v4) {
    m_v4 = _m_v4;
}


#endif // INCLUDE_TEASTOREVARIATION_PV____TEASTOREVARIATION____INTINTINTINTINT__XPORT__XT_HPP_
