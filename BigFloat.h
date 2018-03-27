#pragma once
#include "includes.h"

class BigFloat : public BigNum {
public:
	BigFloat(const bool* const);
	BigFloat(const BigFloat&);
	BigFloat(double);
	BigFloat(float);
	BigFloat() :BigNum(){}

	static BigFloat from_dec_str(const string&);
	static BigFloat from_bin_str(const string&);
	static BigFloat from_hex_str(const string&);
	static const BigFloat INF;
	static const BigFloat ZERO;
	//----------------
    BigFloat operator+(const BigFloat&) const;
    BigFloat operator-(const BigFloat&) const;
	BigFloat operator-() const;
    BigFloat operator*(const BigFloat&) const;
    BigFloat operator/(const BigFloat&) const;

	unsigned short get_exponent() const;
	void set_exponent(unsigned short exp);

	BigInt get_significand() const;
	void set_significand(const BigInt& biNum);
	
	void shift_significand_right();
	void shift_significand_left();

	bool is_exponent_overflow() const;
	bool is_exponent_underflow() const;
	
	bool is_significand_overflow() const;

	bool is_zero() const;
	bool is_normalized() const;
	bool is_denormalized() const;
	bool is_inf() const;
	bool is_nan() const;

	BigInt get_signed_significand() const;

	//-----------------
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
private :
	void add_signed_significands(const BigFloat&X, const BigFloat&Y);
};
