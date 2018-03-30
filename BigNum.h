#pragma once
#include "includes.h"


// cài đặt ở Truong/BigNum.cpp
class BigNum {
public:
	// 8 byte cao lưu ở data[1], 8 byte thấp lưu ở data[0]
	// lưu theo nguyên tắc Little Endian: bit 0 của BigNum là bit 0 của data[0],...
    long long data[2];

    BigNum();
    BigNum(const bool* const);
    virtual void set_bit(int, bool);
    virtual bool get_bit(int) const;
};
