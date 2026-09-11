#ifndef CHIPS_HPP
#define CHIPS_HPP

#include <vector>
#include <numeric>
#include <stdexcept>
#include <cstddef>
#include <functional>
#include <type_traits>
#include <algorithm>
#include <random>
#include <variant>

class chips_any;


/**
 * @brief Multi‑dimensional container that stores its data linearly.
 */
template <typename T>
class chips
{
    static_assert(std::is_same_v<T, int> ||
                      std::is_same_v<T, bool> ||
                      std::is_same_v<T, double>,
                  "chips<T> only supports T = int, bool or double");

public:
    using value_type = T;

    /*--------------------------  ctors  --------------------------*/
    chips() = default;

    explicit chips(const std::vector<int> &shape,
                   const std::vector<T> &flatdata_ = {})
        : dimensions_(static_cast<int>(shape.size())),
          shape_(shape),
          data_(flatdata_),
          age_(0)
    {
        const std::size_t needed = total_size();
        if (!data_.empty() && data_.size() != needed)
        {
            throw std::invalid_argument(
                "flatdata_ size does not match product of shape");
        }
        if (data_.empty())
            data_.resize(needed);
    }

    template <typename... Dims,
              typename = std::enable_if_t<
                  std::conjunction_v<std::is_integral<Dims>...>>>
    explicit chips(Dims... dims)
        : chips(std::vector<int>{static_cast<int>(dims)...})
    {
    }

    /*--------------------------  accessors  --------------------------*/
    int dimensions() const noexcept { return dimensions_; }
    const std::vector<int> &shape() const noexcept { return shape_; }
    const std::vector<T> &data() const noexcept { return data_; }
    std::vector<T> &data() noexcept { return data_; }

    int age() const noexcept { return age_; }

    void tick() noexcept { ++age_; }

    void reset() noexcept { age_ = 0; }

    /*--------------------------  age check   --------------------------*/

    chips<bool> is_fresh() const
    {
        std::vector<int> fresh_shape{1};
        std::vector<bool> freshdata_{age_ == 0};
        return chips<bool>(std::move(fresh_shape), std::move(freshdata_));
    }

    /*--------------------------  assignment   --------------------------*/

    chips &operator=(const chips &rhs)
    {
        if (this == &rhs)
            return *this;

        if (shape_ != rhs.shape_)
        {
            throw std::invalid_argument(
                "chips::operator= – shape mismatch between lhs and rhs");
        }

        data_ = rhs.data_;

        age_ = 0;

        return *this;
    }

    /*--------------------------  chips_any interop  --------------------------*/
    // Definitions are out-of-line, after chips_any is fully declared below.
    explicit chips(const chips_any &rhs);
    chips &operator=(const chips_any &rhs);

    template <typename U = T,
              typename = std::enable_if_t<
                  (std::is_same_v<U, int> && std::is_same_v<T, int>) ||
                  (std::is_same_v<U, double> && std::is_same_v<T, double>) ||
                  (std::is_same_v<U, bool> && std::is_same_v<T, bool>)>>
    chips &operator=(U scalar)
    {
        // shape becomes a single element {1}
        shape_ = std::vector<int>{1};
        dimensions_ = 1;

        data_.clear();
        data_.push_back(static_cast<T>(scalar));
        age_ = 0;
        return *this;
    }

    template <typename U = T,
              typename = std::enable_if_t<
                  (std::is_same_v<U, int> && std::is_same_v<T, int>) ||
                  (std::is_same_v<U, double> && std::is_same_v<T, double>) ||
                  (std::is_same_v<U, bool> && std::is_same_v<T, bool>)>>
    chips(U scalar)
        : dimensions_(1),
          shape_{1},
          data_{static_cast<T>(scalar)},
          age_(0)
    {
    }

    /*--------------------------  numeric cast  --------------------------*/

    template <typename U,
              typename = std::enable_if_t<
                  (std::is_same_v<T, int> && std::is_same_v<U, double>) ||
                  (std::is_same_v<T, double> && std::is_same_v<U, int>)>>
    explicit operator chips<U>() const
    {
        std::vector<int> new_shape = shape_;

        std::vector<U> newdata_;
        newdata_.reserve(data_.size());
        for (const T &v : data_)
            newdata_.push_back(static_cast<U>(v));

        return chips<U>(std::move(new_shape), std::move(newdata_));
    }

    /*--------------------------  element access  --------------------------*/
    T &operator()(const std::vector<int> &indices)
    {
        return data_.at(linear_index(indices));
    }
    T operator()(const std::vector<int> &indices) const
    {
        return data_.at(linear_index(indices));
    }

    /*--------------------------  slice operator  --------------------------*/

private:
    std::size_t linear_index(const std::vector<int> &indices) const
    {
        if (static_cast<int>(indices.size()) != dimensions_)
            throw std::out_of_range("Incorrect number of indices");

        std::size_t idx = 0;
        std::size_t stride = 1;
        for (int d = dimensions_ - 1; d >= 0; --d)
        {
            int i = indices[d];
            int dim = shape_[d];
            if (i < 0 || i >= dim)
                throw std::out_of_range("Index out of bounds");
            idx += static_cast<std::size_t>(i) * stride;
            stride *= static_cast<std::size_t>(dim);
        }
        return idx;
    }

    class slice_proxy {
        chips*                parent_;
        std::vector<int>      fixed_;

        std::size_t linear_index_in_parent(std::size_t pos) const {
            std::vector<int> idx = fixed_;
            std::size_t stride = 1;
            for (int d = static_cast<int>(parent_->dimensions_) - 1;
                 d >= static_cast<int>(fixed_.size()); --d) {
                int cur = static_cast<int>((pos / stride) % parent_->shape_[d]);
                idx.push_back(cur);
                stride *= static_cast<std::size_t>(parent_->shape_[d]);
            }
            return parent_->linear_index(idx);
        }

    public:
        explicit slice_proxy(chips* p, const chips<int>& c)
            : parent_(p) {
            fixed_.push_back(static_cast<int>(c.data()[0]));
        }

        slice_proxy operator[](const chips<int>& c) const {
            slice_proxy nxt(*this);
            nxt.fixed_.push_back(static_cast<int>(c.data()[0]));
            return nxt;
        }

        operator chips<T>() const {
            if (fixed_.size() > static_cast<std::size_t>(parent_->dimensions_))
                throw std::out_of_range("Too many coordinates");
            std::vector<int> full_idx = fixed_;
            full_idx.resize(parent_->dimensions_, 0);
            std::size_t start = parent_->linear_index(full_idx);
            std::vector<int> sub_shape(parent_->shape_.begin() + fixed_.size(),
                                       parent_->shape_.end());
            std::size_t sub_len = sub_shape.empty()
                ? 1
                : std::accumulate(sub_shape.begin(), sub_shape.end(),
                                  std::size_t{1}, std::multiplies<std::size_t>());
            std::vector<T> sub_data(parent_->data_.begin() + static_cast<std::ptrdiff_t>(start),
                                    parent_->data_.begin() + static_cast<std::ptrdiff_t>(start + sub_len));
            return chips<T>(std::move(sub_shape), std::move(sub_data));
        }

        // Explicit equivalent of the implicit conversion above, for contexts
        // (auto deduction, template argument deduction) where the implicit
        // conversion operator is not considered by the compiler.
        chips<T> to_chips() const {
            return static_cast<chips<T>>(*this);
        }

        class iterator {
            const slice_proxy* owner_;
            std::size_t        pos_;
        public:
            using iterator_category = std::random_access_iterator_tag;
            using value_type        = T;
            using difference_type   = std::ptrdiff_t;
            using pointer           = T*;
            using reference         = T&;

            iterator(const slice_proxy* o, std::size_t p) : owner_(o), pos_(p) {}

            reference operator*() const {
                std::size_t lin = owner_->linear_index_in_parent(pos_);
                return const_cast<T&>(owner_->parent_->data_[lin]);
            }
            pointer operator->() const { return &**this; }

            iterator& operator++() { ++pos_; return *this; }
            iterator  operator++(int) { iterator tmp=*this; ++(*this); return tmp; }
            iterator& operator--() { --pos_; return *this; }
            iterator  operator--(int) { iterator tmp=*this; --(*this); return tmp; }
            iterator& operator+=(difference_type n){ pos_+=n; return *this; }
            iterator  operator+ (difference_type n) const { return iterator(*this)+=n; }
            iterator& operator-=(difference_type n){ pos_-=n; return *this; }
            iterator  operator- (difference_type n) const { return iterator(*this)-=n; }
            difference_type operator-(const iterator& o) const {
                return static_cast<difference_type>(pos_) - static_cast<difference_type>(o.pos_);
            }
            bool operator==(const iterator& o) const { return pos_==o.pos_; }
            bool operator!=(const iterator& o) const { return !(*this==o); }
            bool operator<(const iterator& o) const { return pos_<o.pos_; }
            bool operator>(const iterator& o) const { return pos_>o.pos_; }
            bool operator<=(const iterator& o) const { return pos_<=o.pos_; }
            bool operator>=(const iterator& o) const { return pos_>=o.pos_; }
        };

        iterator begin() const {
            std::size_t len = 1;
            for (std::size_t i = fixed_.size(); i < parent_->dimensions_; ++i)
                len *= static_cast<std::size_t>(parent_->shape_[i]);
            return iterator(this, 0);
        }

        iterator end() const {
            std::size_t len = 1;
            for (std::size_t i = fixed_.size(); i < parent_->dimensions_; ++i)
                len *= static_cast<std::size_t>(parent_->shape_[i]);
            return iterator(this, len);
        }
    };

public:
    slice_proxy operator[](const chips<int>& coord) {
        return slice_proxy(this, coord);
    }

    chips<T> operator[](const chips<int>& coord) const {
        std::vector<int> idx{ static_cast<int>(coord.data()[0]) };
        idx.resize(dimensions_, 0);
        std::size_t start = linear_index(idx);
        std::vector<int> sub_shape(shape_.begin() + 1, shape_.end());
        std::size_t sub_len = sub_shape.empty()
            ? 1
            : std::accumulate(sub_shape.begin(), sub_shape.end(),
                              std::size_t{1}, std::multiplies<std::size_t>());
        std::vector<T> sub_data(data_.begin() + static_cast<std::ptrdiff_t>(start),
                                data_.begin() + static_cast<std::ptrdiff_t>(start + sub_len));
        return chips<T>(std::move(sub_shape), std::move(sub_data));
    }

    class slice_iterator {
        chips* parent_;
        std::size_t idx_;

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = chips;
        using difference_type   = std::ptrdiff_t;
        using pointer           = void;
        using reference         = chips;

        slice_iterator(chips* parent, std::size_t idx)
            : parent_(parent), idx_(idx) {}
        
        slice_iterator& operator++() {
            ++idx_;
            return *this;
        }
        
        slice_iterator operator++(int) {
            slice_iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        
        bool operator==(const slice_iterator& other) const {
            return parent_ == other.parent_ && idx_ == other.idx_;
        }
        bool operator!=(const slice_iterator& other) const {
            return !(*this == other);
        }

        
        chips operator*() const {
            return (*parent_)[std::vector<int>{static_cast<int>(idx_)}];
        }
    };
    
    class const_slice_iterator {
        const chips* parent_;
        std::size_t idx_;

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = chips;
        using difference_type   = std::ptrdiff_t;
        using pointer           = void;
        using reference         = chips;

        const_slice_iterator(const chips* parent, std::size_t idx)
            : parent_(parent), idx_(idx) {}

        const_slice_iterator& operator++() { ++idx_; return *this; }
        const_slice_iterator operator++(int) {
            const_slice_iterator tmp = *this; ++(*this); return tmp;
        }
        bool operator==(const const_slice_iterator& o) const {
            return parent_ == o.parent_ && idx_ == o.idx_;
        }
        bool operator!=(const const_slice_iterator& o) const { return !(*this == o); }

        chips operator*() const {
            return (*parent_)[std::vector<int>{static_cast<int>(idx_)}];
        }
    };

    slice_iterator begin() {
        return slice_iterator(this, 0);
    }
    slice_iterator end() {
        // nombre de slices = taille de la première dimension
        return slice_iterator(this, static_cast<std::size_t>(shape_.front()));
    }

    const_slice_iterator begin() const {
        return const_slice_iterator(this, 0);
    }
    const_slice_iterator end() const {
        return const_slice_iterator(this, static_cast<std::size_t>(shape_.front()));
    }

    const_slice_iterator cbegin() const { return begin(); }
    const_slice_iterator cend()   const { return end();   }

    /*---------------------  bool interpretable  ---------------------*/

    template <typename U = T,
              std::enable_if_t<std::is_same_v<U, bool>, int> = 0>
    explicit operator bool() const
    {
        if (shape_.size() == 1 && shape_[0] == 1)
        {
            return data_.empty() ? false : data_[0];
        }

        return std::all_of(data_.begin(), data_.end(),
                           [](bool v)
                           { return v; });
        // may be used with "any" instead of "all"
    }

    /*--------------------------  unary operators  --------------------------*/
    template <typename U = T,
              typename = std::enable_if_t<
                  std::is_same_v<U, int> || std::is_same_v<U, double>>>
    chips<T> operator-() const
    {
        chips<T> res(shape_);
        res.stopFlag = stopFlag;
        if (!res.stopFlag)
        {
            std::transform(data_.begin(), data_.end(), res.data().begin(),
                           [](const T &v) { return -v; });
        }
        return res;
    }

    template <typename U = T,
              typename = std::enable_if_t<std::is_same_v<U, bool>>>
    chips<bool> operator!() const
    {
        chips<bool> res(shape_);
        res.stopFlag = stopFlag;
        if (!res.stopFlag)
        {
            std::transform(data_.begin(), data_.end(), res.data().begin(),
                           [](bool v) { return !v; });
        }
        return res;
    }

    /*--------------------------  utilities  --------------------------*/
    std::size_t total_size() const noexcept
    {
        if (shape_.empty())
            return 0;
        return std::accumulate(shape_.begin(),
                               shape_.end(),
                               std::size_t{1},
                               std::multiplies<std::size_t>());
    }

    chips<int> size() const noexcept
    {
        if (shape_.empty())
            return 0;
        return chips<int>{shape_[0]};
    }

private:

    int dimensions_{0};
    std::vector<int> shape_;
    std::vector<T> data_;
    int age_{0};

public:
    bool stopFlag{false};

private:

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

    // mod operator only for integers
    friend chips<int> operator%(const chips<int> &lhs, const chips<int> &rhs);

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
 *  Implementation of friend operators
 *=====================================================================*/

/*-----------------------  arithmetic (int / double)  -----------------------*/
template <typename U>
std::enable_if_t<(std::is_same_v<U, int> || std::is_same_v<U, double>), chips<U>>
operator+(const chips<U> &lhs, const chips<U> &rhs)
{
    if (lhs.shape() != rhs.shape())
        throw std::invalid_argument("operator+ : shape mismatch");
    chips<U> res(lhs.shape());
    res.stopFlag = lhs.stopFlag || rhs.stopFlag;
    if (!res.stopFlag)
    {
        std::transform(lhs.data().begin(), lhs.data().end(),
                       rhs.data().begin(),
                       res.data().begin(),
                       std::plus<U>());
    }
    return res;
}

template <typename U>
std::enable_if_t<(std::is_same_v<U, int> || std::is_same_v<U, double>), chips<U>>
operator-(const chips<U> &lhs, const chips<U> &rhs)
{
    if (lhs.shape() != rhs.shape())
        throw std::invalid_argument("operator- : shape mismatch");
    chips<U> res(lhs.shape());
    res.stopFlag = lhs.stopFlag || rhs.stopFlag;
    if (!res.stopFlag)
    {
        std::transform(lhs.data().begin(), lhs.data().end(),
                       rhs.data().begin(),
                       res.data().begin(),
                       std::minus<U>());
    }
    return res;
}

template <typename U>
std::enable_if_t<(std::is_same_v<U, int> || std::is_same_v<U, double>), chips<U>>
operator*(const chips<U> &lhs, const chips<U> &rhs)
{
    if (lhs.shape() != rhs.shape())
        throw std::invalid_argument("operator* : shape mismatch");
    chips<U> res(lhs.shape());
    res.stopFlag = lhs.stopFlag || rhs.stopFlag;
    if (!res.stopFlag)
    {
        std::transform(lhs.data().begin(), lhs.data().end(),
                       rhs.data().begin(),
                       res.data().begin(),
                       std::multiplies<U>());
    }
    return res;
}

template <typename U>
std::enable_if_t<(std::is_same_v<U, int> || std::is_same_v<U, double>), chips<U>>
operator/(const chips<U> &lhs, const chips<U> &rhs)
{
    if (lhs.shape() != rhs.shape())
        throw std::invalid_argument("operator/ : shape mismatch");
    chips<U> res(lhs.shape());
    res.stopFlag = lhs.stopFlag || rhs.stopFlag;
    if (!res.stopFlag)
    {
        std::transform(lhs.data().begin(), lhs.data().end(),
                       rhs.data().begin(),
                       res.data().begin(),
                       [](U a, U b)
                       {
                           if (b == U{0})
                               throw std::domain_error("division by zero in chips operator/");
                           return a / b;
                       });
    }
    return res;
}

/*-----------------------  modulo (int only)  ---------------------*/
chips<int> operator%(const chips<int> &lhs, const chips<int> &rhs)
{
    if (lhs.shape() != rhs.shape())
        throw std::invalid_argument("operator% : shape mismatch");
    chips<int> res(lhs.shape());
    res.stopFlag = lhs.stopFlag || rhs.stopFlag;
    if (!res.stopFlag)
    {
        std::transform(lhs.data().begin(), lhs.data().end(),
                       rhs.data().begin(),
                       res.data().begin(),
                       [](int a, int b)
                       {
                           if (b == 0)
                               throw std::domain_error("modulo by zero in chips operator%");
                           return a%b;
                       });
    }
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
    res.stopFlag = lhs.stopFlag || rhs.stopFlag;
    if (!res.stopFlag)
    {
        std::transform(lhs.data().begin(), lhs.data().end(),
                       rhs.data().begin(),
                       res.data().begin(),
                       std::logical_and<bool>());
    }
    return res;
}

template <typename U>
std::enable_if_t<std::is_same_v<U, bool>, chips<bool>>
operator||(const chips<U> &lhs, const chips<U> &rhs)
{
    if (lhs.shape() != rhs.shape())
        throw std::invalid_argument("operator|| : shape mismatch");
    chips<bool> res(lhs.shape());
    res.stopFlag = lhs.stopFlag || rhs.stopFlag;
    if (!res.stopFlag)
    {
        std::transform(lhs.data().begin(), lhs.data().end(),
                       rhs.data().begin(),
                       res.data().begin(),
                       std::logical_or<bool>());
    }
    return res;
}

template <typename U>
std::enable_if_t<std::is_same_v<U, bool>, chips<bool>>
operator^(const chips<U> &lhs, const chips<U> &rhs) // exclusive‑or
{
    if (lhs.shape() != rhs.shape())
        throw std::invalid_argument("operator^ : shape mismatch");
    chips<bool> res(lhs.shape());
    res.stopFlag = lhs.stopFlag || rhs.stopFlag;
    if (!res.stopFlag)
    {
        std::transform(lhs.data().begin(), lhs.data().end(),
                       rhs.data().begin(),
                       res.data().begin(),
                       std::bit_xor<bool>());
    }
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
    res.stopFlag = lhs.stopFlag || rhs.stopFlag;
    if (!res.stopFlag)
    {
        std::transform(lhs.data().begin(), lhs.data().end(),
                       rhs.data().begin(),
                       res.data().begin(),
                       std::equal_to<U>());
    }
    return res;
}

template <typename U>
std::enable_if_t<(std::is_same_v<U, int> || std::is_same_v<U, double>), chips<bool>>
operator!=(const chips<U> &lhs, const chips<U> &rhs)
{
    if (lhs.shape() != rhs.shape())
        throw std::invalid_argument("operator!= : shape mismatch");
    chips<bool> res(lhs.shape());
    res.stopFlag = lhs.stopFlag || rhs.stopFlag;
    if (!res.stopFlag)
    {
        std::transform(lhs.data().begin(), lhs.data().end(),
                       rhs.data().begin(),
                       res.data().begin(),
                       std::not_equal_to<U>());
    }
    return res;
}

template <typename U>
std::enable_if_t<(std::is_same_v<U, int> || std::is_same_v<U, double>), chips<bool>>
operator<(const chips<U> &lhs, const chips<U> &rhs)
{
    if (lhs.shape() != rhs.shape())
        throw std::invalid_argument("operator< : shape mismatch");
    chips<bool> res(lhs.shape());
    res.stopFlag = lhs.stopFlag || rhs.stopFlag;
    if (!res.stopFlag)
    {
        std::transform(lhs.data().begin(), lhs.data().end(),
                       rhs.data().begin(),
                       res.data().begin(),
                       std::less<U>());
    }
    return res;
}

template <typename U>
std::enable_if_t<(std::is_same_v<U, int> || std::is_same_v<U, double>), chips<bool>>
operator<=(const chips<U> &lhs, const chips<U> &rhs)
{
    if (lhs.shape() != rhs.shape())
        throw std::invalid_argument("operator<= : shape mismatch");
    chips<bool> res(lhs.shape());
    res.stopFlag = lhs.stopFlag || rhs.stopFlag;
    if (!res.stopFlag)
    {
        std::transform(lhs.data().begin(), lhs.data().end(),
                       rhs.data().begin(),
                       res.data().begin(),
                       std::less_equal<U>());
    }
    return res;
}

template <typename U>
std::enable_if_t<(std::is_same_v<U, int> || std::is_same_v<U, double>), chips<bool>>
operator>(const chips<U> &lhs, const chips<U> &rhs)
{
    if (lhs.shape() != rhs.shape())
        throw std::invalid_argument("operator> : shape mismatch");
    chips<bool> res(lhs.shape());
    res.stopFlag = lhs.stopFlag || rhs.stopFlag;
    if (!res.stopFlag)
    {
        std::transform(lhs.data().begin(), lhs.data().end(),
                       rhs.data().begin(),
                       res.data().begin(),
                       std::greater<U>());
    }
    return res;
}

template <typename U>
std::enable_if_t<(std::is_same_v<U, int> || std::is_same_v<U, double>), chips<bool>>
operator>=(const chips<U> &lhs, const chips<U> &rhs)
{
    if (lhs.shape() != rhs.shape())
        throw std::invalid_argument("operator>= : shape mismatch");
    chips<bool> res(lhs.shape());
    res.stopFlag = lhs.stopFlag || rhs.stopFlag;
    if (!res.stopFlag)
    {
        std::transform(lhs.data().begin(), lhs.data().end(),
                       rhs.data().begin(),
                       res.data().begin(),
                       std::greater_equal<U>());
    }
    return res;
}

/*-----------------------  convenient type aliases  -----------------------*/

using chips_int = chips<int>;
using chips_bool = chips<bool>;
using chips_float = chips<double>; // float name used to match the BIP compiler namings




/*=====================================================================
 *  chips_any : type-erased holder for one of chips_int/chips_bool/chips_float
 *  Used by the code generator when a static type cannot be resolved
 *  (e.g. forward-referenced loop variables, unresolved function returns).
 *=====================================================================*/
class chips_any
{
public:
    using storage_type = std::variant<chips_int, chips_bool, chips_float>;

    chips_any() = default;
    chips_any(chips_int v) : value_(std::move(v)) {}
    chips_any(chips_bool v) : value_(std::move(v)) {}
    chips_any(chips_float v) : value_(std::move(v)) {}

    const storage_type &value() const noexcept { return value_; }
    storage_type &value() noexcept { return value_; }

    // enables static_cast<chips_int>(someChipsAny), etc.
    template <typename U>
    explicit operator U() const
    {
        if (const U *p = std::get_if<U>(&value_))
            return *p;
        throw std::bad_variant_access();
    }

private:
    storage_type value_;
};

namespace chips_any_detail
{
    template <typename BinOp>
    chips_any visit_binary(const chips_any &lhs, const chips_any &rhs, BinOp &&op, const char *opName)
    {
        return std::visit([&](const auto &a, const auto &b) -> chips_any
        {
            using L = std::decay_t<decltype(a)>;
            using R = std::decay_t<decltype(b)>;
            if constexpr (std::is_same_v<L, R>)
                return op(a, b);
            else
                throw std::invalid_argument(std::string("chips_any ") + opName + " : mismatched underlying types");
        }, lhs.value(), rhs.value());
    }

    template <typename UnOp>
    chips_any visit_unary(const chips_any &v, UnOp &&op, const char *opName)
    {
        return std::visit([&](const auto &a) -> chips_any
        {
            using A = std::decay_t<decltype(a)>;
            if constexpr (std::is_invocable_v<UnOp, const A &>)
                return op(a);
            else
                throw std::invalid_argument(std::string("chips_any ") + opName + " : unsupported underlying type");
        }, v.value());
    }
}

inline chips_any operator+(const chips_any &lhs, const chips_any &rhs)
{ return chips_any_detail::visit_binary(lhs, rhs, [](const auto &a, const auto &b) { return a + b; }, "operator+"); }

inline chips_any operator-(const chips_any &lhs, const chips_any &rhs)
{ return chips_any_detail::visit_binary(lhs, rhs, [](const auto &a, const auto &b) { return a - b; }, "operator-"); }

inline chips_any operator*(const chips_any &lhs, const chips_any &rhs)
{ return chips_any_detail::visit_binary(lhs, rhs, [](const auto &a, const auto &b) { return a * b; }, "operator*"); }

inline chips_any operator/(const chips_any &lhs, const chips_any &rhs)
{ return chips_any_detail::visit_binary(lhs, rhs, [](const auto &a, const auto &b) { return a / b; }, "operator/"); }

inline chips_any operator%(const chips_any &lhs, const chips_any &rhs)
{ return chips_any_detail::visit_binary(lhs, rhs, [](const auto &a, const auto &b) { return a % b; }, "operator%"); }

inline chips_any operator&&(const chips_any &lhs, const chips_any &rhs)
{ return chips_any_detail::visit_binary(lhs, rhs, [](const auto &a, const auto &b) { return a && b; }, "operator&&"); }

inline chips_any operator||(const chips_any &lhs, const chips_any &rhs)
{ return chips_any_detail::visit_binary(lhs, rhs, [](const auto &a, const auto &b) { return a || b; }, "operator||"); }

inline chips_any operator==(const chips_any &lhs, const chips_any &rhs)
{ return chips_any_detail::visit_binary(lhs, rhs, [](const auto &a, const auto &b) { return a == b; }, "operator=="); }

inline chips_any operator!=(const chips_any &lhs, const chips_any &rhs)
{ return chips_any_detail::visit_binary(lhs, rhs, [](const auto &a, const auto &b) { return a != b; }, "operator!="); }

inline chips_any operator<(const chips_any &lhs, const chips_any &rhs)
{ return chips_any_detail::visit_binary(lhs, rhs, [](const auto &a, const auto &b) { return a < b; }, "operator<"); }

inline chips_any operator<=(const chips_any &lhs, const chips_any &rhs)
{ return chips_any_detail::visit_binary(lhs, rhs, [](const auto &a, const auto &b) { return a <= b; }, "operator<="); }

inline chips_any operator>(const chips_any &lhs, const chips_any &rhs)
{ return chips_any_detail::visit_binary(lhs, rhs, [](const auto &a, const auto &b) { return a > b; }, "operator>"); }

inline chips_any operator>=(const chips_any &lhs, const chips_any &rhs)
{ return chips_any_detail::visit_binary(lhs, rhs, [](const auto &a, const auto &b) { return a >= b; }, "operator>="); }

inline chips_any operator-(const chips_any &v)
{ return chips_any_detail::visit_unary(v, [](const auto &a) { return -a; }, "unary operator-"); }

inline chips_any operator!(const chips_any &v)
{ return chips_any_detail::visit_unary(v, [](const auto &a) { return !a; }, "unary operator!"); }


template <typename T>
chips<T>::chips(const chips_any &rhs)
{
    *this = static_cast<chips<T>>(rhs);
}

template <typename T>
chips<T> &chips<T>::operator=(const chips_any &rhs)
{
    *this = static_cast<chips<T>>(rhs);
    return *this;
}

/*=====================================================================
 *  imin,imax,fmin and fmax : min and max functions for chips numerics
 *=====================================================================*/

inline chips_int imin(const chips_int &lhs, const chips_int &rhs)
{
    if (lhs.shape() != rhs.shape())
        throw std::invalid_argument("imin : shape mismatch");
    chips_int res(lhs.shape());
    res.stopFlag = lhs.stopFlag || rhs.stopFlag;
    if (!res.stopFlag)
    {
        std::transform(lhs.data().begin(), lhs.data().end(),
                       rhs.data().begin(),
                       res.data().begin(),
                       [](int a, int b) { return std::min(a, b); });
    }
    return res;
}

inline chips_int imax(const chips_int &lhs, const chips_int &rhs)
{
    if (lhs.shape() != rhs.shape())
        throw std::invalid_argument("imax : shape mismatch");
    chips_int res(lhs.shape());
    res.stopFlag = lhs.stopFlag || rhs.stopFlag;
    if (!res.stopFlag)
    {
        std::transform(lhs.data().begin(), lhs.data().end(),
                       rhs.data().begin(),
                       res.data().begin(),
                       [](int a, int b) { return std::max(a, b); });
    }
    return res;
}

inline chips_float fmin(const chips_float &lhs, const chips_float &rhs)
{
    if (lhs.shape() != rhs.shape())
        throw std::invalid_argument("fmin : shape mismatch");
    chips_float res(lhs.shape());
    res.stopFlag = lhs.stopFlag || rhs.stopFlag;
    if (!res.stopFlag)
    {
        std::transform(lhs.data().begin(), lhs.data().end(),
                       rhs.data().begin(),
                       res.data().begin(),
                       [](double a, double b) { return std::min(a, b); });
    }
    return res;
}

inline chips_float fmax(const chips_float &lhs, const chips_float &rhs)
{
    if (lhs.shape() != rhs.shape())
        throw std::invalid_argument("fmax : shape mismatch");
    chips_float res(lhs.shape());
    res.stopFlag = lhs.stopFlag || rhs.stopFlag;
    if (!res.stopFlag)
    {
        std::transform(lhs.data().begin(), lhs.data().end(),
                       rhs.data().begin(),
                       res.data().begin(),
                       [](double a, double b) { return std::max(a, b); });
    }
    return res;
}


/*=====================================================================
 *  ones : fill with 1
 *=====================================================================*/
inline chips<int> ones(const chips<int> &first) // base‑case for one dimension
{
    // Verify that the argument really is a scalar chip (shape == {1})
    if (first.shape().size() != 1 || first.shape()[0] != 1)
        throw std::invalid_argument("ones(): each dimension argument must be a chips<int> of shape (1)");

    // Extract the single integer value that defines the size of this dimension
    int dim = first.data()[0]; // same as first({0}) but avoids extra vector creation

    // Build the shape vector (just one element)
    std::vector<int> shape{dim};

    if (first.stopFlag)
    {
        chips<int> res(std::move(shape));
        res.stopFlag = true;
        return res;
    }

    // Number of elements = product(shape) = dim
    std::vector<int> data(static_cast<std::size_t>(dim), 1); // fill with 1s

    return chips<int>(std::move(shape), std::move(data));
}

template <typename... Rest>
chips<int> ones(const chips<int> &first, const Rest &...rest)
{
    std::vector<int> shape;
    bool anyStop = false;

    auto push_dim = [&](const chips<int> &c)
    {
        if (c.shape().size() != 1 || c.shape()[0] != 1)
            throw std::invalid_argument(
                "ones(): each dimension argument must be a chips<int> of shape (1)");
        shape.push_back(c.data()[0]); // scalar value stored in the chip
        anyStop = anyStop || c.stopFlag;
    };

    push_dim(first);
    (push_dim(rest), ...);

    if (anyStop)
    {
        chips<int> res(std::move(shape));
        res.stopFlag = true;
        return res;
    }

    std::size_t total = 1;
    for (int d : shape)
        total *= static_cast<std::size_t>(d);

    std::vector<int> data(total, 1);

    return chips<int>(std::move(shape), std::move(data));
}

/*=====================================================================
 *  range : 0 … (product‑of‑dims – 1)
 *=====================================================================*/
inline chips<int> range(const chips<int> &first) // 1‑dim overload
{
    if (first.shape().size() != 1 || first.shape()[0] != 1)
        throw std::invalid_argument(
            "range(): each dimension argument must be a chips<int> of shape (1)");

    int dim = first.data()[0];
    std::vector<int> shape{dim};

    if (first.stopFlag)
    {
        chips<int> res(std::move(shape));
        res.stopFlag = true;
        return res;
    }

    std::vector<int> data;
    data.reserve(static_cast<std::size_t>(dim));
    for (int i = 0; i < dim; ++i)
        data.push_back(i); // 0,1,…,dim‑1

    return chips<int>(std::move(shape), std::move(data));
}

template <typename... Rest>
chips<int> range(const chips<int> &first, const Rest &...rest) // variadic overload
{
    std::vector<int> shape;
    bool anyStop = false;
    auto push_dim = [&](const chips<int> &c)
    {
        if (c.shape().size() != 1 || c.shape()[0] != 1)
            throw std::invalid_argument(
                "range(): each dimension argument must be a chips<int> of shape (1)");
        shape.push_back(c.data()[0]);
        anyStop = anyStop || c.stopFlag;
    };
    push_dim(first);
    (push_dim(rest), ...);

    if (anyStop)
    {
        chips<int> res(std::move(shape));
        res.stopFlag = true;
        return res;
    }

    std::size_t total = 1;
    for (int d : shape)
        total *= static_cast<std::size_t>(d);

    std::vector<int> data;
    data.reserve(total);
    for (std::size_t i = 0; i < total; ++i)
        data.push_back(static_cast<int>(i));

    return chips<int>(std::move(shape), std::move(data));
}

/*=====================================================================
 *  zeros : fill with 0
 *=====================================================================*/
inline chips<int> zeros(const chips<int> &first) // 1‑dim overload
{
    if (first.shape().size() != 1 || first.shape()[0] != 1)
        throw std::invalid_argument(
            "zeros(): each dimension argument must be a chips<int> of shape (1)");

    int dim = first.data()[0];
    std::vector<int> shape{dim};

    if (first.stopFlag)
    {
        chips<int> res(std::move(shape));
        res.stopFlag = true;
        return res;
    }

    std::vector<int> data(static_cast<std::size_t>(dim), 0); // all zeros
    return chips<int>(std::move(shape), std::move(data));
}

template <typename... Rest>
chips<int> zeros(const chips<int> &first, const Rest &...rest) // variadic overload
{
    std::vector<int> shape;
    bool anyStop = false;
    auto push_dim = [&](const chips<int> &c)
    {
        if (c.shape().size() != 1 || c.shape()[0] != 1)
            throw std::invalid_argument(
                "zeros(): each dimension argument must be a chips<int> of shape (1)");
        shape.push_back(c.data()[0]);
        anyStop = anyStop || c.stopFlag;
    };
    push_dim(first);
    (push_dim(rest), ...);

    if (anyStop)
    {
        chips<int> res(std::move(shape));
        res.stopFlag = true;
        return res;
    }

    std::size_t total = 1;
    for (int d : shape)
        total *= static_cast<std::size_t>(d);

    std::vector<int> data(total, 0); // all zeros
    return chips<int>(std::move(shape), std::move(data));
}

/*=====================================================================
 *  randin01 : returns a chips<double> containing a single random number
 *  uniformly distributed in [0,1)
 *=====================================================================*/
inline chips_float randin01()
{
    // Thread‑local generator – each thread gets its own engine.
    thread_local static std::mt19937 engine{
        []
        {
            std::random_device rd;
            return rd();
        }()};

    // Uniform distribution on [0,1)
    // we need to use the next value after 1.0 to avoid rounding errors
    // (uniform_real_distribution is based on computation over integers and not doubles)
    static thread_local std::uniform_real_distribution<double> dist(0.0, std::nextafter(1.0, 2.0));

    double value = dist(engine);

    std::vector<int> shape{1};
    std::vector<double> data{value};

    return chips_float(std::move(shape), std::move(data));
}

/*=====================================================================
 *  is_fresh : returns a chips<bool> containing a single true if the
 *  variable has been updated since the last component clk cycle
 *=====================================================================*/
template <typename U>
chips<bool> is_fresh(chips<U> var)
{
    return var.is_fresh();
}


#endif // CHIPS_HPP

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//----------------Code section generated from chips sources---------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
