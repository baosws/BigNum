#include "../includes.h"

BigInt BigInt::from_dec_str(string dec_str) {
	bool neg = false;
	if (dec_str[0] == '-') {
		neg = true;
		dec_str.erase(0, 1);
	}
	while (dec_str.length() < MAX_DEC_LENGTH)
		dec_str = '0' + dec_str;
	long long a[3] = {0};
	for (int i = 0; i < MAX_DEC_LENGTH; ++i) {
		a[i / 13] = a[i / 13] * 10 + dec_str[i] - '0';
	}
	BigInt res;
	const BigInt d(10000000000000ll);
	for (int i = 0; i < 3; ++i)
		res = res * d + BigInt(a[i]);
	if (neg)
		res = -res;
	return res;
}

string BigInt::to_dec() const {
	if (this->get_bit(127) == 1)
		return "-" + (-*this).to_dec();
	const BigInt d(10000000000000ll);
	BigInt p(*this);
	long long a[3];
	a[0] = p % d;
	p = p / d;
	a[1] = p % d;
	a[2] = p / d;
	string res;
	for (int i = 0; i < MAX_DEC_LENGTH; ++i) {
		res = char(a[i / 13] % 10 + '0') + res;
		a[i / 13] /= 10;
	}
	while (res.length() > 1 && res[0] == '0')
		res.erase(0, 1);
	return res;
}

BigInt BigInt::from_bin_str(string binStr)
{
	BigInt res;
	res.data[0] = 0;
	res.data[1] = 0;
	bool neg = binStr[0] == '-';
	if (neg)
		binStr.erase(0, 1);
	int n = binStr.length();
	for (int i = 0; i < n; ++i)
		res.set_bit(n - 1 - i, binStr[i] == '1');
	if (neg)
		res = -res;
	return res;
}

string BigInt::to_bin() const {
	string res = "";
	for (int i = 0; i < __LENGTH_OF_BITS; ++i)
		res = char(this->get_bit(i) + '0') + res;
	return res;
}

string BigInt::to_hex() const {
	string res = "";
	for (int i = 0; i < __LENGTH_OF_BITS; i += 4) {
		int c = (this->get_bit(i + 3) << 3)
			  + (this->get_bit(i + 2) << 2)
		  	  + (this->get_bit(i + 1) << 1)
			  + this->get_bit(i);	  
		res = char(c < 10 ? c + '0' : c - 10 + 'A') + res;
	}
	return res;
}

BigInt BigInt::from_hex_str(string hex_str) {
	bool neg = false;
	if (hex_str[0] == '-') {
		neg = true;
		hex_str.erase(0, 1);
	}
	while (hex_str.length() < MAX_HEX_LENGTH)
		hex_str = '0' + hex_str;
	BigInt res;
	int n = hex_str.length();
	for (int i = 0; i < n; ++i) {
		int c = (hex_str[n - i - 1] >= 'A' ? hex_str[n - i - 1] - 'A' + 10 : hex_str[n - i - 1] - '0');
		res.set_bit(i << 2, c & 1);
		res.set_bit((i << 2) | 1, (c >> 1) & 1);
		res.set_bit((i << 2) | 2, (c >> 2) & 1);
		res.set_bit((i << 2) | 3, (c >> 3) & 1);
	}
	if (neg)
		res = -res;
	return res;
}

BigInt BigInt::operator-() const {
	return BigInt(0) - *this;
}

BigInt BigInt::operator!() const {
	BigInt result;
	result.data[0] = !(this->data[0] || this->data[1]);
	result.data[1] = 0;
	return result;
}

BigInt BigInt::operator~() const {
	BigInt result;
	result.data[0] = ~this->data[0];
	result.data[1] = ~this->data[1];
	return result;
}

BigInt BigInt::operator&(const BigInt& other) const {
	BigInt result;
	result.data[0] = this->data[0] & other.data[0];
	result.data[1] = this->data[1] & other.data[1];
	return result;
}

BigInt BigInt::operator|(const BigInt& other) const {
	BigInt result;
	result.data[0] = this->data[0] | other.data[0];
	result.data[1] = this->data[1] | other.data[1];
	return result;
}

BigInt BigInt::operator^(const BigInt& other) const {
	BigInt result;
	result.data[0] = this->data[0] ^ other.data[0];
	result.data[1] = this->data[1] ^ other.data[1];
	return result;
}

BigInt& BigInt::operator=(const BigInt& other) {
	BigNum::operator=(other);
	return *this;
}

bool BigInt::operator==(const BigInt& other) const {
	return this->data[0] == other.data[0] && this->data[1] == other.data[1];
}

bool BigInt::operator!=(const BigInt& other) const {
	return !(*this == other);
}

BigInt::operator bool() const {
	return this->data[0] != 0 || this->data[1] != 0;
}

BigInt::operator bool*() const {
	bool* res = new bool[__LENGTH_OF_BITS];
	for (int i = 0; i < __LENGTH_OF_BITS; ++i)
		res[i] = this->get_bit(i);
	return res;
}

BigInt::operator long long() const {
	return this->data[0];
}

ostream& operator<<(ostream& os, const BigInt& p) {
	os << p.to_bin();
	return os;
}

istream& operator>>(istream& is, BigInt& p) {
	string s;
	is >> s;
	p = BigInt::from_dec_str(s);
	return is;
}
