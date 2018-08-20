#pragma once
#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <type_traits>
#include <functional>
#include <iostream>

namespace bpp {
    template <size_t Size>
    class bignum {
        protected:
            typedef uint64_t ctype;
            std::array<ctype, Size> data;
            
        protected:
            bignum& set(size_t pos, bool val) {
                if (val) {
                    data[pos >> 6] |= (1ull << (pos & 63));
                }
                else {
                    data[pos >> 6] &= ~(1ull << (pos & 63));
                }
                
                return *this;
            }

            bool get(size_t pos) const {
                return (data[pos >> 6] >> (pos & 63)) & 1ull;
            }
    };
}
