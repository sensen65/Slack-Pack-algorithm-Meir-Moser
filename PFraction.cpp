
#include "stdafx.h"
#include "PFraction.h"



PFraction::PFraction(RR num)
{

	digit = (RR(num, RRPrecicion));

#ifdef _DEBUG
	pushtoSTR(digit, StrNum);
#endif
};
PFraction::PFraction(  ZZ num,  ZZ denomin)
{ 
	
	digit = RR(RR(num, RRPrecicion)/RR(denomin,RRPrecicion),RRPrecicion);

#ifdef _DEBUG
  pushtoSTR(digit, StrNum);
#endif
};

PFraction::PFraction( std::string num, std::string denomin)
{
	digit.set_prec(RRPrecicion);
	digit = 0;
	
	digit = RR(RR(num, RRPrecicion,10) / RR(denomin, RRPrecicion,10), RRPrecicion);

#ifdef _DEBUG
	pushtoSTR(digit, StrNum);
#endif
};

PFraction::PFraction(std::string str)// "1,11e222"
{
	digit.set_prec(RRPrecicion);
	digit = 0;
	
	digit = RR((const string)str, RRPrecicion, 10);
#ifdef _DEBUG
	pushtoSTR(digit, StrNum);
#endif

}

PFraction::PFraction(long long  num, long long denomin)
{
	digit.set_prec(RRPrecicion);
	this->digit = RR(RR(num, RRPrecicion) / RR(denomin, RRPrecicion), RRPrecicion);

#ifdef _DEBUG
	pushtoSTR(this->digit, this->StrNum);
#endif
	
	
};

PFraction::PFraction(long long num) {

	digit.set_prec(RRPrecicion);
	this->digit = RR(num, RRPrecicion) ;

#ifdef _DEBUG
	pushtoSTR(this->digit, this->StrNum);
#endif
};

PFraction::PFraction( double num) {

	digit.set_prec(RRPrecicion);
	this->digit = RR(num, RRPrecicion);

#ifdef _DEBUG
	pushtoSTR(this->digit, this->StrNum);
#endif
}



PFraction::PFraction(void)
{ 
	digit.set_prec(RRPrecicion);
	digit = RR(0,RRPrecicion);
  

 #ifdef _DEBUG
  pushtoSTR(digit, StrNum);
#endif
};

PFraction::~PFraction(void)

{

	 digit =RR(0);
	 

};



PFraction PFraction::abs(void) {
	if (digit >= 0)
		return *this;
	else
		return -(*this);

};

bool PFraction::operator == (PFraction second) {

	
	if ((digit == second.digit)||((*this - second).abs() < NuLLFraction))
		return true;
	return false;

};

bool  PFraction::operator <= (PFraction second) {
	
	if ((digit <= second.digit) || ((*this - second).abs() < NuLLFraction))
		return true;
	return false;

};


bool  PFraction::operator < (PFraction second) {

	if (digit < second.digit)
		return true;
	return false;

  };

bool  PFraction::operator > (PFraction second)
{
	if (digit > second.digit)
		return true;
	return false;

};

bool PFraction::operator>=( PFraction second)
{
    if ((digit >= second.digit) || ((*this - second).abs() < NuLLFraction))
	    return true; 
	return false;
};

bool  PFraction::operator >= (long long second) {
	if ((digit >= second) || ((*this - second).abs() < NuLLFraction))
		return true;
	return false;
};

bool  PFraction::operator != (PFraction second)
{
	if ( (digit!= second.digit) || ((*this - second).abs() > NuLLFraction))
		return true;
	return false;

};

PFraction PFraction::operator + (PFraction second) {
		
	PF result(0.);
	result.digit.set_prec(RRPrecicion);
	result.digit = this->digit + second.digit;

#ifdef _DEBUG
	pushtoSTR(result.digit, result.StrNum);
#endif	
	return result;
};



PFraction PFraction::operator - (PFraction second) {
	PF result(0.);
	result.digit.set_prec(RRPrecicion);
	result.digit = this->digit - second.digit;

#ifdef _DEBUG
	pushtoSTR(result.digit, result.StrNum);
#endif	
	return result;
};

PFraction PFraction::operator - () {
	PF result(0.);
	result.digit.set_prec(RRPrecicion);
	result.digit = - this->digit;

#ifdef _DEBUG
	pushtoSTR(result.digit, result.StrNum);
#endif	
	return result;

};

PFraction PFraction::operator * ( PFraction second) {
	PF result(0.);
	result.digit.set_prec(RRPrecicion);
	result.digit = this->digit * second.digit;

#ifdef _DEBUG
	pushtoSTR(result.digit, result.StrNum);
#endif	
	return result;
};

PFraction PFraction:: operator * (long long second) {
	PF result(0.);
	result.digit.set_prec(RRPrecicion);
	result.digit = this->digit * second;

#ifdef _DEBUG
	pushtoSTR(result.digit, result.StrNum);
#endif	
	return result;

};

PFraction PFraction:: operator * (mpz_class second) {
	PF result(0.);
	result.digit.set_prec(RRPrecicion);
	result.digit = this->digit * second;

#ifdef _DEBUG
	pushtoSTR(result.digit, result.StrNum);
#endif	
	return result;

};

 PFraction PFraction::operator / (PFraction second) {

	 PF result(0.);
	 result.digit.set_prec(RRPrecicion);
	 result.digit = this->digit / second.digit;

#ifdef _DEBUG
	 pushtoSTR(result.digit, result.StrNum);
#endif	
	 return result;
};





void  PFraction::operator = (const PFraction &  second) {
	
	digit.set_prec(RRPrecicion);
	this->digit = second.digit;

#ifdef _DEBUG
	pushtoSTR(this->digit, this->StrNum);
#endif	
	
};

void  PFraction::operator = ( string  &second) {

	digit.set_prec(RRPrecicion);
	this->digit.set_str(second,10);

#ifdef _DEBUG
	pushtoSTR(this->digit, this->StrNum);
#endif	

};


void  PFraction::operator = (const long  long second) {

	this->digit.set_prec(RRPrecicion);
	this->digit = second;

#ifdef _DEBUG
	pushtoSTR(this->digit, this->StrNum);
#endif	

};


#ifdef _DEBUG
void pushtoSTR(RR & digit, std::string & str)
{
	std::stringstream buf;
	RR rr_buf(0,RRPrecicion);
	mp_exp_t exp(0);


	str.erase();
	if(digit>=0)
	   buf << "0." << digit.get_str(exp, int(10), RRPrecicion) << "e" << exp << endl;
	else {
		rr_buf = -digit;
		buf << "-0." << rr_buf.get_str(exp, int(10), RRPrecicion) << "e" << exp << endl;
	}
	
	str = buf.str();
	buf.str(std::string());
}

#endif