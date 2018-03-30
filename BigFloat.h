#pragma once
#include "includes.h"

class BigFloat : public BigNum {
public:
	BigFloat(const bool* const);
	BigFloat(const BigFloat&);
	BigFloat(double);
	BigFloat(float);
	BigFloat() :BigNum(){}

	static BigFloat from_dec_str(string);
	static BigFloat from_bin_str(string);
	static BigFloat from_hex_str(string);

	string to_dec_str() const;
	string to_bin_str() const;
	string to_hex_str() const;
	
	static const BigFloat INF;
	static const BigFloat ZERO;
	static const BigFloat NaN;
	static const BigFloat POW_10_OF_16;
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
	void shift_significand_left(int);

	bool is_exponent_overflow() const;
	bool is_exponent_underflow() const;
	
	bool is_significand_overflow() const;

	bool is_zero() const;
	bool is_normalized() const;
	bool is_denormalized() const;
	bool is_inf() const;
	bool is_nan() const;

	BigInt get_signed_significand() const;
	friend BigFloat from_another_significand(string);
	string get_first_nbits_of_significand(int n);
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
	operator BigInt() const;
private :
	void add_signed_significands(const BigFloat&X, const BigFloat&Y);

	operator double() const;
};
