#include "../includes.h"
unsigned short get_exponent(const BigFloat&num)
{
	//set 15 exponet bits into unsigned short
	return unsigned short(0);
}
void BigFloat::set_exponent(unsigned short exp)
{
	//set first 15 bits of exp to exponent area
}
BigInt BigFloat::get_significand()
{
	//return 23bits of significand area
	return BigInt(0);
}
void BigFloat::set_significand(const BigInt& biNum)
{

}
void BigFloat::shift_significand_right(int)
{

}
void BigFloat::shift_significand_left(int)
{

}
bool BigFloat::is_exponent_overflow()
{
	return true;
}
bool BigFloat::is_exponent_underflow()
{
	return true;
}
bool BigFloat::is_significand_overflow()
{
	return true;
}
bool BigFloat::is_normalized()
{
	return true;
}
//-----------
BigFloat BigFloat::operator+(const BigFloat& another) const
{
	if (*this == BigFloat(0.0))
		return BigFloat(another);
	else 
	if (another == BigFloat(0.0))
		return BigFloat(*this);
	//res = X + Y
	BigFloat Y(another), X(*this);
	unsigned short X_exponent, Y_exponent;
	do
	{
		X_exponent = X.get_exponent();
		Y_exponent = Y.get_exponent();
		if (X_exponent == Y_exponent)
			break;
		else
		{
			if (X_exponent > Y_exponent)
			{
				X_exponent++;
				X.set_exponent(X_exponent);
				X.shift_significand_right(1); //logical shift
				if (X.get_significand() == BigInt(0))
					return Y;
			}
			else
			{
				Y_exponent++;
				Y.set_exponent(Y_exponent);
				Y.shift_significand_right(1);
				if (Y.get_significand() == BigInt(0))
					return X;
			}
		}
	} while (X_exponent != Y_exponent);

	BigFloat res(0.0);
	res.set_significand(X.get_significand() + Y.get_significand());
	
	if (res.get_significand() == BigInt(0))
		return res;//res=0
	
	if (res.is_significand_overflow())
	{
		res.shift_significand_right(1);
		X_exponent = res.get_exponent();
		X_exponent++;
		res.set_exponent(X_exponent);
		if (res.is_exponent_overflow())
			throw new exception("Exponent overflow!!!");
	}

	
	while (!res.is_normalized())
	{
		res.shift_significand_left(1);
		X_exponent = res.get_exponent();
		X_exponent--;
		res.set_exponent(X_exponent);
		if (res.is_exponent_underflow())
			throw new exception("Exponent underflow!!!");
	}
	//res = res.round();
	return res;

		
}