#pragma once
extern std::vector <MyRectangle*> MainChain/*, SmallChain*/;
extern bool FlagOfGood, FlagWasPrint;
extern  const long StepOfBank;
extern const long BankSize;
extern  long long MaxCicle;
extern PF MaxRatNormRec;


extern long long  GetBankPos(PF width);
// сервисные процедуры // service procedures
void SaveInFile(long long nn, fstream &SaveFile, vector <MyRectangle*> &Chain);;
	
void LoadData(string* name, long long &k);

void SaveData(long long ii);
void ShowCicle(long long i);
void createstat(long long i);
void CheckRec(MyRectangle* NewRec, long long i);
void CountEqual();
void FilterForRatDataNorm();