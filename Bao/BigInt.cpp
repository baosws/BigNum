#include "../includes.h"

BigInt BigInt::operator!() const {
	return BigInt(!(data[0] || data[1]));
}

BigInt BigInt::operator~() const {
	return BigInt({~data[0], ~data[1]});
}

BigInt BigInt::operator&(const BigInt& other) const {
	return BigInt({this->data[0] & other.data[0], this->data[1] & other.data[1]});
}

BigInt BigInt::operator|(const BigInt& other) const {
	return BigInt({this->data[0] | other.data[0], this->data[1] | other.data[1]});
}

BigInt BigInt::operator^(const BigInt& other) const {
	return BigInt({this->data[0] ^ other.data[0], this->data[1] ^ other.data[1]});
}
