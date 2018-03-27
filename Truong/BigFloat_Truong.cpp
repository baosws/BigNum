#include "../includes.h"

BigFloat::BigFloat(const string & other) {
	for (int i = 0; i < __LENGTH_OF_BITS; i++)
	{
		set_bit(i, other[i] - 48);
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

string getBinary(int num) {
	string res = "";
	while (num > 0) {
		res = char((num % 2) + 48) + res;
		num = num >> 1;
	}
	return res;
}

BigFloat::BigFloat(double other) {
	// 112|15|1
	bool neg = 0;
	if (other < 0) {
		neg = true;
		other = -other;
	}
	long long integerPart = other;
	double fractionPart = other - integerPart;

	string doubleBinary = getBinary(integerPart);

	int exponent = doubleBinary.length() - 1 + 16383; // 2^(n-1)-1 = 2^(15-1) -1 = 16383
	doubleBinary.erase(0, 1); // delete number 1 at first of number
	//get binary of significand
	while (fractionPart != 1 && doubleBinary.length() <= 112) { //112 numbers for Significand precision
		char bit = '0';
		if (fractionPart * 2 > 1) {
			bit = '1';
			fractionPart = fractionPart * 2 - 1;
		}
		else {
			fractionPart = fractionPart * 2;
		}
		doubleBinary += bit;
	}
	while (doubleBinary.length() < 112) { doubleBinary += '0'; }

	string str_exponent = getBinary(exponent);
	while (str_exponent.length() < 15) { str_exponent = '0' + str_exponent; }

	//write to datas
	data[0] = 0; data[1] = 0;
	if (neg) {
		set_bit(__LENGTH_OF_BITS -1 , 1);
	}
	for (int i = 0; i < str_exponent.length(); i++) {
		set_bit(__LENGTH_OF_BITS - i - 1 -1, str_exponent[i] - 48);
	}
	for (int i = 0; i < doubleBinary.length(); i++) {
		set_bit(__LENGTH_OF_BITS - i - 16 -1 , doubleBinary[i] - 48);
	}
}

unsigned short BigFloat::get_exponent()
{
	unsigned short exponent = 0;
	for (int i = 112; i < __LENGTH_OF_BITS - 1; ++i) {
		if (this->get_bit(i))
			exponent |= 1 << (i - 112);
	}
	return exponent;
}

void BigFloat::set_exponent(unsigned short exp)
{
	//exp has 16 bits but it only uses 15 bits for exponent
	for (int i = 0; i < 15; ++i) {
		bool bit = (exp >> i) & 1; //get bit of exp at index i
		this->set_bit(i + 112, bit);
	}
}

BigInt BigFloat::get_significand() const
{
	BigInt sig(0);
	for (int i = 0; i < 112; ++i) {
		sig.set_bit(i,this->get_bit(i));
	}
	return sig;
}

void BigFloat::set_significand(const BigInt & biNum) {
	for (int i = 0; i < 112; ++i) {
		this->set_bit(i, biNum.get_bit(i));
	}
}
