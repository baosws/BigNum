<<<<<<< HEAD
#pragma once
#include "includes.h"

class BigInt: public BigNum {
public:
    BigInt(const string&);
    BigInt(const bool* const);
    BigInt(const BigInt&);
    BigInt(long long);
    
    BigInt operator+(const BigInt&) const;
    BigInt operator-(const BigInt&) const;
    BigInt operator*(const BigInt&) const;
    BigInt operator/(const BigInt&) const;

    BigInt& operator+=(const BigInt&);
    BigInt& operator-=(const BigInt&);
    BigInt& operator*=(const BigInt&);
    BigInt& operator/=(const BigInt&);

    BigInt operator~() const;
    BigInt operator!() const;
    BigInt operator&(const BigInt&) const;
    BigInt operator|(const BigInt&) const;
    BigInt operator^(const BigInt&) const;
    BigInt operator<<() const;
    BigInt operator>>() const;
    
    BigInt& operator=(const BigInt&);
    BigInt& operator&=(const BigInt&);
    BigInt& operator|=(const BigInt&);
    BigInt& operator^=(const BigInt&);
    BigInt& operator<<=(int);
    BigInt& operator>>=(int);

    bool operator==(const BigInt&) const;
    bool operator!=(const BigInt&) const;
    bool operator<(const BigInt&) const;
    bool operator>(const BigInt&) const;
    bool operator<=(const BigInt&) const;
    bool operator>=(const BigInt&) const;

    operator bool() const;
};
=======
#pragma once
#include "includes.h"

class BigInt: public BigNum {
public:
//     BigInt(const string&);
    BigInt(const bool* const);
    BigInt(const BigInt&);
    BigInt(long long);
    
    BigInt operator+(const BigInt&) const;
    BigInt operator-(const BigInt&) const;
    BigInt operator*(const BigInt&) const;
    BigInt operator/(const BigInt&) const;

//     BigInt& operator+=(const BigInt&);
//     BigInt& operator-=(const BigInt&);
//     BigInt& operator*=(const BigInt&);
//     BigInt& operator/=(const BigInt&);

//     BigInt operator~() const;
//     BigInt operator!() const;
//     BigInt operator&(const BigInt&) const;
//     BigInt operator|(const BigInt&) const;
//     BigInt operator^(const BigInt&) const;
//     BigInt operator<<() const;
//     BigInt operator>>() const;
    
//     BigInt& operator=(const BigInt&);
//     BigInt& operator&=(const BigInt&);
//     BigInt& operator|=(const BigInt&);
//     BigInt& operator^=(const BigInt&);
//     BigInt& operator<<=(int);
//     BigInt& operator>>=(int);

    bool operator==(const BigInt&) const;
    bool operator!=(const BigInt&) const;
    bool operator<(const BigInt&) const;
    bool operator>(const BigInt&) const;
    bool operator<=(const BigInt&) const;
    bool operator>=(const BigInt&) const;

//     operator bool() const;
    operator bool*() const;
};
>>>>>>> 206c45c3ae14bca212a588274b75fbc4bfbfb381
