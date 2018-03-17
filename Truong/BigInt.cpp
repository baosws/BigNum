#include "../includes.h"
BigInt::BigInt() : BigNum() {}

bool BigInt::operator<=(const BigInt& other) const{
	return !(*this > other);
}
bool BigInt::operator>=(const BigInt& other) const{
	return !(*this < other);
}

//reference at: https://www.geeksforgeeks.org/add-two-bit-strings/
BigInt BigInt::operator+(const BigInt & num) const {
	/*
	 * The situation the number of bit is out of LENGTHS_OF_BITS not handle
	 */
	BigInt result;
	bool carry = 0;
	for (int i = 0; i < LENGTH_OF_BITS; ++i) {
		result.set_bit(i, (this->get_bit(i) ^ num.get_bit(i)) ^ carry);
		carry = (this->get_bit(i) & num.get_bit(i) | (this->get_bit(i) & carry)) | (carry & num.get_bit(i));
	}
	return result;
}

//reference at : https://www.geeksforgeeks.org/subtract-two-numbers-without-using-arithmetic-operators/
BigInt BigInt::operator-(const BigInt & num) const {
	BigInt result;
	bool borrow = 0;
	for (int i = 0; i < LENGTH_OF_BITS; ++i) {
		result.set_bit(i, (this->get_bit(i) ^ num.get_bit(i)) ^ borrow);
		borrow = (~this->get_bit(i)) & num.get_bit(i);
	}
	return result;
}
