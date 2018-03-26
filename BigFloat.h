#pragma once
#include "includes.h"

class BigFloat : public BigNum {
public:
	BigFloat(const string&){};
	BigFloat(const bool* const){};
	BigFloat(const BigFloat&){};
	BigFloat(double){};
	BigFloat() :BigNum(){}
	//----------------
    BigFloat operator+(const BigFloat&) const;
    BigFloat operator-(const BigFloat&) const;
    BigFloat operator*(const BigFloat&) const;
    BigFloat operator/(const BigFloat&) const;

	unsigned short get_exponent();
	void set_exponent(unsigned short exp);

	BigInt get_significand() const;
	void set_significand(const BigInt& biNum);
	
	void shift_significand_right();
	void shift_significand_left();

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
    
	bool operator==(const BigFloat&) const{ return true; };//temporary solution
    bool operator!=(const BigFloat&) const;
    bool operator<(const BigFloat&) const;
    bool operator>(const BigFloat&) const;
    bool operator<=(const BigFloat&) const;
    bool operator>=(const BigFloat&) const;

    operator bool() const;
private :
	void add_signed_significands(const BigFloat&X, const BigFloat&Y);
};
