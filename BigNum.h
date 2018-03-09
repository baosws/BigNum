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
