#pragma once
#include "includes.h"

class BigInt: public BigNum {
public:
	BigInt();
    BigInt(const bool* const);
    BigInt(const BigInt&);
    BigInt(long long);
	BigInt(int);

	static BigInt from_dec_str(string);
	static BigInt from_hex_str(string);
	static BigInt from_bin_str(string);
	string to_bin_str() const;
	string to_dec_str() const;
	string to_hex_str() const;

	pair<BigInt, BigInt> full_multiply(const BigInt&) const;
	pair<BigInt, BigInt> full_divide(const BigInt&) const;
    
    BigInt operator+(const BigInt&) const;
	BigInt operator-() const;
    BigInt operator-(const BigInt&) const;
    BigInt operator*(const BigInt&) const;
    BigInt operator/(const BigInt&) const;
	BigInt operator%(const BigInt&) const;

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

	bool operator==(int other) const;

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
