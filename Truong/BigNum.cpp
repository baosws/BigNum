#include "../includes.h"

BigNum::BigNum() {
	this->data[0] = this->data[1] = 0;
}

BigNum::BigNum(const bool* numbers) {
	//init data=00000..00;
	//the position will be marked from left to right correlate 0 -> 128
	data[0] = 0; data[1] = 0;
	for (int i = 0; i < LENGTH_OF_BITS; ++i) {
		set_bit(i, numbers[i]);
	}
}

void BigNum::set_bit(int index, bool value) {
	//(LENGTH_OF_BITS >> 1) = 128/2 =64
	//print decimal to binary with 64data //test
	//std::string binary = dataet<64>(data[0]).to_string(); cout << binary << endl;

	/*
	(LENGTH_OF_BITS >> (index >> 6)
	(index >> 6) = index/64 = {1,2}
	(LENGTH_OF_BITS >> (index >> 6) = LENGTH_OF_BITS / {1,2} = 64
	(index <64)  = LENGTH_OF_BITS>> 0 = 64
	(index >=65)  = LENGTH_OF_BITS>> 1 = 64	
	*/
	if (value == 1) {
// 		data[index >> 6] |= (1ll << ((LENGTH_OF_BITS >> (index >> 6)) - 1 - index));
		data[index >> 6] |= 1ll << (index & 63);
	}
	else {
// 		data[index >> 6] &= ~(1ll << ((LENGTH_OF_BITS >> (index >> 6)) - 1 - index));
		data[index >> 6] &= ~(1ll << (index & 63));
	}
}

bool BigNum::get_bit(int index) const {
// 	return data[index >> 6] >> ((LENGTH_OF_BITS >> (index >> 6)) - 1 - index) & 1;
	return (data[index >> 6] >> (index & 63)) & 1;
}

BigNum& BigNum::operator=(const BigNum & big_num)
{
	// TODO: insert return statement here
	data[0] = big_num.data[0];
	data[1] = big_num.data[1];
	return *this;
}

