#include "../includes.h"
const BigFloat BigFloat::INF ;
const BigFloat BigFloat::ZERO;

bool BigFloat::is_denormalized() const {
	return this->get_exponent() == 1;
}
bool BigFloat::is_zero() const { // should not call get_exponent here (inf recursion)
	return this->data[0] == 0
		&& (this->data[1] << 1) == 0; // exclude the sign bit
}
bool BigFloat::is_inf() const {
	return this->get_exponent() == FULL_EXPONENT
		&& this->get_significand() == (BigInt)0;
}
bool BigFloat::is_nan() const {
	return this->get_exponent() == FULL_EXPONENT
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
		x++;
		X = X >> 1;
		if (X == (BigInt)0)
			return other;
	}
	while (y < x) {
		y++;
		Y = Y >> 1;
		if (Y == (BigInt)0)
			return *this;
	}
	BigFloat res;
	BigInt Z = X + Y;
	if (Z.get_bit(127) == 1) {
		Z = -Z;
		res.set_bit(127, 1);
	}
	auto get_high_bytes = [] (BigInt& Z) {return (long long)(Z >> 112) & ((1 << 16) - 1);};
	while (x < FULL_EXPONENT && get_high_bytes(Z) > 1) {
		++x;
		Z = Z >> 1;
	}
	if (x == FULL_EXPONENT && get_high_bytes(Z) > 1)
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



string BigFloat::to_dec_str() const
{
	BigFloat A(*this);
	string res = "";
	if (this->get_bit(127) == 1)
		return "-" + (-A).to_dec_str();
	int exp = A.get_exponent() - (int)pow(2, 14) + 1;//bias value;
	//
	if (exp < 0)
	{
		res += "0.";
		for (int i = 0; i < -exp; i++) res.push_back('0');
	}
	else
	{
		string mansita = "1";
		for (int i = 0; i < exp; i++)
			mansita += A.get_first_nbits_of_significand(exp);
		BigInt biTmp(mansita);
		res += biTmp.to_dec_str() + ".";
	}
	for (int i = 0; i < 7; i++)
	{
		string SigStr = A.get_first_nbits_of_significand(16);
		BigInt BiTmp(SigStr);
		res += BiTmp.to_dec_str();
		A.shift_significand_left(16);
	}
	return res;
}