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

ostream& BigInt::to_bits(ostream& os) {
	for (int i = __LENGTH_OF_BITS - 1; i >= 0; --i)
		os << this->get_bit(i);
	return os;
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

bool BigInt::operator==(long long other) const {
	return this->data[0] == 0 && this->data[1] == other;
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

ostream& operator<<(ostream& os, const BigInt& num) {
	if (num.get_bit(127) == 1)
		return os << '-' << -num;
	const BigInt d(10000000000000ll);
	BigInt p(num);
	long long a[3];
	a[0] = p % d;
	p = p / d;
	a[1] = p % d;
	a[2] = p / d;
	string s;
	for (int i = 0; i < MAX_DEC_LENGTH; ++i) {
		s = char(a[i / 13] % 10 + '0') + s;
		a[i / 13] /= 10;
	}
	while (s.length() > 1 && s[0] == '0')
		s.erase(0, 1);
	return os<< s;
}

istream& operator>>(istream& is, BigInt& p) {
	string s;
	//is >> s;
	p = BigInt(s.c_str());
	return is;
}
