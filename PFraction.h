#pragma once


// класс псевдодробей. В начале использовалось рациональное представление, но в силу необходимости расчета до 
// 10^12 пришлось изменить представление чисел с плавающей запятона 
// a class of pseudo fractions. In the beginning, a rational representation was used, but due to the need 
//to calculate upto  10 ^12 had to change the representation of floating point numbers hidden
class PFraction

{
public:
	
	RR digit;

#ifdef _DEBUG
	std::string StrNum;
#endif
	PFraction(RR num);
	PFraction( ZZ num, ZZ denomin);
	PFraction(long long num, long long denomin);
	PFraction(long long num);
	PFraction(double num);
	PFraction(std::string num, std::string denomin);
	PFraction(std::string str);// "1.11e222"
	PFraction(void);
	~PFraction(void);

	PFraction abs(void);

	PFraction operator + (PFraction second);
	PFraction operator - ( PFraction second);
	
	PFraction operator - ();

	PFraction operator * ( PFraction second);
	PFraction operator * (long long second);
	PFraction operator * (mpz_class second);

	PFraction operator / ( PFraction second);
	void  operator = (const PFraction & second);
	void  operator = (const long long  second);
	void  operator = ( string &second);

	bool  operator == (PFraction second);
	bool  operator < (PFraction second);
	bool  operator <= (PFraction second);
	bool  operator > ( PFraction second);
	bool  operator >= (PFraction second);
	bool  operator >= (long long second);
	bool  operator != (PFraction second);

#ifdef _DEBUG
	friend void   pushtoSTR(RR &digit, std::string &str);
#endif
};

