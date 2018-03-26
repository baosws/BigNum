#pragma once
#include "includes.h"

class BigFloat: public BigNum {
public:
	BigFloat(const string&);
    BigFloat(const bool* const);
    BigFloat(const BigFloat&);
    BigFloat(double);
    
	//----------------
    BigFloat operator+(const BigFloat&) const;
    BigFloat operator-(const BigFloat&) const;
    BigFloat operator*(const BigFloat&) const;
    BigFloat operator/(const BigFloat&) const;

	unsigned short get_exponent();
	void set_exponent(unsigned short exp);

	BigInt get_significand() const;
	void set_significand(const BigInt& biNum);
	
	void shift_significand_right(int);
	void shift_significand_left(int);

	bool is_exponent_overflow();
	bool is_exponent_underflow();
	
	bool is_significand_overflow();

	bool is_normalized();


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
};
