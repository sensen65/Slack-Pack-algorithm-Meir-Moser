#pragma once

bool FlagOfGood = true, FlagWasPrint = false;
int TorcCounter = 1;
long long SmallCounterTorc = 0, CounterTorc = 0;
long double SmallRat = 0;
PF MaxRatNormRec(0, 1);
//long long NumOfCheck = StartPos;

#ifdef DELTA    //Если определена  DELTA то размещение с зазором, если нет - то классика
				//If DELTA is defined, then placement with a gap, if not, then classic
PF Delta;

#endif // DELTA


PF MinBorder(ZZ(1), ZZ(MaxCicle)), DoubleMinBorder(ZZ(1), ZZ(ZZ(MaxCicle))*ZZ(2));


#ifdef LOG	
long long StepStatistic = 10;// изменяемый шаг сохранения статистики
#else
long long StepStatistic = 1000000;// фиксированный шаг сохранения статистики
								  // fixed step of saving statistics
#endif //LOG

PF SVerySmall(0., RRPrecicion);


long long  GetBankPos(PF width);

long double PowH = 10;//числитель DeltaThe //numerator is Delta
long double PowL = 7;// знаменатель в Delta// the denominator in Delta

static long StartPos = 1000000; //начальная установка старта//initial start setting


static PF  a1(sqrt(1. / StartPos)),
a2(sqrt(1. / StartPos));// дроби для старта, размер длины квадрата
						// fractions for the start, the size of the length of the square

long long StepOfGoodChain = 10000;

static long StepAutoSave = 500000000;// шаг автосохранения// auto-save step

 // установки размера массива для хранения обрезков
 // setting the size of the array for storing scraps
const long StepOfBank = 10000;// ширина ячейки банка// width of the bank's cell
const long BankSize = 1000000;// MaxCicle / StepOfBank;
//установка предела вычислений//setting the calculation limit
long long MaxCicle = 10000000000;//MaxCicle = StepOfBank*BankSize !!!! Обязательно//Necessarily



