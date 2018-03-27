#include "../includes.h"

BigFloat::BigFloat(const bool * const other) {
	for (int i = 0; i < LENGTH_OF_BITS; i++)
	{
		set_bit(i, other[i]);
	}
}

BigFloat::BigFloat(const BigFloat & other) {
	this->data[0] = other.data[0];
	this->data[1] = other.data[1];
}

BigFloat::BigFloat(double other) : BigNum() {
	long long t = *(long long*)&other;
	this->set_bit(127, (t >> 63) & 1);
	int exponent = (t >> 52) & (~(1 << 11)) // get other's exponent
					- 1023 				    // get unsigned value
					+ 16383;				// to 15-bias
	this->set_exponent(exponent);
	this->set_significand(BigInt(t & ((1ll << 52) - 1)) << (112 - 52));
}

unsigned short BigFloat::get_exponent() const
{
	unsigned short exponent = 0;
	for (int i = 112; i < LENGTH_OF_BITS - 1; ++i) {
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

<<<<<<< HEAD
BigInt BigFloat::get_significand() const
{
=======
BigInt BigFloat::get_significand() const {
>>>>>>> 34431fff2b74491510542f2e627a15e32ebcad9e
	BigInt sig(0);
	for (int i = 0; i < 112; ++i) {
		sig.set_bit(i, this->get_bit(i));
	}
	return sig;
}

void BigFloat::set_significand(const BigInt & sig) {
	for (int i = 0; i < 112; ++i) {
<<<<<<< HEAD
		this->set_bit(i, biNum.get_bit(i));
=======
		this->set_bit(i, sig.get_bit(i));
>>>>>>> 34431fff2b74491510542f2e627a15e32ebcad9e
	}
}
