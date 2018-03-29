#include "../includes.h"

const BigFloat BigFloat::INF = BigFloat((bool*)(BigInt(MAX_EXP) << 112));
const BigFloat BigFloat::ZERO = BigFloat(0.0);
const BigFloat BigFloat::NaN = BigFloat((bool*)((BigInt(MAX_EXP) << 112) + (BigInt)1));

bool BigFloat::operator==(const BigFloat& p) const {
	return this->data[0] == p.data[0]
		&& this->data[1] == p.data[1];
}

bool BigFloat::operator!=(const BigFloat& p) const {
	return !(*this == p);
}

BigFloat& BigFloat::operator=(const BigFloat& other) {
	BigNum::operator=(other);
	return *this;
}

bool BigFloat::operator<(const BigFloat& other) const {
	BigInt X = this->get_signed_significand();
	BigInt Y = other.get_signed_significand();
	int x = this->get_exponent();
	int y = other.get_exponent();
	while (x < y) {
		++x;
		X = X >> 1;
	}
	while (y < x) {
		++y;
		Y = Y >> 1;
	}
	return X < Y;
}

bool BigFloat::operator>(const BigFloat& other) const {
	BigInt X = this->get_signed_significand();
	BigInt Y = other.get_signed_significand();
	int x = this->get_exponent();
	int y = other.get_exponent();
	while (x < y) {
		x++;
		X = X >> 1;
	}
	while (y < x) {
		y++;
		Y = Y >> 1;
	}
	return X > Y;
}

bool BigFloat::operator<=(const BigFloat& p) const {
	return !(*this > p);
}

bool BigFloat::operator>=(const BigFloat& p) const {
	return !(*this < p);
}

BigFloat BigFloat::operator*(const BigFloat& other) const {
	if (this->is_nan() || other.is_nan())
		return BigFloat::NaN;
	BigFloat res;
	res.set_bit(127, this->get_bit(127) ^ other.get_bit(127));
	BigInt X = this->get_signed_significand() << 8;
	if (X < (BigInt)0)
		X = -X;
	BigInt Y = other.get_signed_significand() << 8;
	if (Y < (BigInt)0)
		Y = -Y;
	int exp = this->get_exponent() + other.get_exponent() - BIAS;
	if (exp >= MAX_EXP)
		return BigFloat::INF;
	BigInt A, Q;
	tie(A, Q) = X.full_multiply(Y);
	auto get_high_bits = [] (BigInt& Z) {
		return (long long)(Z >> 112) & ((1 << 16) - 1);
	};
	while (exp > 1 && get_high_bits(A) == 0) {
		--exp;
		A = A << 1;
		A.set_bit(0, Q.get_bit(127));
		Q = Q << 1;
	}
	if (exp == 1 && A == (BigInt)0)
		return BigFloat::ZERO;
	res.set_exponent(exp);
	res.set_significand(A);
	return res;
}

BigFloat BigFloat::operator/(const BigFloat& divisor) const {
	if (this->is_nan() || divisor.is_nan())
		return BigFloat::NaN;
	if (*this == BigFloat::ZERO) {
		if (divisor.is_zero())
			return BigFloat::NaN;
		return BigFloat::ZERO;
	}
	if (divisor == BigFloat::ZERO) {
		if (*this < (BigFloat)0.0)
			return -INF;
		else
			return INF;
	}
	if (divisor < (BigFloat)0.0)
		return -(*this / (-divisor));
	if (*this < (BigFloat)0.0)
		return -((-*this) / divisor);
	BigInt X = this->get_signed_significand();
	BigInt Y = divisor.get_signed_significand();
	int x = this->get_exponent();
	int y = divisor.get_exponent();
	int z = x - y + MAX_EXP;
	BigFloat res;
	BigInt Z, R;
	for (int i = 112, cnt = -1; i >= 0 || cnt >= 0; --i) {
		R = (R << 1) + (BigInt)X.get_bit(i); 
		int c = 0;
		if (R >= Y) {
			c = 1;
			R = R - Y;
		}
		if (cnt == -1 && c == 1)
			cnt = 112;
		if (cnt != -1) {
			Z.set_bit(cnt, c);
			--cnt;
		}
		else
			--z;
	}
	auto get_high_bytes = [] (BigInt& Z) {return (long long)(Z >> 112) & ((1 << 16) - 1);};
	while (z < MAX_EXP && get_high_bytes(Z) > 1) {
		++z;
		Z = Z >> 1;
	}
	if (z > MAX_EXP
	|| (z == MAX_EXP && get_high_bytes(Z) > 1))
		return BigFloat::INF;
	while (z > 1 && get_high_bytes(Z) == 0) {
		--z;
		Z = Z << 1;
	}
	if (z < 1
	|| (z == 1 && Z == (BigInt)0)) { // zero
		z = 0;
		res.set_bit(127, 0);
	}
	res.set_exponent(z);
	res.set_significand(Z);
	return res;
}

string BigFloat::to_bin_str() const {
	if (this->get_bit(127) == 1)
		return "-" + (-*this).to_bin_str();
	if (this->is_inf())
		return "INF";
	if (this->is_nan())
		return "NaN";
	BigInt X = this->get_signed_significand();
	int exp = this->get_exponent() - (MAX_EXP >> 1);
// 	cout << "exp: " << exp << endl;
	string res = X.to_bin_str(); // + "e" + BigInt(x).to_bin_str();
	exp -= 113 - res.length();
	res.insert(1, ".");
	while (res.back() == '0' && res[res.length() - 2] != '.')
		res.erase(res.length() - 1, 1);
	res = res + "e" + BigInt(exp).to_bin_str();
	return res;
}
