#pragma once
#include "includes.h"

class BigFloat: public BigNum {
public:
    BigFloat(const string&);
    BigFloat(const bool* const);
    BigFloat(const BigFloat&);
    BigFloat(double);
    
    BigFloat operator+(const BigFloat&) const;
    BigFloat operator-(const BigFloat&) const;
    BigFloat operator*(const BigFloat&) const;
    BigFloat operator/(const BigFloat&) const;

    BigFloat& operator+=(const BigFloat&);
    BigFloat& operator-=(const BigFloat&);
    BigFloat& operator*=(const BigFloat&);
    BigFloat& operator/=(const BigFloat&);

    BigFloat& operator=(const BigFloat&);
    
    bool operator==(const BigFloat&) const;
    bool operator!=(const BigFloat&) const;
    bool operator<(const BigFloat&) const;
    bool operator>(const BigFloat&) const;
    bool operator<=(const BigFloat&) const;
    bool operator>=(const BigFloat&) const;

    operator bool() const;
};
