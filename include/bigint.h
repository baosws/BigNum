#pragma once
#include "bignum.h"

#define impl(op) \
    bigint& operator op##=(const bigint& other) noexcept {\
        for (size_t i = 0; i < Size; ++i) {\
            this->data[i] op##= other.data[i];\
        }\
        return *this;\
    }\
    bigint operator op(const bigint& other) const noexcept {\
        bigint<Size> res(*this);\
        res op##= other;\
        return res;\
    }\
    bigint operator op(bigint&& other) const noexcept {\
        bigint<Size> res(std::move(other));\
        res op##= *this;\
        return res;\
    }

namespace bpp {
    template <size_t Size>
    class bigint: public bignum<Size> {
        typedef typename bignum<Size>::ctype ctype;
        public:
            using bignum<Size>::bignum;
            template <size_t _Size>
                friend class bigint;

            template <size_t _Size>
                bigint(const bigint<_Size>& other) noexcept {
                    std::cerr << "bigint copy ctor\n";
                    constexpr int nsize = std::min(Size, _Size);
                    std::copy(other.data.begin(), other.data.begin() + nsize, this->data.begin());
                }

            template <size_t _Size>
                bigint(bigint<_Size>&& other) noexcept {
                    std::cerr << "bigint move ctor\n";
                    constexpr int nsize = std::min(Size, _Size);
                    std::move(other.data.begin(), other.data.begin() + nsize, this->data.begin());
                }
            // logical operators
            impl(^);
            impl(|);
            impl(&);

            bigint operator!() const noexcept {
                bigint res;
                res.data[0] = 1;
                for (ctype& block : this->data) {
                    if (block != 0) {
                        res.data[0] = 0;
                        break;
                    }
                }
                return res;
            }
            
            bigint operator~() const noexcept {
                bigint res(*this);
                for (ctype& block : res.data) {
                    block = ~block;
                }
                return res;
            }

            bigint& operator<<=(size_t dist) noexcept {
                size_t st = dist >> 6, d = dist & 63;
                for (size_t i = 0; i < st && i < Size; ++i) {
                    this->data[i] = 0;
                }
                ctype last = 0;
                for (size_t i = st; i < Size; ++i) {
                    ctype tmp = this->data[i] >> (64 - d); 
                    this->data[i] = (this->data[i] << d) | last;
                    last = tmp;
                }
            }

            bigint operator<<(size_t dist) const noexcept {
                bigint res(*this);
                res <<= dist;
                return res;
            }

            bigint& operator>>=(size_t dist) noexcept {
                // to do
                return *this;
            }

            bigint operator>>(size_t dist) const noexcept {
                bigint res(*this);
                res >>= dist;
                return res;
            }

            // arithmetic operators
            bigint& operator+=(const bigint& other) noexcept {
                ctype c = 0;
                for (size_t i = 0; i < Size; ++i) {
                    ctype t = 0;
                    if (this->data[i] > std::numeric_limits<ctype>::max() - c) {
                        t = 1;
                    }
                    this->data[i] += c;
                    if (this->data[i] > std::numeric_limits<ctype>::max() - other.data[i]) {
                        t = 1;
                    }
                    this->data[i] += other.data[i];
                    c = t;
                }
                return *this;
            }

            bigint operator+(const bigint& other) const noexcept {
                bigint res(*this);
                res += other;
                return res;
            }

            bigint operator+(bigint&& other) const noexcept {
                bigint res(std::move(other));
                res += *this;
                return res;
            }

            bigint& operator-=(const bigint& other) noexcept {
                ctype c = 0;
                for (size_t i = 0; i < Size; ++i) {
                    ctype t = 0;
                    if (other.data[i] > std::numeric_limits<ctype>::max() - c) {
                        t = 1;
                    }
                    other.data[i] += c;
                    if (this->data[i] < other.data[i]) {
                        t = 1;
                    }
                    this->data[i] -= other.data[i];
                    c = t;
                }
                return *this;
            }

            bigint operator-() const noexcept {
                bigint res(~*this);
                for (size_t i = 0; i < Size; ++i) {
                    if (res.data[i] == std::numeric_limits<ctype>::max()) {
                        res.data[i] = 0;
                    }
                    else {
                        ++res.data[i];
                        break;
                    }
                }
                return res;
            }
            
            bigint operator-(const bigint& other) const noexcept {
                bigint res(*this);
                res -= other;
                return res;
            }

            bigint operator-(bigint&& other) const noexcept {
                bigint res(std::move(other));
                res -= *this;
                res = -res;
                return res;
            }
    };
}
