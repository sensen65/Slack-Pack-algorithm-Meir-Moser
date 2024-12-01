#pragma once



extern std::vector <MyRectangle*> MainChain/*, SmallChain*/;

extern std::vector <MyRectangle*> Bank[];


extern PF SVerySmall;
extern long double SmallRat;
extern long long SmallCounterTorc, CounterTorc ;

extern long long MaxCicle;
extern long double PowH;
extern long double PowL;

void StatTorc(long long i);

#ifdef DELTA
PF CalcDelta(long long i);

PF PowFromHeight(PF* Height);


#endif // DELTA

void calcstat(long long nn);

void ShowTime(const char * s);
