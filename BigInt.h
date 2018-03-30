#pragma once
#include "includes.h"

class BigInt: public BigNum {
public:
	// các hàm khởi tạo
	BigInt() {};
    BigInt(const bool* const); // chien/BigInt_Chien.cpp
    BigInt(const BigInt&); // chien/BigInt_Chien.cpp
    BigInt(long long); // chien/BigInt_Chien.cpp
	BigInt(int); // chien/BigInt_Chien.cpp

	// chuyển từ chuỗi sang số
	static BigInt from_dec_str(string); // Bao/BigInt_Bao.cpp
	static BigInt from_hex_str(string); // Bao/BigInt_Bao.cpp
	static BigInt from_bin_str(string); // Bao/BigInt_Bao.cpp

	// chuyển từ số sang chuỗi
	string to_bin_str() const; // Bao/BigInt_Bao.cpp
	string to_dec_str() const; // Bao/BigInt_Bao.cpp
	string to_hex_str() const; // Bao/BigInt_Bao.cpp

	// nhân, chia đủ
	pair<BigInt, BigInt> full_multiply(const BigInt&) const; // chien/BigInt_Chien.cpp
	pair<BigInt, BigInt> full_divide(const BigInt&) const; // chien/BigInt_Chien.cpp
    
	// phép toán số học
    BigInt operator+(const BigInt&) const; // Truong/BigInt_Truong.cpp
	BigInt operator-() const; // Bao/BigInt_Bao.cpp
    BigInt operator-(const BigInt&) const; // Truong/BigInt_Truong.cpp
    BigInt operator*(const BigInt&) const; // chien/BigInt_Chien.cpp
    BigInt operator/(const BigInt&) const; // chien/BigInt_Chien.cpp
	BigInt operator%(const BigInt&) const; // chien/BigInt_Chien.cpp

	// phép toán trên bit
	BigInt operator~() const; // Bao/BigInt_Bao.cpp
    BigInt operator!() const; // Bao/BigInt_Bao.cpp
    BigInt operator&(const BigInt&) const; // Bao/BigInt_Bao.cpp
    BigInt operator|(const BigInt&) const; // Bao/BigInt_Bao.cpp
    BigInt operator^(const BigInt&) const; // Bao/BigInt_Bao.cpp
    BigInt operator<<(int) const; // chien/BigInt_Chien.cpp
    BigInt operator>>(int) const; // chien/BigInt_Chien.cpp
    
    BigInt& operator=(const BigInt&); // Bao/BigInt_Bao.cpp

	// phép so sánh
    bool operator==(const BigInt&) const; // Bao/BigInt_Bao.cpp
    bool operator!=(const BigInt&) const; // Bao/BigInt_Bao.cpp
    bool operator<(const BigInt&) const; // chien/BigInt_Chien.cpp
    bool operator>(const BigInt&) const; // chien/BigInt_Chien.cpp
    bool operator<=(const BigInt&) const; // Truong/BigInt_Truong.cpp
    bool operator>=(const BigInt&) const; // Truong/BigInt_Truong.cpp

	// phép đổi kiểu
    operator bool() const; // Bao/BigInt_Bao.cpp
    operator bool*() const; // Bao/BigInt_Bao.cpp
	operator long long () const; // Bao/BigInt_Bao.cpp
	
	// hàm nhập xuất
	friend ostream& operator<<(ostream&, const BigInt&); // Bao/BigInt_Bao.cpp
	friend istream& operator>>(istream&, BigInt&); // Bao/BigInt_Bao.cpp
};
