#pragma once


#pragma warning( disable : 4146 )

#include <tchar.h>
#include <stdio.h>
#include "vector"
#include "algorithm"
#include <time.h>
#include <iostream>
#include <conio.h>
#include <sstream>
#include "fstream"
#include <mpirxx.h>


using namespace std;
#pragma comment(linker, "/STACK:4000000000")

typedef mpz_class ZZ;
typedef mpf_class RR;

#define PFraction PF
#define RRPrecicion 64 // длина мантиссы PF// mantissa length PF
#include "PFraction.h"
#include "PMyRectangle.h"
#include "SaveLoadFilter.h"
#include "Stat.h"

static PF NuLLFraction("1e-30");





