#include "../includes.h"


BigFloat::BigFloat(const string & other) {
	for (int i = 0; i < __LENGTH_OF_BITS; i++)
	{
		set_bit(i, other[i] - '48');
	}
}

BigFloat::BigFloat(const bool * const other) {
	for (int i = 0; i < __LENGTH_OF_BITS; i++)
	{
		set_bit(i, other[i]);
	}
}

BigFloat::BigFloat(const BigFloat & other) {
	this->data[0] = other.data[0];
	this->data[1] = other.data[1];
}

BigFloat::BigFloat(double other)
{
	// 1 || 15 ||112
	bool neg = 0;
	if (other < 0) {
		neg = true;
		other = -other;
	}
	long long integerPart = other;
	double fractionPart = other - integerPart;

	string doubleBinary = "";
	while (integerPart > 0) {
		doubleBinary = char((integerPart % 2) + 48) + doubleBinary;
		integerPart = integerPart >> 1;
	}

	int exponent = doubleBinary.length() - 1 + 16383; // 2^(n-1)-1 = 2^(15-1) -1 = 16383
	doubleBinary.erase(0, 1); // delete number 1 at first of number
	while (fractionPart != 1 || doubleBinary.length() <= 114) { //114 = 1 + 1 + 112 <=> number 1 + point(.) + 112 numbers for Significand precision
		char bit = (fractionPart * 2) > 1 ? '1' : '0';
		doubleBinary += bit;
		fractionPart = fractionPart * 2;
	}

	string str_exponent = "";
	while (exponent > 0) {
		str_exponent = char((exponent % 2) + 48) + str_exponent;
		exponent = exponent >> 1;
	}
	while (str_exponent.length() < 15) { str_exponent = '0' + str_exponent; }

	//write to datas
	data[0] = 0; data[1] = 0;
	if (neg) {
		set_bit(__LENGTH_OF_BITS, 1);
	}
	for (int i = 0; i < str_exponent.length(); i++) {
		set_bit(__LENGTH_OF_BITS - i - 1, str_exponent[i] - '48');
	}
	for (int i = 0; i < doubleBinary.length(); i++) {
		set_bit(__LENGTH_OF_BITS - i - 16, doubleBinary[i] - '48');
	}
}





