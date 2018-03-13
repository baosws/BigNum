<<<<<<< HEAD
#pragma once
#include "includes.h"

class BigNum {
protected:
    long long bits[2];
    BigNum(const bool* const);

    void set_bit(int, bool);
    bool get_bit(int);

    BigNum& operator=(const BigNum&);
};
=======
#pragma once
#include "includes.h"

class BigNum {
protected:
    long long data[2];
    BigNum();
    BigNum(const bool* const);

    void set_bit(int, bool);
    bool get_bit(int) const;

    BigNum& operator=(const BigNum&);
};
>>>>>>> 206c45c3ae14bca212a588274b75fbc4bfbfb381
