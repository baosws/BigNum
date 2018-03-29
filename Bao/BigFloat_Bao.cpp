#include "../includes.h"

const BigFloat BigFloat::INF = BigFloat((bool*)(BigInt(MAX_EXP) << 112));
const BigFloat BigFloat::ZERO = BigFloat();
const BigFloat BigFloat::NaN = BigFloat((bool*)((BigInt(MAX_EXP) << 112) + (BigInt)1));
const BigFloat BigFloat::POW_2_OF_16 = BigFloat((double)pow(2, 16));

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
// 	cout << "this: " << this->to_bin_str() << endl;
// 	cout << "other: " << other.to_bin_str() << endl;
	BigFloat res;
	res.set_bit(127, this->get_bit(127) ^ other.get_bit(127));
	BigInt X = this->get_signed_significand();
	if (X < (BigInt)0)
		X = -X;
	BigInt Y = other.get_signed_significand();
	if (Y < (BigInt)0)
		Y = -Y;
	int exp = this->get_exponent() + other.get_exponent() - BIAS;
	if (exp >= MAX_EXP)
		return BigFloat::INF;
	BigInt A, Q;
	tie(A, Q) = X.full_multiply(Y);
// 	cout << "A < 1000...: " << (A < (BigInt(1) << 112)) << endl;
// 	cout << "A: " << A.to_bin_str() << " " << A.to_bin_str().length() << endl;
	exp += (128 - 112);
	while (exp > 1 && A < (BigInt(1) << 112)) {
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
	int exp = this->get_exponent() - divisor.get_exponent() + BIAS + 112;
	BigFloat res;
	BigInt significand, remainder;
	X = X << 1;
	for (int i = 113, cnt = -1; i >= 0 || cnt >= 0; --i) {
		if (i >= 0)
			remainder = (remainder << 1) + (BigInt)X.get_bit(i); 
		else
			remainder = remainder << 1;
		int c = 0;
		if (remainder >= Y) {
			c = 1;
			remainder = remainder - Y;
		}
		if (cnt == -1 && c == 1)
			cnt = 112;
		if (cnt != -1) {
			significand.set_bit(cnt, c);
			--cnt;
		}
		else
			--exp;
	}
	res.set_exponent(exp);
	res.set_significand(significand);
	return res;
}

string BigFloat::to_bin_str() const {
	if (this->get_bit(127) == 1)
		return "-" + (-*this).to_bin_str();
	if (this->is_zero())
		return "0.0";
	if (this->is_inf())
		return "INF";
	if (this->is_nan())
		return "NaN";
	BigInt X = this->get_signed_significand();
	int exp = this->get_exponent() - (MAX_EXP >> 1);
	string res = X.to_bin_str(); // + "e" + BigInt(x).to_bin_str();
	exp -= 113 - res.length();
	res.insert(1, ".");
	while (res.back() == '0' && res[res.length() - 2] != '.')
		res.erase(res.length() - 1, 1);
	res = res + "e" + BigInt(exp).to_bin_str();
	return res;
}

BigFloat BigFloat::from_hex_str(string hex_str) {
	bool neg = false;
	if (hex_str[0] == '-') {
		neg = true;
		hex_str.erase(0, 1);
	}
	if (hex_str == "0.0")
		return BigFloat::ZERO;
	if (hex_str == "inf")
		return BigFloat::INF;
	if (hex_str == "nan")
		return BigFloat::NaN;

	string bin_str = "";
	string hex_to_bin[] = {"0000", "0001", "0010", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1010", "1011", "1100", "1101", "1110", "1111"};
	for (int i = 0; i < (int)hex_str.length(); ++i)
		if (hex_str[i] == '.' || hex_str[i] == 'e')
			bin_str += hex_str[i];
		else
			bin_str += hex_to_bin[hex_str[i] >= 'A' ? hex_str[i] - 'A' + 10 : hex_str[i] - '0'];
	while (bin_str[0] == '0' && bin_str[1] != '.')
		bin_str.erase(0, 1);
	if (neg)
		bin_str = "-" + bin_str;
	return BigFloat::from_bin_str(bin_str);
}

BigFloat BigFloat::from_dec_str(string dec_str) {
	std::transform(dec_str.begin(), dec_str.end(), dec_str.begin(), ::tolower);
	bool neg = false;
	if (dec_str[0] == '-') {
		neg = true;
		dec_str.erase(0, 1);
	}
	if (dec_str == "0.0")
		return BigFloat::ZERO;
	if (dec_str == "inf")
		return BigFloat::INF;
	if (dec_str == "nan")
		return BigFloat::NaN;

	int e = dec_str.find('e');
	string dec_significand = dec_str.substr(0, e);
	dec_significand.erase(1, 1);
	int dec_exp = (long long)BigInt::from_dec_str(dec_str.substr(e + 1, dec_str.length() - 1 - e));
	dec_exp -= (e - 2);
	BigFloat res, ten = 10.0;
	for (int i = 0; i < (int)dec_significand.length(); ++i) {
		res = res * ten + (BigFloat)(double)(dec_significand[i] - '0');
	}
	while (dec_exp > 0) {
		--dec_exp;
		res = res * ten;
	}
	while (dec_exp < 0) {
		++dec_exp;
		res = res / ten;
	}
	return res;
}
