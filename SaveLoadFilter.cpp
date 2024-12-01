#include "stdafx.h"
#include "SaveLoadFilter.h"
#pragma warning(suppress : 4996)

void CountEqual() {
	fstream SourFile;
	long long prevnn = 0, nn;
	string prevrat, rat;
	int count = 0;

	SourFile.open("RatDataNormF.txt", ios::in, ios::binary);
	
	while (SourFile >> nn) {
		SourFile >> rat;
		if (nn == prevnn ) {
			count++;
			cout << count << endl;
				
		}
		prevnn = nn;
		prevrat = rat;
	}

	SourFile.close();
	system("pause");
};

void FilterForRatDataNorm() {
	fstream SourFile, DestFile;
	long long prevnn = 0, nn;
	string prevrat,rat, cicle, prevcicle;
	string buf;
	
	SourFile.open("RatDataNorm.txt", ios::in, ios::binary);
	DestFile.open("RatDataNormF.txt", ios::out, ios::binary);
	SourFile >> buf; //  считываем шапку
	DestFile << buf << '\t';
	SourFile >> buf; //  считываем шапку
	DestFile << buf << '\t';
#ifdef CICLE
	SourFile >> buf;
	DestFile << buf << endl;
	
#endif//CICLE
	

	while (SourFile >> nn) {
		SourFile >> rat;
		
#ifdef CICLE
		SourFile >> cicle;
#endif//CICLE

		if (nn - prevnn > 1) {
			if (prevnn != 0) {
				if (prevnn != nn) {
					DestFile << prevnn << '\t' << prevrat;
#ifdef CICLE
					DestFile << '\t' << prevcicle;
#endif//CICLE				
					 DestFile << endl;
				}
				DestFile << nn << '\t' << rat;
#ifdef CICLE
				DestFile << '\t' << cicle;
#endif//CICLE				
				DestFile << endl;
				
			}
			else {
				DestFile << nn << '\t' << rat;
#ifdef CICLE
				DestFile << '\t' << cicle;
#endif//CICLE				
				DestFile << endl;
			}
		}
		prevnn = nn;
		prevrat = rat;
		prevcicle = cicle;
	}

	DestFile << nn << '\t' << rat;
#ifdef CICLE
	DestFile << '\t' << cicle;
#endif//CICLE				
	DestFile << endl;
	
	DestFile.close();
	SourFile.close();
};

void CheckRec(MyRectangle* NewRec, long long i) {

	PF	HeightInPow = PowFromHeight(&NewRec->Height);
	ofstream SaveFile;
	size_t size;
	mp_exp_t exp = 0;

	if (NewRec->Width / HeightInPow > MaxRatNormRec) {

		MaxRatNormRec = NewRec->Width / HeightInPow;

		SaveFile.open("RatDataNorm.txt", ios::out | ios::app);
		SaveFile.seekp(0, ios::end);
		size = SaveFile.tellp();
		if (size == 0) {

			SaveFile << "Цикл       " << " Отношение_Шир/Высота^3/4" << 
#ifdef CICLE
				'\t' << " Цикл_родителя" <<
#endif//CICLE				
				endl;
		}

		SaveFile << i << '\t' << "0," << MaxRatNormRec.digit.get_str(exp) << "e" << exp <<
#ifdef CICLE
			'\t' << NewRec->parentcicle <<
#endif//CICLE
			endl;

		SaveFile.close();

	}


};

void SaveInFile(long long nn, fstream &SaveFile, vector <MyRectangle*> &Chain) {
	auto iter = Chain.cbegin();
	long long i = 0;
	MyRectangle * Rect;
	mp_exp_t exp = 0;

	if (nn % 1000 == 0)
		cout << Chain.size() << "   " << nn << endl;

	while (iter != Chain.end()) {
		Rect = Chain[i];
		SaveFile << "0," << Rect->Width.digit.get_str(exp) << "e" << exp << endl;
		SaveFile << "0," << Rect->Height.digit.get_str(exp) << "e" << exp << endl;
		SaveFile << endl;

		++iter;
		i++;
	};

}
void LoadData(string* name, long long &k) {

	fstream OpenFile;

	MyRectangle *NewRect;
	string buf;
	long long nn = 0;
	long long BankPos, CurPos;


	size_t n = 0;

	OpenFile.open(*name, ios::in, ios::binary);
	OpenFile >> k;// номер цикла прерывания
	OpenFile >> buf;
	PF s(buf);
	SVerySmall = s;
	CurPos = k / StepOfBank + 1;

	k += 1;

	cout << endl;


	while (OpenFile >> buf) {
		PFraction FileWidth = buf;
		OpenFile >> buf;
		PFraction FileHeight = buf;
		if (nn % 10000 == 0)
			cout << nn << "\r";
		NewRect = new MyRectangle(FileWidth, FileHeight);

		NewRect->checksize();
		BankPos = GetBankPos(NewRect->Width);
		if (BankPos <= CurPos || nn == 0) {//первый всегда в MainChain
			MainChain.push_back(NewRect);
		}
		else {
			if (BankPos < BankSize)
				Bank[BankPos - 1].push_back(NewRect);
			else
				;
		};
		nn++;
	};
	cout << endl;
	OpenFile.close();
	cout << "Количество считанных записей: " << nn << endl;
	cout << "Количество записей в MainChain: " << MainChain.size() << endl;
};

void SaveData(long long ii) {

	fstream SaveFile;
	mp_exp_t exp = 0;

	cout << "Сохранение..." << endl;
	SaveFile.open("SData" + to_string(ii) + ".txt", ios::out);

	SaveFile << ii << endl;// номер цикла прерывания
	SaveFile << "0," << SVerySmall.digit.get_str(exp) << "e" << exp << endl << endl;

	SaveInFile(ii, SaveFile, MainChain);
	for (long long n = 0; n < BankSize; n++) {
		SaveInFile(n, SaveFile, Bank[n]);
	}

	SaveFile.close();
	cout << "End saving" << endl;
};
void createstat(long long i) {

	size_t size;
	mp_exp_t exp = 0;
	fstream SaveFile;

	SaveFile.open("StatData.txt", ios::out | ios::app);

	SaveFile.seekp(0, ios::end);
	size = SaveFile.tellp();
	if (size == 0) {

		SaveFile << "Цикл       " << "| Приведенный Потенциал  " << endl;
	}

	SaveFile << i << "| " << "0," << (MainChain[0]->Width*MainChain[0]->Height*(i)).digit.get_str(exp)
		<< "e" << exp << endl;

	SaveFile.close();
};
void ShowCicle(long long i) {
	if (i < 1000000) {
		if (i % 1000 == 0) {
			FlagWasPrint = true;
		}
	}
	else {
		if (i % 10000 == 9999)
			FlagWasPrint = true;
	};
	if (i < 1000000) {
		if (i % 1000 == 999) {
			if (FlagWasPrint) {
				cout << i;
				cout << endl;
				ShowTime("End of cicle: ");
				FlagWasPrint = false;

			};
		};
	}
	else {
		if (i % 1000000 == 999999)
			if (FlagWasPrint) {
				cout << i;
				cout << endl;
				ShowTime("End of cicle: ");
				FlagWasPrint = false;
			};
	};

};
