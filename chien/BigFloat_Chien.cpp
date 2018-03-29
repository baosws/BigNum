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



// string BigFloat::to_dec_str() const
// {
// 	BigFloat A(*this);
// 	BigInt nguyen;
// 	string res = "";
// 	if (this->get_bit(127) == 1)
// 		return "-" + (-A).to_dec_str();
// 	int exp = A.get_exponent() - BIAS;//bias value;
// 	//
// 	if (exp < 0)
// 	{
// 		res += "0.";
// 		for (int i = 0; i < -exp; i++) res += '0';
// 	}
// 	else
// 	{
// 		nguyen = A.operator BigInt();//
// 		res += nguyen.to_dec_str() + ".";
// 	}
// 	BigFloat tmp;
// 	string SigStr;
// 	for (int i = 0; i < 7; i++)
// 	{
// 		SigStr = A.get_first_nbits_of_significand(16);
// 		tmp = from_another_significand(SigStr);
// 		tmp = tmp * BigFloat::POW_2_OF_16;
// 		nguyen = BigInt(tmp);
// 		res += nguyen.to_dec_str();
// 		A.shift_significand_left(16);
// 	}
// 	return res;
// }

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
		res += this->get_bit(111 - i) - 48;
	return res;
}
/*Convert a binary string to BigFloat store
-Input: Binary String
- Ouput: A BigFloat
	Exp: "000010101000" -> BigFloat: 0|2^14-1 - 5|0101000
*/
BigFloat from_another_significand(string binStr)
{
	BigFloat res = (0.0);
	int idx = binStr.find_first_of('1');
	if (idx < 112)
	{
		unsigned short exp = -(idx+1) + 16383;//exp = -(idx+1)+2^14-1;
		res.set_exponent(exp);
		for (int i = 0; i <= idx; i++)
			binStr.erase(binStr.begin()+0);
		for (int i = 0; i < binStr.length(); i++)
			res.set_bit(111 - i, binStr[i] - 48);
	}
	return res;
}
