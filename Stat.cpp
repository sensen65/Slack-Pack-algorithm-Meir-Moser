#include "stdafx.h"
#pragma warning(suppress : 4996)


void StatTorc(long long i) {

	long double rat = 0;
	long double width, height;
	ofstream SaveFile;
	size_t size;
	CounterTorc = 0;

	for (long i = 0; i < MainChain.size(); i++) {
		if (!MainChain[i]->Normstatus  && MainChain[i]->FromNorm) {
			CounterTorc++;
			width = MainChain[i]->Width.digit.get_d();
			height = MainChain[i]->Height.digit.get_d();
			rat = rat + height / width;

		}
	}

	for (long k = 0; k < BankSize; k++) {
		for (long n = 0; n < Bank[k].size(); n++) {
			if (!Bank[k][n]->Normstatus && 	Bank[k][n]->FromNorm) {
				CounterTorc++;
				width = Bank[k][n]->Width.digit.get_d();
				height = Bank[k][n]->Height.digit.get_d();
				rat = rat + height / width;
			}
		}
	}

	if (SmallCounterTorc != 0 || CounterTorc != 0) {
		rat = (rat + SmallRat) / (CounterTorc + SmallCounterTorc);
	}
	else
		rat = 0;



	SaveFile.open("RatData.txt", ios::out | ios::app);
	SaveFile.seekp(0, ios::end);
	size = SaveFile.tellp();
	if (size == 0) {

		SaveFile << "Цикл       " << " Колич 2-го рода " << " Колич 2-го рода отброшены " << " Среднее отнош Д/Ш" << " Среднее отнош Д/Ш отброшен" << endl;
	}


	SaveFile.precision(14);
	SaveFile << i << '\t' << '\t' << CounterTorc + SmallCounterTorc << '\t' << '\t' << SmallCounterTorc << '\t' << '\t' << rat <<
		'\t';
	if (SmallCounterTorc != 0) { SaveFile << SmallRat / SmallCounterTorc; }
	else { SaveFile << 0; }
	SaveFile << endl;
	SaveFile.close();

}
#ifdef DELTA
PF CalcDelta(long long i) {

	double dd;

	dd = pow(double(i), PowH / PowL);
	mpf_class f(dd);
	f = 1 / f;

	return f;

}

PF PowFromHeight(PF* Height) {
	double DHeight = Height->digit.get_d();

	DHeight = pow(DHeight, PowH/ PowL);
	mpf_class f(DHeight);

	return f;
};


#endif // DELTA
void calcstat(long long nn) {
	PF Sost(RR(0., RRPrecicion));
	long long i = MainChain.size();
	mp_exp_t exp = 0;

	for (long long n = 0; n < i; n++) {
		Sost = Sost + MainChain[n]->Width*MainChain[n]->Height;
	}
	for (long long n = 0; n < BankSize; n++) {
		for (long k = 0; k < Bank[n].size(); k++)
			Sost = Sost + Bank[n][k]->Width*Bank[n][k]->Height;
	}
	Sost = Sost + SVerySmall;

	cout << endl << "Sost = " << "0." << Sost.digit.get_str(exp) << "e" << exp << endl;
	cout << "Отклонение = " << "0," << (Sost - PF(RR(1., RRPrecicion) / (nn + 1))).digit.get_str(exp)
		<< "e" << exp << endl;

	cout << endl << "Ширина первого = " << "0," << MainChain[0]->Width.digit.get_str(exp) << "e" << exp << endl;
	cout << "Длина первого = " << "0," << MainChain[0]->Height.digit.get_str(exp) << "e" << exp << endl;

	cout << endl << "Приведенная Ширина первого = " << "0," << (MainChain[0]->Width*nn).digit.get_str(exp) << "e" << exp << endl;
	cout << "Приведенная Длина первого = " << "0," << (MainChain[0]->Height*nn).digit.get_str(exp) << "e" << exp << endl;
	cout << endl << "Потенциал = " << "0," << (MainChain[0]->Width*nn*MainChain[0]->Height*nn).digit.get_str(exp)
		<< "e" << exp << endl;

	cout << endl << "Приведенный Потенциал = " << "0," << (MainChain[0]->Width*MainChain[0]->Height*nn).digit.get_str(exp)
		<< "e" << exp << endl;

	cout << endl << "Количество записей = " << MainChain.size() << endl;
	cout << endl << "Цикл = " << nn << endl;


};

void ShowTime(const char * s) {
	//time_t timer;
	//struct tm *timeinfo;

	//	timer = time(NULL);
	//	timeinfo = localtime(&timer);
	//	cout << s << asctime(timeinfo) << std::endl;


};
