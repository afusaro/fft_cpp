#ifndef _ccomplex_h
#define _ccomplex_h
#include <iostream.h>
//some comment test3
class Ccomplex
{
	private:
	  double real;
	  double imag;

	public:
	friend ostream& operator <<(ostream& os,Ccomplex& a);
	Ccomplex(float real=0, float imag=0);
	Ccomplex operator + (Ccomplex a);
	Ccomplex operator - (Ccomplex a);
	Ccomplex operator * (Ccomplex a);
	Ccomplex operator / (Ccomplex a);
	void setReal(float real);
	void setImag(float imag);
	float getReal(void);
	float getImag(void);

};


#endif
