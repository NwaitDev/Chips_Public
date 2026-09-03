#ifndef CHIPS_HPP
#define CHIPS_HPP

#include <vector>
#include <numeric>      // std::accumulate
#include <stdexcept>    // std::out_of_range, std::invalid_argument, std::domain_error
#include <cstddef>      // std::size_t
#include <functional>   // std::multiplies
#include <type_traits>  // std::enable_if_t, std::conjunction_v, …
#include <algorithm>    // std::transform

/**
 * @brief Multi‑dimensional container that stores its data linearly.
 *
 * The template parameter `T` is **restricted** to `int`, `bool` or `double`.
 * All element‑wise arithmetic / logical operators are provided, but
 * increment/decrement and compound‑assignment (`+=`, `*=`, …) are deliberately
 * omitted.  Operators are only defined for chips with the **same** underlying
 * type, so `chips<int>` and `chips<double>` can never be mixed.
 *
 * **New feature:** each chip now carries an `int age_` counter (initially 0)
 * together with `tick()`, `reset()` and `is_fresh()` utilities.
 */
template <typename T>
class chips {
    static_assert(std::is_same_v<T, int>   ||
                  std::is_same_v<T, bool> ||
                  std::is_same_v<T, double>,
                  "chips<T> only supports T = int, bool or double");
public:
    using value_type = T;

    /*--------------------------  ctors  --------------------------*/
    chips() = default;

    explicit chips(const std::vector<int>& shape,
                   const std::vector<T>& flat_data = {})
        : dimensions_(static_cast<int>(shape.size())),
          shape_(shape),
          _data(flat_data),
          age_(0)                           // <-- initialise age_
    {
        const std::size_t needed = total_size();
        if (!_data.empty() && _data.size() != needed) {
            throw std::invalid_argument(
                "flat_data size does not match product of shape");
        }
        if (_data.empty())
            _data.resize(needed);
    }

    template <typename... Dims,
              typename = std::enable_if_t<
                  std::conjunction_v<std::is_integral<Dims>...>>>
    explicit chips(Dims... dims)
        : chips(std::vector<int>{static_cast<int>(dims)...})
    {}

    /*--------------------------  accessors  --------------------------*/
    int dimensions() const noexcept { return dimensions_; }
    const std::vector<int>& shape() const noexcept { return shape_; }
    const std::vector<T>& data() const noexcept { return _data; }
    std::vector<T>& data() noexcept { return _data; }

    /** New: current age of the chip (read‑only). */
    int age() const noexcept { return age_; }

    /** New: increase the internal age counter by one. */
    void tick() noexcept { ++age_; }

    /** New: reset the internal age counter to zero. */
    void reset() noexcept { age_ = 0; }

    /*--------------------------  age check   --------------------------*/

    chips<bool> is_fresh() const {
        std::vector<int> fresh_shape{1};
        std::vector<bool> fresh_data{ age_ == 0 };
        return chips<bool>(std::move(fresh_shape), std::move(fresh_data));
    }

    /*--------------------------  assignment   --------------------------*/

    chips& operator=(const chips& rhs) {
        // Guard against self‑assignment (does nothing but keeps the current age)
        if (this == &rhs) return *this;

        // The two objects must describe the same multidimensional layout.
        if (shape_ != rhs.shape_) {
            throw std::invalid_argument(
                "chips::operator= – shape mismatch between lhs and rhs");
        }

        // Copy the linearised data.
        _data = rhs._data;          // std::vector<T>::operator= does the work

        // Reset the age counter of the receiving object, as requested.
        age_ = 0;

        // dimensions_ and shape_ are already equal, so nothing else to do.
        return *this;
    }

    /*--------------------------  numeric cast  --------------------------*/

    template <typename U,
              typename = std::enable_if_t<
                  (std::is_same_v<T, int> && std::is_same_v<U, double>) ||
                  (std::is_same_v<T, double> && std::is_same_v<U, int>)>>
    explicit operator chips<U>() const
    {
        // Same shape – just copy it.
        std::vector<int> new_shape = shape_;

        // Cast every element from T to U.
        std::vector<U> new_data;
        new_data.reserve(_data.size());
        for (const T& v : _data)
            new_data.push_back(static_cast<U>(v));

        // Construct the target chip; its constructor will set age_ = 0.
        return chips<U>(std::move(new_shape), std::move(new_data));
    }

    /*--------------------------  element access  --------------------------*/
    T& operator()(const std::vector<int>& indices) {
        return _data.at(linear_index(indices));
    }
    T operator()(const std::vector<int>& indices) const {
        return _data.at(linear_index(indices));
    }

    /*--------------------------  slice operator  --------------------------*/
    chips<T> operator[](const std::vector<int>& fixed_coords) const {
        if (fixed_coords.size() > static_cast<std::size_t>(dimensions_))
            throw std::out_of_range("Too many coordinates for operator[]");

        std::vector<int> full_idx = fixed_coords;
        full_idx.resize(dimensions_, 0);
        std::size_t start = linear_index(full_idx);

        std::vector<int> sub_shape(shape_.begin() + fixed_coords.size(),
                                   shape_.end());

        std::size_t sub_len = sub_shape.empty()
                                  ? 1
                                  : std::accumulate(sub_shape.begin(),
                                                    sub_shape.end(),
                                                    std::size_t{1},
                                                    std::multiplies<std::size_t>());

        std::vector<T> sub_data(_data.begin() + start,
                                _data.begin() + start + sub_len);

        return chips<T>(std::move(sub_shape), std::move(sub_data));
    }

    /*--------------------------  utilities  --------------------------*/
    std::size_t total_size() const noexcept {
        if (shape_.empty())
            return 0;
        return std::accumulate(shape_.begin(),
                               shape_.end(),
                               std::size_t{1},
                               std::multiplies<std::size_t>());
    }

private:
    std::size_t linear_index(const std::vector<int>& indices) const {
        if (static_cast<int>(indices.size()) != dimensions_)
            throw std::out_of_range("Incorrect number of indices");

        std::size_t idx = 0;
        std::size_t stride = 1;               // product of dimensions to the right
        for (int d = dimensions_ - 1; d >= 0; --d) {
            int i   = indices[d];
            int dim = shape_[d];
            if (i < 0 || i >= dim)
                throw std::out_of_range("Index out of bounds");
            idx += static_cast<std::size_t>(i) * stride;
            stride *= static_cast<std::size_t>(dim);
        }
        return idx;
    }

    int                     dimensions_{0};
    std::vector<int>        shape_;
    std::vector<T>          _data;
    int                     age_{0};

    /*--------------------------------------------------------------------
     *  Friends – element‑wise operators (only same‑type operands)
     *--------------------------------------------------------------------*/
    // Arithmetic operators – enabled for int and double only
    template <typename U>
    friend std::enable_if_t<
        (std::is_same_v<U, int> || std::is_same_v<U, double>),
        chips<U>>
    operator+(const chips<U> &lhs, const chips<U> &rhs);

    template <typename U>
    friend std::enable_if_t<
        (std::is_same_v<U, int> || std::is_same_v<U, double>),
        chips<U>>
    operator-(const chips<U> &lhs, const chips<U> &rhs);

    template <typename U>
    friend std::enable_if_t<
        (std::is_same_v<U, int> || std::is_same_v<U, double>),
        chips<U>>
    operator*(const chips<U> &lhs, const chips<U> &rhs);

    template <typename U>
    friend std::enable_if_t<
        (std::is_same_v<U, int> || std::is_same_v<U, double>),
        chips<U>>
    operator/(const chips<U> &lhs, const chips<U> &rhs);

    // Logical operators – only for bool
    template <typename U>
    friend std::enable_if_t<std::is_same_v<U, bool>, chips<bool>>
    operator&&(const chips<U> &lhs, const chips<U> &rhs);

    template <typename U>
    friend std::enable_if_t<std::is_same_v<U, bool>, chips<bool>>
    operator||(const chips<U> &lhs, const chips<U> &rhs);

    template <typename U>
    friend std::enable_if_t<std::is_same_v<U, bool>, chips<bool>>
    operator^(const chips<U> &lhs, const chips<U> &rhs); // xor

    // Comparison operators – return chips<bool>, defined for int and double
    template <typename U>
    friend std::enable_if_t<
        (std::is_same_v<U, int> || std::is_same_v<U, double>),
        chips<bool>>
    operator==(const chips<U> &lhs, const chips<U> &rhs);

    template <typename U>
    friend std::enable_if_t<
        (std::is_same_v<U, int> || std::is_same_v<U, double>),
        chips<bool>>
    operator!=(const chips<U> &lhs, const chips<U> &rhs);

    template <typename U>
    friend std::enable_if_t<
        (std::is_same_v<U, int> || std::is_same_v<U, double>),
        chips<bool>>
    operator<(const chips<U> &lhs, const chips<U> &rhs);

    template <typename U>
    friend std::enable_if_t<
        (std::is_same_v<U, int> || std::is_same_v<U, double>),
        chips<bool>>
    operator<=(const chips<U> &lhs, const chips<U> &rhs);

    template <typename U>
    friend std::enable_if_t<
        (std::is_same_v<U, int> || std::is_same_v<U, double>),
        chips<bool>>
    operator>(const chips<U> &lhs, const chips<U> &rhs);

    template <typename U>
    friend std::enable_if_t<
        (std::is_same_v<U, int> || std::is_same_v<U, double>),
        chips<bool>>
    operator>=(const chips<U> &lhs, const chips<U> &rhs);
};

/*=====================================================================
 *  Implementation of friend operators (inline, same header)
 *=====================================================================*/

/*-----------------------  arithmetic (int / double)  -----------------------*/
template <typename U>
std::enable_if_t<(std::is_same_v<U, int> || std::is_same_v<U, double>), chips<U>>
operator+(const chips<U> &lhs, const chips<U> &rhs)
{
    if (lhs.shape() != rhs.shape())
        throw std::invalid_argument("operator+ : shape mismatch");
    chips<U> res(lhs.shape());
    std::transform(lhs.data().begin(), lhs.data().end(),
                   rhs.data().begin(),
                   res.data().begin(),
                   std::plus<U>());
    return res;
}

template <typename U>
std::enable_if_t<(std::is_same_v<U, int> || std::is_same_v<U, double>), chips<U>>
operator-(const chips<U> &lhs, const chips<U> &rhs)
{
    if (lhs.shape() != rhs.shape())
        throw std::invalid_argument("operator- : shape mismatch");
    chips<U> res(lhs.shape());
    std::transform(lhs.data().begin(), lhs.data().end(),
                   rhs.data().begin(),
                   res.data().begin(),
                   std::minus<U>());
    return res;
}

template <typename U>
std::enable_if_t<(std::is_same_v<U, int> || std::is_same_v<U, double>), chips<U>>
operator*(const chips<U> &lhs, const chips<U> &rhs)
{
    if (lhs.shape() != rhs.shape())
        throw std::invalid_argument("operator* : shape mismatch");
    chips<U> res(lhs.shape());
    std::transform(lhs.data().begin(), lhs.data().end(),
                   rhs.data().begin(),
                   res.data().begin(),
                   std::multiplies<U>());
    return res;
}

template <typename U>
std::enable_if_t<(std::is_same_v<U, int> || std::is_same_v<U, double>), chips<U>>
operator/(const chips<U> &lhs, const chips<U> &rhs)
{
    if (lhs.shape() != rhs.shape())
        throw std::invalid_argument("operator/ : shape mismatch");
    chips<U> res(lhs.shape());
    std::transform(lhs.data().begin(), lhs.data().end(),
                   rhs.data().begin(),
                   res.data().begin(),
                   [](U a, U b)
                   {
                       if (b == U{0})
                           throw std::domain_error("division by zero in chips operator/");
                       return a / b;
                   });
    return res;
}

/*-----------------------  logical (bool)  -----------------------*/
template <typename U>
std::enable_if_t<std::is_same_v<U, bool>, chips<bool>>
operator&&(const chips<U> &lhs, const chips<U> &rhs)
{
    if (lhs.shape() != rhs.shape())
        throw std::invalid_argument("operator&& : shape mismatch");
    chips<bool> res(lhs.shape());
    std::transform(lhs.data().begin(), lhs.data().end(),
                   rhs.data().begin(),
                   res.data().begin(),
                   std::logical_and<bool>());
    return res;
}

template <typename U>
std::enable_if_t<std::is_same_v<U, bool>, chips<bool>>
operator||(const chips<U> &lhs, const chips<U> &rhs)
{
    if (lhs.shape() != rhs.shape())
        throw std::invalid_argument("operator|| : shape mismatch");
    chips<bool> res(lhs.shape());
    std::transform(lhs.data().begin(), lhs.data().end(),
                   rhs.data().begin(),
                   res.data().begin(),
                   std::logical_or<bool>());
    return res;
}

template <typename U>
std::enable_if_t<std::is_same_v<U, bool>, chips<bool>>
operator^(const chips<U> &lhs, const chips<U> &rhs) // exclusive‑or
{
    if (lhs.shape() != rhs.shape())
        throw std::invalid_argument("operator^ : shape mismatch");
    chips<bool> res(lhs.shape());
    std::transform(lhs.data().begin(), lhs.data().end(),
                   rhs.data().begin(),
                   res.data().begin(),
                   std::bit_xor<bool>());
    return res;
}

/*-----------------------  comparisons (int / double)  -----------------------*/
template <typename U>
std::enable_if_t<(std::is_same_v<U, int> || std::is_same_v<U, double>), chips<bool>>
operator==(const chips<U> &lhs, const chips<U> &rhs)
{
    if (lhs.shape() != rhs.shape())
        throw std::invalid_argument("operator== : shape mismatch");
    chips<bool> res(lhs.shape());
    std::transform(lhs.data().begin(), lhs.data().end(),
                   rhs.data().begin(),
                   res.data().begin(),
                   std::equal_to<U>());
    return res;
}

template <typename U>
std::enable_if_t<(std::is_same_v<U, int> || std::is_same_v<U, double>), chips<bool>>
operator!=(const chips<U> &lhs, const chips<U> &rhs)
{
    if (lhs.shape() != rhs.shape())
        throw std::invalid_argument("operator!= : shape mismatch");
    chips<bool> res(lhs.shape());
    std::transform(lhs.data().begin(), lhs.data().end(),
                   rhs.data().begin(),
                   res.data().begin(),
                   std::not_equal_to<U>());
    return res;
}

template <typename U>
std::enable_if_t<(std::is_same_v<U, int> || std::is_same_v<U, double>), chips<bool>>
operator<(const chips<U> &lhs, const chips<U> &rhs)
{
    if (lhs.shape() != rhs.shape())
        throw std::invalid_argument("operator< : shape mismatch");
    chips<bool> res(lhs.shape());
    std::transform(lhs.data().begin(), lhs.data().end(),
                   rhs.data().begin(),
                   res.data().begin(),
                   std::less<U>());
    return res;
}

template <typename U>
std::enable_if_t<(std::is_same_v<U, int> || std::is_same_v<U, double>), chips<bool>>
operator<=(const chips<U> &lhs, const chips<U> &rhs)
{
    if (lhs.shape() != rhs.shape())
        throw std::invalid_argument("operator<= : shape mismatch");
    chips<bool> res(lhs.shape());
    std::transform(lhs.data().begin(), lhs.data().end(),
                   rhs.data().begin(),
                   res.data().begin(),
                   std::less_equal<U>());
    return res;
}

template <typename U>
std::enable_if_t<(std::is_same_v<U, int> || std::is_same_v<U, double>), chips<bool>>
operator>(const chips<U> &lhs, const chips<U> &rhs)
{
    if (lhs.shape() != rhs.shape())
        throw std::invalid_argument("operator> : shape mismatch");
    chips<bool> res(lhs.shape());
    std::transform(lhs.data().begin(), lhs.data().end(),
                   rhs.data().begin(),
                   res.data().begin(),
                   std::greater<U>());
    return res;
}

template <typename U>
std::enable_if_t<(std::is_same_v<U, int> || std::is_same_v<U, double>), chips<bool>>
operator>=(const chips<U> &lhs, const chips<U> &rhs)
{
    if (lhs.shape() != rhs.shape())
        throw std::invalid_argument("operator>= : shape mismatch");
    chips<bool> res(lhs.shape());
    std::transform(lhs.data().begin(), lhs.data().end(),
                   rhs.data().begin(),
                   res.data().begin(),
                   std::greater_equal<U>());
    return res;
}

/*-----------------------  convenient type aliases  -----------------------*/
using chips_int = chips<int>;
using chips_bool = chips<bool>;
using chips_float = chips<double>; // float name used to match the BIP compiler namings

#endif // CHIPS_HPP