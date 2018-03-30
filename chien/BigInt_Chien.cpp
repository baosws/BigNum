#include "../includes.h"

// khởi tạo từ mảng bool
BigInt::BigInt(const bool* const binArr): BigNum(binArr) {}

// khởi tạo copy
BigInt::BigInt(const BigInt& bgNum) : BigNum(bgNum) {}

// khởi tạo từ số long long
BigInt::BigInt(long long llNum)
{
	this->data[0] = llNum;
	this->data[1] = -(llNum < 0);
}

// khởi tạo từ int
BigInt::BigInt(int num): BigInt((long long) num) {}


// phép nhân đầy đủ (128 bit x 128 bit = 256 bit)
// trả về 1 cặp là 128 bit cao và 128 bit thấp của tích
pair<BigInt, BigInt> BigInt::full_multiply(const BigInt& Mutiplier) const
{
	BigInt A(0);
	BigInt Q(Mutiplier);
	bool   Q_1 = 0;
	
	for(int i = 0; i < LENGTH_OF_BITS; i++)
	{
		switch(Q.get_bit(0) - Q_1)
		{
			case 1: 
				A = A - (*this);
				break;
			
			case -1: 
				A = A + (*this);
				break;
		}
		Q_1 = Q.get_bit(0);
		Q = Q >> 1;
		Q.set_bit(127, A.get_bit(0));
		A = A >> 1;
	}
	return pair<BigInt, BigInt>(A, Q);
}

// phép nhân mất mát (128 bit x 128 bit = 128 bit)
BigInt BigInt::operator*(const BigInt& Mutiplier) const
{
	return this->full_multiply(Mutiplier).second;
}

// phép chia đầy đủ, trả về phần dư và thương
pair<BigInt, BigInt> BigInt::full_divide(const BigInt& Divisor) const
{
	if (Divisor == (BigInt)0)
		throw "ERROR: Divided by zero!!!";
	bool neg = (this->get_bit(127) != Divisor.get_bit(127));

	BigInt A(0);
	BigInt M(Divisor);
	BigInt Q(*this);
	if (M < (BigInt)0)
		M = -M;
	if (Q < (BigInt)0)
		Q = -Q;
	for(int i = 0; i < 128; i++)
	{
		A = A << 1;
		A.set_bit(0, Q.get_bit(127));
		Q = Q << 1;
		A = A - M;
		if(A.get_bit(127) == 0) //(A >=0)?
			Q.set_bit(0, 1);		
		else
		{
			Q.set_bit(0, 0);
			A = A + M;
		}
	}
	if(neg == true) {
		A = -A;
		Q = -Q;
	}
	return pair<BigInt, BigInt>(A, Q);
}

// phép chia lấy phần nguyên
BigInt BigInt::operator/(const BigInt& Divisor) const {
	return this->full_divide(Divisor).second;
}

// phép chia lấy phần dư
BigInt BigInt::operator%(const BigInt& Divisor) const
{
	return this->full_divide(Divisor).first;
}

// phép dịch phải
BigInt BigInt::operator>>(int amountBits) const
{
	BigInt res(*this); //0000.1001 << 2 = 0010.0100
		
	if(amountBits == 128)
		res = 0;
	else			//1001.0000 << 2 = 0010.0100 <=> 1001.0000 >> 2 (với 2 bit dau =0)
		if(amountBits>0 && amountBits < 128)
		{
			bool signal = res.get_bit(127);

			for(int i = 0; i < 128 - amountBits; i++)
				res.set_bit(i, this->get_bit(i+amountBits));
			
			for (int i = 127; i >= 128 - amountBits; i--)
				res.set_bit(i, signal);
		}
	return res;
}

// phép dịch trái
BigInt BigInt::operator<<(int amountBits) const
{
	BigInt res(*this); //0000.1001 << 2 = 0010.0100

	if (amountBits >= 128)
	{
		if (res.get_bit(127) == 0)
			res = 0;
		else
			res = -1;
	}
	else			//1001.0000 << 2 = 0010.0100 <=> 1001.0000 >> 2 (với 2 bit dau =0)
	{
		if (amountBits > 0)
		{
			for (int i = 127; i >= amountBits; i--)
				res.set_bit(i, this->get_bit(i - amountBits));

			for (int i = amountBits-1; i>=0; i--)
				res.set_bit(i, false);

		}
	}
	return res;
}

// so sánh bé hơn
bool BigInt::operator < (const BigInt& other) const 
{
	if (this->get_bit(127) != other.get_bit(127))
		return this->get_bit(127) == 1;
	for (int i = LENGTH_OF_BITS - 1; i >= 0; --i)
		if (this->get_bit(i) != other.get_bit(i))
			return this->get_bit(i) < other.get_bit(i);
	return false;
}

// so sánh lớn hơn
bool BigInt::operator > (const BigInt &other) const
{
	if (this->get_bit(127) != other.get_bit(127))
		return this->get_bit(127) == 0;
	for (int i = LENGTH_OF_BITS - 1; i >= 0; --i)
		if (this->get_bit(i) != other.get_bit(i))
			return this->get_bit(i) > other.get_bit(i);
	return false;
}
