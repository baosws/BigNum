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
