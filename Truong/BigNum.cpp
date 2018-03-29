#include "../includes.h"

BigNum::BigNum() {
	this->data[0] = this->data[1] = 0;
}

BigNum::BigNum(const bool* numbers) {
	data[0] = 0; data[1] = 0;
	for (int i = 0; i < LENGTH_OF_BITS; ++i) {
		set_bit(i, numbers[i]);
	}
}

void BigNum::set_bit(int index, bool value) {
	if (value == 1) {
		data[index >> 6] |= 1ll << (index & 63);
	}
	else {
		data[index >> 6] &= ~(1ll << (index & 63));
	}
}

bool BigNum::get_bit(int index) const {
	return (data[index >> 6] >> (index & 63)) & 1;
}

BigNum& BigNum::operator=(const BigNum & big_num)
{
	data[0] = big_num.data[0];
	data[1] = big_num.data[1];
	return *this;
}

