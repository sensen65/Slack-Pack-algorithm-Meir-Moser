#pragma once
#include "stdafx.h"

class MyRectangle
{
public:
	 
	PF Width;
	PF Height;
	bool Normstatus;
	bool FromNorm;
#ifdef CICLE
	long long parentcicle;
	long long curcicle;

#endif//CICLE

MyRectangle::MyRectangle (PF width, PF height, bool stat);

MyRectangle::MyRectangle(PF width, PF height
#ifdef CICLE
	, long long _curcicle = 0, long long _parentcicle = 0
#endif//CICLE
);
MyRectangle::MyRectangle(bool stat);

~MyRectangle(void);

void fillrect(PF width, PF height
#ifdef CICLE
	, long long _curcicle = 0, long long _parentcicle = 0
#endif//CICLE
	);
void checksize();

};

