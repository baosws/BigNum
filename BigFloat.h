#pragma once
#include "includes.h"

class BigFloat : public BigNum {
public:
	// hàm khởi tạo
	BigFloat(const bool* const bits);		// Truong/BigFloat_Truong.cpp
	BigFloat(const BigFloat&);				// Truong/BigFloat_Truong.cpp
	BigFloat(double);						// Truong/BigFloat_Truong.cpp
	BigFloat(BigInt);						// Bao/BigFloat_Bao.cpp
	BigFloat() :BigNum(){}

	// chuyển từ chuỗi sang số
	static BigFloat from_dec_str(string);			 // Bao/BigFloat_Bao.cpp
	static BigFloat from_bin_str(string);			// Truong/BigFloat_Truong.cpp
	static BigFloat from_hex_str(string);			// Bao/BigFloat_Bao.cpp

	// chuyển từ số sang chuỗi
	string to_dec_str() const;		// chien/BigFloat_Chien.cpp
	string to_bin_str() const;		// Bao/BigFloat_Bao.cpp
	string to_hex_str() const;		// Truong/BigFloat_Truong.cpp
	
	// các số đặc biệt
	static const BigFloat INF; // Bao/BigFloat_Bao.cpp
	static const BigFloat ZERO; // Bao/BigFloat_Bao.cpp
	static const BigFloat NaN; // Bao/BigFloat_Bao.cpp
	
	// các phép toán số học
    BigFloat operator+(const BigFloat&) const;	// chien/BigFloat_Chien.cpp
    BigFloat operator-(const BigFloat&) const;	// chien/BigFloat_Chien.cpp
	BigFloat operator-() const;					// chien/BigFloat_Chien.cpp
    BigFloat operator*(const BigFloat&) const; // Bao/BigFloat_Bao.cpp
    BigFloat operator/(const BigFloat&) const; // Bao/BigFloat_Bao.cpp

	// lấy phần mũ
	unsigned short get_exponent() const;		// Truong/BigFloat_Truong.cpp
	// thay đổi phần mũ
	void set_exponent(unsigned short exp);		// Truong/BigFloat_Truong.cpp

	// lấy phần trị
	BigInt get_significand() const;				// Truong/BigFloat_Truong.cpp		
	// thay đổi phần trị
	void set_significand(const BigInt& biNum);	// Truong/BigFloat_Truong.cpp

	// hàm kiểm tra loại số
	bool is_zero() const;						// chien/BigFloat_Chien.cpp
	bool is_normalized() const;					// chien/BigFloat_Chien.cpp
	bool is_denormalized() const;				// chien/BigFloat_Chien.cpp
	bool is_inf() const;						// chien/BigFloat_Chien.cpp
	bool is_nan() const;						// chien/BigFloat_Chien.cpp

	// lấy phần trị, kèm theo số 1 (1.xxx, nếu có), ở dạng số có dấu
	BigInt get_signed_significand() const;		// chien/BigFloat_Chien.cpp

	// phép gán
    BigFloat& operator=(const BigFloat&); // Bao/BigFloat_Bao.cpp
    
	// phép so sánh
	bool operator==(const BigFloat&) const; // Bao/BigFloat_Bao.cpp
    bool operator!=(const BigFloat&) const; // Bao/BigFloat_Bao.cpp
    bool operator<(const BigFloat&) const; // Bao/BigFloat_Bao.cpp
    bool operator>(const BigFloat&) const; // Bao/BigFloat_Bao.cpp
    bool operator<=(const BigFloat&) const; // Bao/BigFloat_Bao.cpp
    bool operator>=(const BigFloat&) const; // Bao/BigFloat_Bao.cpp

	// trả về mảng bool tương ứng với các bit
	operator bool*() const;
	// phép lấy phần nguyên ở dạng số BigInt
	operator BigInt() const; // Bao/BigFloat_Bao.cpp

	//Toán tử xuất << ra stream 
	friend ostream& operator<<(ostream&, const BigFloat&); // chien/BigFloat_Chien.cpp
	//Toán tử nhập >> vào stream
	friend istream& operator>>(istream&, BigFloat&); // chien/BigFloat_Chien.cpp
};
