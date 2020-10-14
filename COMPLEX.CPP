#include "ccomplex.h"
#include <iostream.h>
//other comment
Ccomplex::Ccomplex(float real, float imag)
{
	this->real=real;
	this->imag=imag;
}

Ccomplex
Ccomplex:: operator + (Ccomplex a)
{
	Ccomplex c;
	c.real=a.real+this->real;
	c.imag=a.imag+this->imag;
	return c;
}

Ccomplex
Ccomplex:: operator - (Ccomplex a)
{
	Ccomplex c;
	c.real=this->real-a.real;
	c.imag=this->imag-a.imag;
	return c;
}

Ccomplex
Ccomplex:: operator * (Ccomplex a)
{
	Ccomplex c;
	c.real=this->real*a.real -this->imag*a.imag;  //(ac-bd)
	c.imag=this->real*a.imag+this->imag*a.real; //(ad+bc)
	return c;
}

Ccomplex
Ccomplex:: operator / (Ccomplex a)
{
	Ccomplex c;
	float den=a.real*a.real+a.imag*a.imag; //(c^2+d^2)
	if (den!=0)
	{
		c.real=(this->real*a.real+this->imag*a.imag)/den;
		c.imag=(this->imag*a.real-this->real*a.imag)/den;
		return c;
	}
	else
	{
#ifdef DEBUG
		cout << "Error de division por 0\n";
#endif
		c.real=c.imag=0;
		return c;
	}
}
void
Ccomplex::setReal(float real)
{
	this->real=real;
}

void
Ccomplex::setImag(float imag)
{
	this->imag=imag;
}

float
Ccomplex:: getReal(void)
{
	return this->real;
}

float
Ccomplex:: getImag(void)
{
	return this->imag;
}

ostream&
operator <<(ostream& os,Ccomplex & a)
{
	os << a.real;
	if (a.imag>=0)
	{
		os << "+j";
		os << a.imag;
	}
	else
	{
		os << "-j";
		os << -a.imag;
	}

	return os;
}
