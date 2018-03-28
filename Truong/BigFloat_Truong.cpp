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
	int exponent = ((t >> 52) & ((1 << 11) - 1)) // get other's exponent
					- ((1 << 10) - 1)         // get signed value
					+ (1 << 14) - 1;        // to 15-bias
	this->set_exponent(exponent);
	this->set_significand(BigInt(t & ((1ll << 52) - 1)) << (112 - 52));
}

unsigned short BigFloat::get_exponent() const
{
	if (this->is_zero())
		return 0;
	unsigned short exponent = 0;
	for (int i = 112; i < LENGTH_OF_BITS - 1; ++i) {
		if (this->get_bit(i))
			exponent |= 1 << (i - 112);
	}
	return exponent + (exponent == FULL_EXPONENT >> 1); // 0 -> 1 (-127 -> -126)
}

void BigFloat::set_exponent(unsigned short exp)
{
	//exp has 16 bits but it only uses 15 bits for exponent
	for (int i = 0; i < 15; ++i) {
		bool bit = (exp >> i) & 1; //get bit of exp at index i
		this->set_bit(i + 112, bit);
	}
}

BigInt BigFloat::get_significand() const {
	BigInt sig;
	for (int i = 0; i < 112; ++i) {
		sig.set_bit(i, this->get_bit(i));
	}
	return sig;
}

void BigFloat::set_significand(const BigInt & sig) {
	for (int i = 0; i < 112; ++i) {
		this->set_bit(i, sig.get_bit(i));
	}
}
