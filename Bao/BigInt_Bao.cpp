#include "../includes.h"

BigInt::BigInt(): BigNum() {}

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
