#include "../includes.h"

// kiểm tra số không chuẩn
bool BigFloat::is_denormalized() const {
	return this->get_exponent() == 1;
}

// kiểm tra số zero
bool BigFloat::is_zero() const { // should not call get_exponent here (inf recursion)
	return this->data[0] == 0
		&& (this->data[1] << 1) == 0; // exclude the sign bit
}

// kiểm tra số vô cực
bool BigFloat::is_inf() const {
	return this->get_exponent() == MAX_EXP
		&& this->get_significand() == (BigInt)0;
}

// kiểm tra số nan
bool BigFloat::is_nan() const {
	return this->get_exponent() == MAX_EXP
		&& this->get_significand() != (BigInt)0;
}

// kiểm tra số chuẩn
bool BigFloat::is_normalized() const {
	return !this->is_denormalized()
		&& !this->is_inf()
		&& !this->is_nan()
		&& !this->is_zero();
}

// lấy phần trị, kèm theo số 1 (1.xxx, nếu có), ở dạng số có dấu
BigInt BigFloat::get_signed_significand() const {
	BigInt sig = this->get_significand();
	if (this->is_normalized())
		sig.set_bit(112, 1);
	if (this->get_bit(127) == 1)
		sig = -sig;
	return sig;
}

// phép cộng
BigFloat BigFloat::operator+(const BigFloat& other) const {
	BigInt X = this->get_signed_significand();
	BigInt Y = other.get_signed_significand();
	int x = this->get_exponent();
	int y = other.get_exponent();
	if (x < y) {
		X = X >> (y - x);
		x = y;
	}
	if (X == (BigInt)0)
		return other;
	if (y < x) {
		Y = Y >> (x - y);
		y = x;
	}
	if (Y == (BigInt)0)
		return *this;
	BigFloat res;
	BigInt Z = X + Y;
	if (Z.get_bit(127) == 1) {
		Z = -Z;
		res.set_bit(127, 1);
	}
	while (x < MAX_EXP && Z >= ((BigInt)1) << 113) {
		++x;
		Z = Z >> 1;
	}
	if (x == MAX_EXP && Z >= ((BigInt)1) << 113)
		return BigFloat::INF;
	while (x > 1 && Z < ((BigInt)1) << 112) {
		--x;
		Z = Z << 1;
	}
	if (x == 1 && Z == (BigInt)0) { // zero
		x--;
		res.set_bit(127, 0);
	}
	res.set_exponent(x);
	res.set_significand(Z);
	return res;
}

// phép lấy số đối
BigFloat BigFloat::operator-() const {
	if (this->is_zero())
		return *this;
	BigFloat res(*this);
	res.set_bit(127, 1 ^ res.get_bit(127));
	return res;
}

// phép trừ
BigFloat BigFloat::operator-(const BigFloat& other) const
{
	return *this + (-other);
}

// chuyển thành chuỗi thập phân
string BigFloat::to_dec_str() const
{
	if (this->get_bit(127) == 1)
 		return "-" + (-*this).to_dec_str();
 	BigFloat A(*this), ten_17 = 1e17;
	BigInt B = A.operator BigInt();
 	string res = B.to_dec_str() + ".";
	A = A - BigFloat(B);
	do {
		BigFloat tmp = A * ten_17;
		string t = tmp.operator BigInt().to_dec_str();
		while (t.length() < 17)
			t = "0" + t;
		res += t;
		A = tmp - BigFloat(tmp.operator BigInt());
	} while (A > BigFloat::ZERO);
	while (res.back() == '0' && res[res.length() - 2] != '.')
		res.pop_back();
	return res;
}
//Toán tử xuất << ra stream 
ostream& operator<<(ostream& os, const BigFloat& p) // chien/BigFloat_Chien.cpp
{
	os << p.to_dec_str();
	return os;
}
//Toán tử nhập >> vào stream
istream& operator>>(istream& is, BigFloat& p) // chien/BigFloat_Chien.cpp
{
	string s;
	is >> s;
	p = BigFloat::from_dec_str(s);
	return is;
}