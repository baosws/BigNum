#include "../includes.h"
//Toán tử so sánh bé hơn hoặc bằng
bool BigInt::operator<=(const BigInt& other) const {
	return !(*this > other);
}
//Toán tử so sánh lớn hơn hoặc bằng
bool BigInt::operator>=(const BigInt& other) const {
	return !(*this < other);
}

//Phép cộng
//reference at: https://www.geeksforgeeks.org/add-two-bit-strings/
BigInt BigInt::operator+(const BigInt & num) const {
	/*
	 * The situation the number of bit is out of LENGTHS_OF_BITS not handle
	 */
	BigInt result;
	bool carry = 0;
	for (int i = 0; i < LENGTH_OF_BITS; ++i) {
		result.set_bit(i, (this->get_bit(i) ^ num.get_bit(i)) ^ carry);
		carry = (this->get_bit(i) & num.get_bit(i)) | (this->get_bit(i) & carry) | (carry & num.get_bit(i));
	}
	return result;
}

//Phép trừ
//reference at : https://www.geeksforgeeks.org/subtract-two-numbers-without-using-arithmetic-operators/
BigInt BigInt::operator-(const BigInt & num) const {
	BigInt result;
	bool borrow = 0;
	for (int i = 0; i < LENGTH_OF_BITS; ++i) {
		int c = this->get_bit(i) - num.get_bit(i) - borrow;
		result.set_bit(i, c & 1);
		borrow = c < 0;
	}
	return result;
}
