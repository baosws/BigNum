#pragma once
#include "includes.h"

class BigInt: public BigNum {
public:
	BigInt();
    BigInt(const char* binString);
    BigInt(const bool* const);
    BigInt(const BigInt&);
    BigInt(long long);
	BigInt(int);
    
    BigInt operator+(const BigInt&) const;
	BigInt operator-() const;
    BigInt operator-(const BigInt&) const;
    BigInt operator*(const BigInt&) const;
    BigInt operator/(const BigInt&) const;
	BigInt operator%(const BigInt&) const;

    BigInt& operator+=(const BigInt&);
    BigInt& operator-=(const BigInt&);
    BigInt& operator*=(const BigInt&);
    BigInt& operator/=(const BigInt&);

    BigInt operator~() const;
    BigInt operator!() const;
    BigInt operator&(const BigInt&) const;
    BigInt operator|(const BigInt&) const;
    BigInt operator^(const BigInt&) const;
    BigInt operator<<(int) const;
    BigInt operator>>(int) const;
    
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
    operator bool*() const;
	operator long long () const;
	
	friend ostream& operator<<(ostream&, const BigInt&);
	friend istream& operator>>(istream&, BigInt&);
};
