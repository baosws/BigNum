#include "../includes.h"

BigNum::BigNum() {
	this->data[0] = this->data[1] = 0;
}

BigNum::BigNum(const bool* numbers) {
	//init data=00000..00;
	//the position will be marked from left to right correlate 0 -> 127
	data[0] = 0; data[1] = 0;
	for (int i = 0; i < LENGTH_OF_BITS; ++i) {
		set_bit(i, numbers[i]);
	}
}


void BigNum::set_bit(int index, bool value) {
	//(LENGTH_OF_BITS >> 1) = 128/2 =64
	if (index < (LENGTH_OF_BITS >> 1)) {
		//print decimal to binary with 64data //test
		//std::string binary = dataet<64>(data[0]).to_string(); cout << binary << endl; 
		if (value == 1) {
			data[0] |= (1ll << ((LENGTH_OF_BITS >> 1) - 1 - index));
		}
		else {
			data[0] &= ~(1ll << ((LENGTH_OF_BITS >> 1) - 1 - index));
		}
	}
	else {
		if (value == 1) {
			data[1] |= (1ll << (LENGTH_OF_BITS - 1 - index));
		}
		else {
			data[1] &= ~(1ll << (LENGTH_OF_BITS - 1 - index));
		}
	}
}

bool BigNum::get_bit(int index) const {
	return (index < (LENGTH_OF_BITS >> 1)) ? (data[0] >> ((LENGTH_OF_BITS >> 1) - 1 - index)) & 1 : (data[1] >> (LENGTH_OF_BITS - 1 - index)) & 1;
}

BigNum& BigNum::operator=(const BigNum & big_num)
{
	// TODO: insert return statement here
	data[0] = big_num.data[0];
	data[1] = big_num.data[1];
	return *this;
}

