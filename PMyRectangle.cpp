#include <stdafx.h>


void MyRectangle::  fillrect(PF width, PF height
#ifdef CICLE
	 ,long long _curcicle, long long _parentcicle
#endif//CICLE
) {
	if (width < height)
	{
		Width = width;
		Height = height;

	}
	else {
		Width = height;
		Height = width;
	}
	Normstatus = true;
	FromNorm = true;

#ifdef CICLE
	curcicle = _curcicle;
	parentcicle = _parentcicle;
#endif//CICLE

};

MyRectangle::MyRectangle(PF width, PF height, bool NormStat)
{ 
  fillrect(width, height);
  Normstatus = NormStat;
  FromNorm = true;
#ifdef CICLE
  curcicle = 0;
  parentcicle = 0;
#endif//CICLE

};

MyRectangle::MyRectangle(PF width, PF height
#ifdef CICLE
	 , long long _curcicle, long long _parentcicle 
#endif//CICLE
)
{
	fillrect(width, height
#ifdef CICLE
		 ,_curcicle,_parentcicle 
#endif//CICLE	
	);
	Normstatus = true;
	FromNorm = true;
};

MyRectangle::MyRectangle(bool  stat) {
	
	Width = 0;
	Height = 0;
	Normstatus = stat;
	FromNorm = true;
#ifdef CICLE
	curcicle = 0;
	parentcicle = 0;
#endif//CICLE

};



MyRectangle::~MyRectangle(void)

{
	Width = 0;

	Height = 0;

};
void MyRectangle::  checksize() {
	PF buf;

	if (Width > Height) {
		buf = Height;
		Height = Width;
		Width = buf;
	}

};


