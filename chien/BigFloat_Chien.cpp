#include "../includes.h"

bool BigFloat::is_denormalized() const {
	return this->get_exponent() == 1;
}
bool BigFloat::is_zero() const { // should not call get_exponent here (inf recursion)
	return this->data[0] == 0
		&& (this->data[1] << 1) == 0; // exclude the sign bit
}
bool BigFloat::is_inf() const {
	return this->get_exponent() == MAX_EXP
		&& this->get_significand() == (BigInt)0;
}
bool BigFloat::is_nan() const {
	return this->get_exponent() == MAX_EXP
		&& this->get_significand() != (BigInt)0;
}
bool BigFloat::is_normalized() const {
	return !this->is_denormalized()
		&& !this->is_inf()
		&& !this->is_nan()
		&& !this->is_zero();
}

BigInt BigFloat::get_signed_significand() const {
	BigInt sig = this->get_significand();
	if (this->is_normalized())
		sig.set_bit(112, 1);
	if (this->get_bit(127) == 1)
		sig = -sig;
	return sig;
}

// too many cases, needs to be optimized
BigFloat BigFloat::operator+(const BigFloat& other) const {
	BigInt X = this->get_signed_significand();
	BigInt Y = other.get_signed_significand();
	int x = this->get_exponent();
	int y = other.get_exponent();
	while (x < y) {
		++x;
		X = X >> 1;
		if (X == (BigInt)0)
			return other;
	}
	while (y < x) {
		++y;
		Y = Y >> 1;
		if (Y == (BigInt)0)
			return *this;
	}
	if (this->to_bin_str() == "1.101e11") {
		cout << "opt +\n";
		cout << "X: " << X.to_bin_str() << endl;
		cout << "Y: " << Y.to_bin_str() << endl;
	}
	BigFloat res;
	BigInt Z = X + Y;
	if (Z.get_bit(127) == 1) {
		Z = -Z;
		res.set_bit(127, 1);
	}
	auto get_high_bytes = [] (BigInt& Z) {return (long long)(Z >> 112) & ((1 << 16) - 1);};
	while (x < MAX_EXP && get_high_bytes(Z) > 1) {
		++x;
		Z = Z >> 1;
	}
	if (x == MAX_EXP && get_high_bytes(Z) > 1)
		return BigFloat::INF;
	while (x > 1 && get_high_bytes(Z) == 0) {
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

BigFloat BigFloat::operator-() const {
	if (this->is_zero())
		return *this;
	BigFloat res(*this);
	res.set_bit(127, 1 ^ res.get_bit(127));
	return res;
}
BigFloat BigFloat::operator-(const BigFloat& other) const
{
	return *this + (-other);
}
