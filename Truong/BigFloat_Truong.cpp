#include "../includes.h"

string BigFloat::to_hex_str() const {
	if (this->get_bit(127) == 1)
		return "-" + (-*this).to_bin_str();
	if (this->is_zero())
		return "0.0";
	if (this->is_inf())
		return "INF";
	if (this->is_nan())
		return "NaN";
	if (this->get_bit(127) == 1)
		return "-" + (-*this).to_bin_str();
	if (this->is_zero())
		return "0.0";
	string res;
	BigInt X = this->get_signed_significand();
	int exp = this->get_exponent() - BIAS;
	res = X.to_hex_str();
// 	exp -= 29 - res.length();
	res.insert(1, ".");
	while (res.back() == '0' && res[res.length() - 2] != '.')
		res.erase(res.length() - 1, 1);
	res = res + "e" + BigInt(exp).to_hex_str();
	return res;
}

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
	if (other == 0.0) {
		*this = BigFloat::ZERO;
		return;
	}
	long long t = *(long long*)&other;
	this->set_bit(127, (t >> 63) & 1);
	int exponent = ((t >> 52) & ((1 << 11) - 1)) // get other's exponent
					- ((1 << 10) - 1)         // get signed value
					+ ((1 << 14) - 1);        // to 15-bias
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
	return exponent + (exponent == 0); // 0 -> 1 (-127 -> -126)
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

BigFloat BigFloat::from_bin_str(string bin_str) {
	std::transform(bin_str.begin(), bin_str.end(), bin_str.begin(), ::tolower);
	bool neg = false;
	if (bin_str[0] == '-') {
		neg = true;
		bin_str.erase(0, 1);
	}
	if (bin_str == "0.0")
		return BigFloat::ZERO;
	if (bin_str == "inf")
		return BigFloat::INF;
	if (bin_str == "nan")
		return BigFloat::NaN;
	
	int e = bin_str.find('e');
	string significand = bin_str.substr(0, e);
	significand.erase(1, 1);
	while (significand.length() < 113)
		significand += "0";
	int exp = (long long)BigInt::from_bin_str(bin_str.substr(e + 1, bin_str.length() - 1 - e));
	BigFloat res;
	res.set_exponent(exp + BIAS);
	res.set_significand(BigInt::from_bin_str(significand));
	if (neg)
		res = -res;
	return res;
}
