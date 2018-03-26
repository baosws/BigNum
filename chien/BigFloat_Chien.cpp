#include "../includes.h"
unsigned short BigFloat::get_exponent()
{
	//set 15 exponet bits into unsigned short
	unsigned short res = 0;
	return res;
}

void BigFloat::set_exponent(unsigned short exp)
{
	//set first 15 bits of exp to exponent area
}
bool BigFloat::is_exponent_overflow(){ return false; }
bool BigFloat::is_exponent_underflow(){ return false; }
bool BigFloat::is_significand_overflow(){ return false; }
bool BigFloat::is_normalized(){ return false; }

BigInt BigFloat::get_significand() const
{
	BigInt res(0);
	for (int i = 0; i <= 111; i++)
		res.set_bit(i, this->get_bit(111-i));
	return res;
}
void BigFloat::set_significand(const BigInt& biNum)
{
	for (int i = 0; i <= 111; i++)
		this->set_bit(i, biNum.get_bit(111-i));
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

	if (res.get_significand() == 0)
		return res;//res=0
	
	if (res.is_significand_overflow())
	{
		res.shift_significand_right();
		X_exponent++;
		res.set_exponent(X_exponent);
		if (res.is_exponent_overflow())
			throw new exception("Exponent overflow!!!");
	}

	
	while (!res.is_normalized())
	{
		res.shift_significand_left();
		X_exponent = res.get_exponent();
		X_exponent--;
		res.set_exponent(X_exponent);
		if (res.is_exponent_underflow())
			throw new exception("Exponent underflow!!!");
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