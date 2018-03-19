#include "../includes.h"

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
	bool* res = new bool[LENGTH_OF_BITS];
	for (int i = 0; i < LENGTH_OF_BITS; ++i)
		res[i] = this->get_bit(i);
	return res;
}

ostream& operator<<(ostream& os, const BigInt& p) {
	for (int i = LENGTH_OF_BITS - 1; i >= 0; --i)
		os << (int)p.get_bit(i);
	return os;
}
