#include "../includes.h"

// chuyển từ chuỗi thập phân
BigInt BigInt::from_dec_str(string dec_str) {
	bool neg = false;
	if (dec_str[0] == '-') {
		neg = true;
		dec_str.erase(0, 1);
	}
	while (dec_str.length() < MAX_DEC_LENGTH)
		dec_str = '0' + dec_str;
	long long a[3] = {0};
	for (int i = 0; i < MAX_DEC_LENGTH; ++i) {
		a[i / 13] = a[i / 13] * 10 + dec_str[i] - '0';
	}
	BigInt res;
	const BigInt d(10000000000000ll);
	for (int i = 0; i < 3; ++i)
		res = res * d + BigInt(a[i]);
	if (neg)
		res = -res;
	return res;
}

// chuyển thành chuỗi thập phân
string BigInt::to_dec_str() const {
	if (this->get_bit(127) == 1)
		return "-" + (-*this).to_dec_str();
	const BigInt d(10000000000000ll);
	BigInt p(*this);
	long long a[3];
	a[0] = p % d;
	p = p / d;
	a[1] = p % d;
	a[2] = p / d;
	string res;
	for (int i = 0; i < MAX_DEC_LENGTH; ++i) {
		res = char(a[i / 13] % 10 + '0') + res;
		a[i / 13] /= 10;
	}
	while (res.length() > 1 && res[0] == '0')
		res.erase(0, 1);
	return res;
}

// chuyển từ chuỗi nhị phân
BigInt BigInt::from_bin_str(string binStr)
{
	BigInt res;
	res.data[0] = 0;
	res.data[1] = 0;
	bool neg = binStr[0] == '-';
	if (neg)
		binStr.erase(0, 1);
	int n = binStr.length();
	for (int i = 0; i < n; ++i)
		res.set_bit(n - 1 - i, binStr[i] == '1');
	if (neg)
		res = -res;
	return res;
}

// chuyển thành chuỗi nhị phân
string BigInt::to_bin_str() const {
	if (this->get_bit(127) == 1)
		return "-" + (-*this).to_bin_str();
	string res = "";
	for (int i = 0; i < LENGTH_OF_BITS; ++i)
		res = char(this->get_bit(i) + '0') + res;
	while (res.length() > 1 && res[0] == '0')
		res.erase(0, 1);
	return res;
}

// chuyển thành chuỗi hexa
string BigInt::to_hex_str() const {
	if (this->get_bit(127) == 1)
		return "-" + (-*this).to_hex_str();
	string res = "";
	for (int i = 0; i < LENGTH_OF_BITS; i += 4) {
		int c = (this->get_bit(i + 3) << 3)
			  + (this->get_bit(i + 2) << 2)
		  	  + (this->get_bit(i + 1) << 1)
			  + this->get_bit(i);	  
		res = char(c < 10 ? c + '0' : c - 10 + 'A') + res;
	}
	while (res.length() > 1 && res[0] == '0')
		res.erase(0, 1);
	return res;
}

// chuyển từ chuỗi hexa
BigInt BigInt::from_hex_str(string hex_str) {
	bool neg = false;
	if (hex_str[0] == '-') {
		neg = true;
		hex_str.erase(0, 1);
	}
	while (hex_str.length() < MAX_HEX_LENGTH)
		hex_str = '0' + hex_str;
	BigInt res;
	int n = hex_str.length();
	for (int i = 0; i < n; ++i) {
		int c = (hex_str[n - i - 1] >= 'A' ? hex_str[n - i - 1] - 'A' + 10 : hex_str[n - i - 1] - '0');
		res.set_bit(i << 2, c & 1);
		res.set_bit((i << 2) | 1, (c >> 1) & 1);
		res.set_bit((i << 2) | 2, (c >> 2) & 1);
		res.set_bit((i << 2) | 3, (c >> 3) & 1);
	}
	if (neg)
		res = -res;
	return res;
}

// lấy số đối
BigInt BigInt::operator-() const {
	return BigInt(0) - *this;
}

// trả về 1 nếu this khác 0, ngước lại 0
BigInt BigInt::operator!() const {
	BigInt result;
	result.data[0] = !(this->data[0] || this->data[1]);
	result.data[1] = 0;
	return result;
}

// phép not
BigInt BigInt::operator~() const {
	BigInt result;
	result.data[0] = ~this->data[0];
	result.data[1] = ~this->data[1];
	return result;
}

// phép and
BigInt BigInt::operator&(const BigInt& other) const {
	BigInt result;
	result.data[0] = this->data[0] & other.data[0];
	result.data[1] = this->data[1] & other.data[1];
	return result;
}

// phép or 
BigInt BigInt::operator|(const BigInt& other) const {
	BigInt result;
	result.data[0] = this->data[0] | other.data[0];
	result.data[1] = this->data[1] | other.data[1];
	return result;
}

// phép xor
BigInt BigInt::operator^(const BigInt& other) const {
	BigInt result;
	result.data[0] = this->data[0] ^ other.data[0];
	result.data[1] = this->data[1] ^ other.data[1];
	return result;
}

// phép gán
BigInt& BigInt::operator=(const BigInt& other) {
	BigNum::operator=(other);
	return *this;
}

// so sánh bằng
bool BigInt::operator==(const BigInt& other) const {
	return this->data[0] == other.data[0] && this->data[1] == other.data[1];
}

// so sánh khác
bool BigInt::operator!=(const BigInt& other) const {
	return !(*this == other);
}

// trả về true nếu this khác 0, ngược lại false
BigInt::operator bool() const {
	return this->data[0] != 0 || this->data[1] != 0;
}

// trả về mảng bool tương ứng với các bit
BigInt::operator bool*() const {
	bool* res = new bool[LENGTH_OF_BITS];
	for (int i = 0; i < LENGTH_OF_BITS; ++i)
		res[i] = this->get_bit(i);
	return res;
}

// ép kiểu về long long
BigInt::operator long long() const {
	return this->data[0];
}

// toán tử xuất
ostream& operator<<(ostream& os, const BigInt& p) {
	os << p.to_dec_str();
	return os;
}

// toán tử nhập
istream& operator>>(istream& is, BigInt& p) {
	string s;
	is >> s;
	p = BigInt::from_dec_str(s);
	return is;
}
