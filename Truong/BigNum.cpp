#include "BigNum.h"
#include <bitset>



BigNum::BigNum(const bool* numbers) {
	//init bits=00000..00;
	//the position will be marked from left to right correlate 0 -> 128
	bits[0] = 0; bits[1] = 0;
	for (int i = 0; i < LENGTH_OF_BITS; ++i) {
		set_bit(i, numbers[i]);
	}
}


void BigNum::set_bit(int index, bool value) {
	//(LENGTH_OF_BITS >> 1) = 128/2 =64
	if (index < (LENGTH_OF_BITS >> 1)) {
		//print decimal to binary with 64bits //test
		//std::string binary = bitset<64>(bits[0]).to_string(); cout << binary << endl; 
		if (value == 1) {
			bits[0] |= (1ll << ((LENGTH_OF_BITS >> 1) - 1 - index));
		}
		else {
			bits[0] &= ~(1ll << ((LENGTH_OF_BITS >> 1) - 1 - index));
		}
	}
	else {
		if (value == 1) {
			bits[1] |= (1ll << (LENGTH_OF_BITS - 1 - index));
		}
		else {
			bits[1] &= ~(1ll << (LENGTH_OF_BITS - 1 - index));
		}
	}
}

bool BigNum::get_bit(int index) {
	return (index < (LENGTH_OF_BITS >> 1)) ? (bits[0] >> ((LENGTH_OF_BITS >> 1) - 1 - index)) & 1 : (bits[1] >> (LENGTH_OF_BITS - 1 - index)) & 1;
}

BigNum & BigNum::operator=(const BigNum & big_num)
{
	// TODO: insert return statement here
	bits[0] = big_num.bits[0];
	bits[1] = big_num.bits[1];
	return *this;
}

