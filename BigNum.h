#pragma once
#include "includes.h"


// cài đặt ở Truong/BigNum.cpp
class BigNum {
public:
	// 8 byte cao lưu ở data[1], 8 byte thấp lưu ở data[0]
	// lưu theo nguyên tắc Little Endian: bit 0 của BigNum là bit 0 của data[0],...
    long long data[2];
	//Constructor mặc định, tạo đối tượng có giá trị bằng 0
    BigNum();
	//Constructor khởi tạo từ một mảng bool chứa các giá trị nhị phân
    BigNum(const bool* const);
	
	//Hàm gán giá trị theo từng vị trí bit
    void set_bit(int, bool);
	//Lấy giá trị bit tại một vị trí
    bool get_bit(int) const;
};
