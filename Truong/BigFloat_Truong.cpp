#include "../includes.h"

string BigFloat::to_hex_str() const {
	if (this->get_bit(127) == 1)
		return "-" + (-*this).to_hex_str();
	string bin_str = "";// this->to_bin_str();	//to_bin_str belongs to BigInt????
	string res = "";
	int dot = bin_str.find('.');
	while (dot % 4) {
		bin_str = '0' + bin_str;
		dot++;
	}
	while ((bin_str.length() - 1 - dot) % 4)
		bin_str = bin_str + '0';
	for (int i = 0; i < (int)bin_str.length(); i += 4)
		if (bin_str[i] != '.') {
			int temp= (int(bin_str[i]-48)<<3) +
						(int(bin_str[i+1]-48)<<2) +
						(int(bin_str[i+2]-48)<<1) +
						(int(bin_str[i+3]-48));
			res+= char(temp<10 ? temp + '0' : temp - 10 + 'A');
		}
		else {
			res += '.';
			i -= 3;
		}
	while (res.back() == '0' && res[res.length() - 2] != '.')
		res.erase(res.length() - 1, 1);
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
	if (bin_str == "0.0")
		return BigFloat::ZERO;
	if (bin_str == "INF")
		return BigFloat::INF;
	bool neg = false;
	if (bin_str[0] == '-') {
		neg = true;
		bin_str.erase(0, 1);
	}
	int dot = bin_str.find('.');
	if (dot == (int)string::npos) {
		bin_str += ".0";
		dot = bin_str.length() - 2;
	}
	int one = bin_str.find('1');
	if (one < dot)
		bin_str.erase(dot, 1);
	BigFloat res;
	int exp = (one < dot ? dot - one - 1 : dot - one) + (FULL_EXPONENT >> 1);
	if (exp < 1) {
		one = bin_str.length() - 113;
		exp = 0;
	}
	res.set_exponent(exp);
	int n = bin_str.length();
	for (int i = one + 1; i < n && i < one + 113; ++i)
	   res.set_bit(112 + one - i, bin_str[i] == '1');
	return res;
}
