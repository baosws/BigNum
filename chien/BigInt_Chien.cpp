#include "../includes.h"

//BigInt::BigInt(const string& decStr)
//{
// 	string binStr = decStrToBinStr(decStr);//hoặc là bool*
// 	for(int i = 0; i<128;i++)
// 		if(binStr[i] == '0')
// 			this->set_bit(i, 0);
// 		else
// 			this->set_bit(i, 1);
//}

BigInt::BigInt(const bool* const binArr): BigNum(binArr) {}

BigInt::BigInt(const BigInt& bgNum) : BigNum(bgNum) {}

BigInt::BigInt(long long llNum)
{
	this->data[0] = llNum;
	this->data[1] = 0;
}

BigInt::BigInt(int num): BigInt((long long) num) {}

// need more checking!!!
BigInt BigInt::operator*(const BigInt& Mutiplier) const
{
	BigInt A(0);
	BigInt Q(Mutiplier);
	bool	Q_1 = 0;
	
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
		Q = Q << 1;
		Q.set_bit(127, A.get_bit(0));
		A = A << 1;
		A.set_bit(127, A.get_bit(126));
		
		//Check overflow
		if(A != BigInt(0)) { // overflow
			// insert exception handling here
		}
	}
	return Q;
}

BigInt BigInt::operator/(const BigInt& Divisor) const
{
	bool flag = this->get_bit(127) != Divisor.get_bit(127);

	BigInt A(0);
	BigInt Q(*this); //Q = Dividend
	for(int i = 0;i < 128; i++)
	{
		//shift: [A,Q] << 1
		A = A << 1;
		A.set_bit(0, Q.get_bit(127));
		Q = Q << 1;
		
		A = A - Divisor;
		//if(A < 0)
		if(A.get_bit(127) == 0) //(A >=0)?
			Q.set_bit(0, 1);		
		else
		{
			Q.set_bit(0, 0);
			A = A + Divisor;
		}
	}
	if(flag == true)
		Q = 0-Q;
	return Q;
}


BigInt BigInt::operator<<(int amountBits) const
{
	BigInt res(*this); //0000.1001 << 2 = 0010.0100
		
	if(amountBits == 128)
		res = 0;
	else			//1001.0000 << 2 = 0010.0100 <=> 1001.0000 >> 2 (với 2 bit dau =0)
		if(amountBits>0 && amountBits < 128)
		{
			for(int i = 127; i>= amountBits; i--)
			{
				res.set_bit(i, this->get_bit(i-amountBits));
			}
		}
	return res;
}

BigInt BigInt::operator>>(int amountBits) const
{
	BigInt res(*this); //0000.1001 << 2 = 0010.0100
		
	if(amountBits >= 128)
	{
		if(res.get_bit(127)==0)
			res = 0;
		else
			res = -1;
	}	
	else			//1001.0000 << 2 = 0010.0100 <=> 1001.0000 >> 2 (với 2 bit dau =0)
	{
		if(amountBits > 0)
		{
			for(int i = 0; i + amountBits < 128; i++)
			{
				res.set_bit(i, this->get_bit(i+amountBits));
			}
		}
	}
	return res;
}
