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

BigFloat from_another_significand(string binStr)
{
	BigFloat res = BigFloat::ZERO;
	int idx = binStr.find_first_of('1');
	if (idx < 112 && idx !=-1)
	{
		unsigned short exp = -(idx+1) + 16383;//exp = -(idx+1)+2^14-1;
		res.set_exponent(exp);
		for (int i = 0; i <= idx; i++)
			binStr.erase(binStr.begin()+0);
		for (int i = 0; i < (int)binStr.length(); i++)
			res.set_bit(111 - i, binStr[i] - 48);
	}
	return res;
}
string BigFloat::to_dec_str() const
{
	if (this->get_bit(127) == 1)
 		return "-" + (-*this).to_dec_str();
 	BigFloat A(*this), ten = 10.0;
	BigInt B = A.operator BigInt();
 	string res = B.to_dec_str() + ".";
	A = A - BigFloat(B);
	do {
		BigFloat tmp = A * ten;
		BigInt d = tmp.operator BigInt();
		res += d.to_dec_str();
		A = tmp - BigFloat(tmp.operator BigInt());
	} while (A > BigFloat::ZERO);
	return res;
}

void BigFloat::shift_significand_left(int n)
{
	BigInt biNum = this->get_significand();
	biNum = biNum << n;
	this->set_significand(biNum);
}

/*Return the first n-bit string of BigFloat's significand area*/
string BigFloat::get_first_nbits_of_significand(int n)
{
	string res = "";
	for (int i = 0; i < n; i++)
		res += this->get_bit(111 - i) + 48;
	return res;
}
/*Convert a binary string to BigFloat store
-Input: Binary String
- Ouput: A BigFloat
	Exp: "000010101000" -> BigFloat: 0|2^14-1 - 5|0101000
*/

