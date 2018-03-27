#include "../includes.h"

//Checking the exponent will be overflow if increase 1
bool BigFloat::is_exponent_overflow()
{
	for (int i = 112; i <= 126;i++)
	if (this->get_bit(i) == false)
		return false;
	return true; 
}
//Checking the exponent will be overflow if decrease 1
bool BigFloat::is_exponent_underflow()
{ 
	for (int i = 112; i <= 126; i++)
	if (this->get_bit(i) == true)
		return false;
	return true; 
}
bool BigFloat::is_significand_overflow(){ return false; }
bool BigFloat::is_normalized()
{ 
	return ((this->get_exponent() != 0) && (this->get_significand() != BigInt(0)));
}

void BigFloat::shift_significand_right()
{
	for (int i = 111; i > 0; i--)
		this->set_bit(i, this->get_bit(i - 1));
	this->set_bit(0, false);
}
void BigFloat::shift_significand_left()
{
	for (int i = 0; i <= 110; i++)
		this->set_bit(i, this->get_bit(i + 1));
	this->set_bit(111, false);
}
//bool BigFloat::is_exponent_overflow()
//{
//	return true;
//}
//bool BigFloat::is_exponent_underflow()
//{
//	return true;
//}
//bool BigFloat::is_significand_overflow()
//{
//	return true;
//}
//bool BigFloat::is_normalized()
//{
//	return true;
//}
//-----------

BigFloat BigFloat::operator+(const BigFloat& another) const
{
	if (*this == BigFloat(0.0))
		return BigFloat(another);
	else 
	if (another == BigFloat(0.0))
		return BigFloat(*this);

	BigFloat Y(another), X(*this);
	unsigned short X_exponent, Y_exponent;
	
	//Balance two exponents
	do
	{
		X_exponent = X.get_exponent();
		Y_exponent = Y.get_exponent();
		if (X_exponent != Y_exponent)
		{
			if (X_exponent > Y_exponent)
			{
				X_exponent++;
				X.set_exponent(X_exponent);
				X.shift_significand_right(); //logical shift
				if (X.get_significand() == 0)
					return Y;
			}
			else
			{
				Y_exponent++;
				Y.set_exponent(Y_exponent);
				Y.shift_significand_right();
				if (Y.get_significand() == 0)
					return X;
			}
		}
	} while (X_exponent != Y_exponent);


	BigFloat res;
	res.add_signed_significands(X, Y);
	res.set_exponent(X_exponent);

	if (res.get_significand() == 0)
		return res;//res=0
	
	if (res.is_significand_overflow())
	{		
		if (res.is_exponent_overflow())
			throw new exception("Exponent overflow!!!");
		else
		{
			res.shift_significand_right();
			X_exponent++;
			res.set_exponent(X_exponent);
		}
	}

	
	while (!res.is_normalized())
	{
		if (res.is_exponent_underflow())
			throw new exception("Exponent underflow!!!");
		else
		{
			res.shift_significand_left();
			X_exponent = res.get_exponent();
			X_exponent--;
			res.set_exponent(X_exponent);
		}
	}
	//res = res.round();
	return res;		
}

BigFloat BigFloat::operator-(const BigFloat& another) const
{
	BigFloat temp(another);
	temp.set_bit(127, 1 - another.get_bit(127));
	return this->operator+(temp);
}


void BigFloat::add_signed_significands(const BigFloat&X, const BigFloat&Y)
{
	//Add signed significands
	BigInt X_significand = X.get_significand();
	BigInt Y_significand = Y.get_significand();

	if (X.get_bit(127) == 1)
		X_significand = BigInt(0) - X_significand;

	if (Y.get_bit(127) == 1)
		Y_significand = BigInt(0) - Y_significand;

	BigInt Added_Significands = X_significand + Y_significand;

	this->set_bit(127, Added_Significands.get_bit(127));

	//change res's significand if it was negative
	if (Added_Significands.get_bit(127) == 1)//negative
		Added_Significands = BigInt(0) - Added_Significands; //significand is unsigned

	this->set_significand(Added_Significands);//just set last 112 bit

}