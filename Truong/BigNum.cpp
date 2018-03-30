#include "../includes.h"

// hàm khởi tạo mặc định: data = 0
BigNum::BigNum() {
	this->data[0] = this->data[1] = 0;
}

// khởi tạo bởi dãy bit được cho bởi mảng bool, bit i tương ứng với numbers[i]
BigNum::BigNum(const bool* numbers) {
	for (int i = 0; i < LENGTH_OF_BITS; ++i) {
		set_bit(i, numbers[i]);
	}
}

// hàm set bit
void BigNum::set_bit(int index, bool value) {
	// phần tử data cần thay đổi là index / 64, tức là index >> 6
	// bit cần thay đổi của data[index >> 6] là index % 64, tức là index & 63
	if (value == 1) {
		data[index >> 6] |= 1ll << (index & 63);
	}
	else {
		data[index >> 6] &= ~(1ll << (index & 63));
	}
}

// hàm lấy bit
bool BigNum::get_bit(int index) const {
	// phần tử data cần lấy là index / 64, tức là index >> 6
	// bit cần lấy của data[index >> 6] là index % 64, tức là index & 63
	return (data[index >> 6] >> (index & 63)) & 1;
}
