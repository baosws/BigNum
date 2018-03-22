#include "../includes.h"

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

ostream& operator<<(ostream& os, const BigInt& num) {
// 	for (int i = __LENGTH_OF_BITS - 1; i >= 0; --i)
// 		os << num.get_bit(i);
// 	return os;
	if (num.get_bit(127) == 1)
		return os << '-' << -num;
	const BigInt d(100000000000000ll);
	BigInt p(num);
	long long c = p % d;
	p = p / d;
	long long b = p % d;
	long long a = p / d;
	if (a)
		os << a << b << c;	
	else {
		if (b)
			os << b << c;
		else
			os << c;
	}
	return os;
}

istream& operator>>(istream& is, BigInt& p) {
	string s;
	is >> s;
	p = BigInt(s.c_str());
	return is;
}
