// � ��������� ��������� ������������ ���������� MPIR(The Multiple Precision Integers and Rationals 
// Library), Edition 3.0.0. https://github.com/wbhart/mpir
//
//  this program uses the MPIR library(The Multiple Precision Integer and Rational
// Library), Edition 3.0.0. https://github.com/wbhart/mpir


#include "stdafx.h"
#include "Global.h"
#pragma warning(suppress : 4996)

std::vector <MyRectangle*> MainChain/*, SmallChain*/;// ������ ��� ��������� ����������� ��������
													//vector for storing operational scraps
std::vector <long long > GoodChain;// ������� � MainChain//indexes in the MainChain
std::vector <MyRectangle*> Bank[BankSize];//�������� ���� ��������
											//storing all the scraps


bool _FirstAbsorbSecond(MyRectangle * first, MyRectangle * second) {//��������� ��������� ��������������� 
																	//rectangle comparison procedure

	if ((first->Width - second->Width >= 0) && (first->Height - second->Height >= 0))
		return true;
	return false;
};


long long  GetBankPos(PF width) {// ��������� ����������� ������� � ��������� �� ������ �������
									//the procedure for determining the position in the storage by width is cropping
	long long pos;

	pos = ((PF(1.).digit.get_d() / width.digit.get_d()) / StepOfBank);

	return pos;
};

void ReloadMainChain(long long i) {// ������������ ��������� �������
									// reloading the main array

	long long BankPos = i / StepOfBank /*+1*/;
	mp_exp_t exp = 0;
	long long pos;
	std::vector <MyRectangle*> tmp;
	long double width, height;

	if (BankPos > BankSize)
		BankPos = BankSize;

	for (long k = 1; k < MainChain.size(); k++) { //�� 1, �.�. ������ ������ ����� ���
												  // from 1, because the LRP is always the first
		MainChain[k]->checksize();
		pos = GetBankPos(MainChain[k]->Width);
		if (pos >= BankSize) {
			SVerySmall = SVerySmall + MainChain[k]->Width*MainChain[k]->Height;

			if (!MainChain[k]->Normstatus && MainChain[k]-> FromNorm ) {  //������� ���������� ������� ���� 
																 //counting of endpoints of the second kind
				SmallCounterTorc++;
				width = MainChain[k]->Width.digit.get_d();
				height = MainChain[k]->Height.digit.get_d();
				SmallRat = SmallRat + height / width;
			}
			delete MainChain[k];
		}
		else {
			if (pos <= BankPos)
				pos = BankPos;
			Bank[pos].push_back(MainChain[k]);

		};
	};

	MainChain.erase(MainChain.begin() + 1, MainChain.end());
	for (long k = 0; k <= BankPos; k++) {

		for (size_t m = 0; m < Bank[k].size(); m++) {
			MainChain.push_back(Bank[k][m]);
		}
		if (Bank[k].size() > 0) {
			Bank[k].clear();
			Bank[k].swap(tmp);
		};
	};
};


void  DeleteGoodChain(long long nn) {// �������� ������� ��������
										//// deleting an array of indexes

	GoodChain.clear();
	ReloadMainChain(nn);

};


bool CreatGoodChain(long long  i, ZZ &NumOfCicles) {// �������� ������� ��������
													// creating an array of indexes

	bool flag = false;
	MyRectangle *PerspRect;
	//auto  iter = MainChain.cbegin();
	unsigned long long n = 0;
	PF DeltaBorder;

	DeltaBorder = CalcDelta(i+StepOfGoodChain);

	DeleteGoodChain(i);

	if (i % StepOfGoodChain == 0) {

		PerspRect = new MyRectangle(PF(1, i + StepOfGoodChain + 1), PF(1, i + StepOfGoodChain));
	}
	else {
		PerspRect = new MyRectangle(PF(1, i + StepOfGoodChain - i % StepOfGoodChain + 1), PF(1,
			i + StepOfGoodChain + 1 - i % StepOfGoodChain));
	}

#ifdef DELTA
	PerspRect->Width = PerspRect->Width + DeltaBorder;
	PerspRect->Height = PerspRect->Height + DeltaBorder;
#endif // DELTA

	PerspRect->checksize();

	for (n = 0; n<MainChain.size(); n++) {
		if (_FirstAbsorbSecond(MainChain[n], PerspRect)) {
			GoodChain.push_back(n);
			flag = true;
		}
		else {
			if (MainChain[n]->Width < MinBorder || MainChain[n]->Height < MinBorder) {
				MainChain.erase(MainChain.cbegin() + n);
				n--;
			};
		};
	};//for
	delete PerspRect;
	return flag;
};


//����� ������������ ����������� ������� � MainChain ����� GoodChain
//search for the minimum suitable pruning in the MainChain via GoodChain
long long  FindMinRect(MyRectangle* RectPtr, vector < long long> &Chain, unsigned long long i) {

	ZZ poten_n, poten_index;
	long long index = -1;
	long long n = 0;
	auto  iter = Chain.cbegin();
	PF MaxWidth((long long)0);

	while (iter != Chain.end()) {
		if (_FirstAbsorbSecond(MainChain[Chain[n]], RectPtr)) {
			if (index != -1) {
				if (MainChain[Chain[n]]->Width > MaxWidth) {
					MaxWidth = MainChain[Chain[n]]->Width;
					index = n;
				}
			}
			else
				index = n;
		};
		n++;
		++iter;
	};
	return index;
};

// ����� ������ ���������, �� �������� ������ �����
// when the widths match, then we cut off only the length
long long ClipRectWithoutNew(vector <MyRectangle*> &Chain, long long CIndex, PF &TargDim, PF &RectDim, long long i) {

	
#ifdef DELTA
	TargDim = TargDim -RectDim + Delta;
#else
	TargDim = TargDim - RectDim; // �������
#endif
	return Chain.size();

};

//���������� ������� � MainChain, ��� Bank ��� �����������, ���� ������� �� ������� ����������
//Placing the trim in the MainChain, or Bank, or discarding if it goes beyond the calculation boundary
void AllocRect(MyRectangle * Rec, long long border, long long i)
{
	long long BankPos;
	MyRectangle NextRect(PF(1, border + 1), PF(1, border));

	BankPos = GetBankPos(Rec->Width);
	if (BankPos <= i / StepOfBank/*+1*/) {
		MainChain.push_back(Rec);
		if (_FirstAbsorbSecond(Rec, &NextRect))
			GoodChain.push_back(MainChain.size() - 1);
	}
	else {
		if (BankPos < BankSize) {
			Bank[BankPos - 1].push_back(Rec);
		}
		else {

			SVerySmall = SVerySmall + Rec->Height * Rec->Width;
			delete Rec;

		}
	};

}

// ����������� ���������� ������ � ��������� �������
// Recursive placement of a part in the selected crop

long long CLipRect(long long CIndex, MyRectangle * Rect, long long &i, ZZ NumOfCicles) { // �������� �������������� ����������

	PF Smin = NuLLFraction;
	MyRectangle NextRect(PF(1, i + 2), PF(1, i + 1)
#ifdef CICLE
		, i
#endif//CICLE
		);

	long long LastRec = -1;
	MyRectangle *NewRec;

#ifdef DELTA
	PF NextDelta = CalcDelta(i + 1);

	NextRect.Width = NextRect.Width + NextDelta;
	NextRect.Height = NextRect.Height + NextDelta;

#endif // DELTA	

	ShowCicle(i);
	MainChain[GoodChain[CIndex]]->checksize();//�������� ����������//orientation check
	Rect->checksize();



	// ����  ������ ������ � ��������� ���������
	// if the width of the part and the workpiece are the same
	if (MainChain[GoodChain[CIndex]]->Width - Rect->Width == PF(0.)) {
		LastRec = ClipRectWithoutNew(MainChain, GoodChain[CIndex], MainChain[GoodChain[CIndex]]->Height, Rect->Height, i);
		
		if (MainChain[GoodChain[CIndex]]->Height == PF(0.)) {
			MainChain.erase(MainChain.begin() + CIndex);
		    GoodChain.erase(GoodChain.begin() + CIndex);
		} else
			MainChain[GoodChain[CIndex]]->checksize();
#ifdef DELTA
		MyRectangle *NewRec1 = new MyRectangle(Delta, Rect->Height - Delta
#ifdef CICLE
			, i, MainChain[GoodChain[CIndex]]->curcicle
#endif//CICLE
			);
		AllocRect(NewRec1, i/ StepOfGoodChain*StepOfGoodChain+ StepOfGoodChain, i);
#endif //DELTA	

		
		return LastRec;
	}
	else { //������� ������ ������, ��� � ���������
		   //the sides of the part are smaller than those of the workpiece

		if (CIndex == 0) {//�������� ������� �� ���
						  // cut the strip from the LRP
	
		    createstat(i);///!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!	
			MainChain[GoodChain[CIndex]]->Height = MainChain[GoodChain[CIndex]]->Height -
				Rect->Width;//������� ����� �������
							// The upper part was cut off

			NewRec = new MyRectangle(Rect->Width, MainChain[GoodChain[CIndex]]->Width
#ifdef CICLE
				,i, MainChain[GoodChain[CIndex]]->curcicle
#endif//CICLE
			); // ����� ������� �� ���
			   // new strip from LRP
			NewRec->FromNorm = false; //����������, ��� �������� �� �� ���������� �������
									  //indicates that the end face is not from a normal strip
            MainChain[GoodChain[CIndex]]->checksize();//�������� ����������//orientation check
			NewRec->checksize();
			// ���������� ������� � MainChain// placing the strip in the MainChain
			AllocRect(NewRec, i / StepOfGoodChain*StepOfGoodChain + StepOfGoodChain, i);

			LastRec = MainChain.size();
			i--;//�������� �������, �� �� ��������� ������//cut the strip, but did not place the parts
			return LastRec;
		}
		else { //�� ���// not LRP

#ifdef DELTA
			MainChain[GoodChain[CIndex]]->Height = MainChain[GoodChain[CIndex]]->Height -
			Rect->Height+Delta;//������� ����� �������

			NewRec = new MyRectangle(MainChain[GoodChain[CIndex]]->Width - Rect->Width+Delta,
									Rect->Height-Delta
#ifdef CICLE
				,i, MainChain[GoodChain[CIndex]]->curcicle
#endif//CICLE
			);

#else //DELTA
			MainChain[GoodChain[CIndex]]->Height = MainChain[GoodChain[CIndex]]->Height -
			Rect->Height;//������� ����� �������

			NewRec = new MyRectangle(MainChain[GoodChain[CIndex]]->Width - Rect->Width ,
			Rect->Height);
#endif // Delta


			MainChain[GoodChain[CIndex]]->checksize();//�������� ����������//orientation check
			NewRec->checksize();
			if (MainChain[GoodChain[CIndex]]->Normstatus) {
				CheckRec(NewRec, i);
			}

						
			AllocRect(NewRec, i / StepOfGoodChain*StepOfGoodChain + StepOfGoodChain, i);
			LastRec = MainChain.size();

			if ((i + 1) % StepOfGoodChain == 0)// ���� ���� ���������// if the cycle is the last one
				return LastRec;
			if ((_FirstAbsorbSecond(MainChain[GoodChain[CIndex]], &NextRect))) {
				i++;
#ifdef DELTA 

				Delta = NextDelta;

#endif // Delta
				LastRec = CLipRect(CIndex, &NextRect, i, NumOfCicles);
				return LastRec;
			}
			else {
				MainChain[GoodChain[CIndex]]->Normstatus = false; // ��� ���������, ��� �������� �������
																  // this is an indication that the end trim is
			}
			
		}//�� ���//not LRP

	}
	return LastRec;

};



int main(int argc, char* argv[])
{

	
	string arg;

	long long  k = 0, ChainIndex, NewStepGCh;
	ZZ  NumOfCicles;

	long long i;

	char answer;

	MyRectangle* StartRect;

	setlocale(LC_ALL, ".1251");

	NewStepGCh = StepOfGoodChain;
	
	NumOfCicles = MaxCicle;

	if (argc >1) {
		arg = string("SData.txt");
		ShowTime("������ ��������: ");
		LoadData(&arg, k);
		ShowTime("��������� ��������: ");
		calcstat(k);
		if (k > StepOfGoodChain - 1) {
			if (!CreatGoodChain(k, NumOfCicles)) {
				cout << "��������� ����������1. ��� �������������� ��� �����  = " << k << endl;
				std::system("pause");
				return 1;
			};
		};
	}
	else {
		k = StartPos;
		StartRect = new MyRectangle(a1, a2
#ifdef CICLE
			, k, k
#endif//CICLE
				);

		MainChain.push_back(StartRect);
		if (!CreatGoodChain(k, NumOfCicles)) {
			cout << "��������� ����������2. �� ������ ������������� ��� �����  = " << k << endl;
			std::system("pause");
			return 1;
		};
	};



	// �������� ����// main cycle
	i = k;
 	for (i = k; i< NumOfCicles + ZZ(1); i++) {
#ifdef DELTA

		Delta = CalcDelta(i);

#endif // DELTA

		StartRect = new MyRectangle(PF(1, i + 1), PF(1, i)// �������� ������ ��� ������
														  // creating a part without a gap
#ifdef CICLE
			, i, i
#endif//CICLE	
		);

#ifdef DELTA
		// ��������� ����� � ������// adding a gap to the part
		StartRect->Width = StartRect->Width + Delta;
		StartRect->Height = StartRect->Height + Delta;

#endif // DELTA

		
		if ((i % StepOfGoodChain == 0) || ((i % StepOfGoodChain == 1) && (FlagOfGood == false))) {
				FlagOfGood = true;
				ShowTime("������ ����� : ");
				if (!CreatGoodChain(i, NumOfCicles)) {
					cout << "��������� ����������2. �� ������ ������������� ��� �����  = " << i << endl;
					std::system("pause");
					return 1;
				};
				ShowTime("�����  �������� �������: ");
		};
		if ((i % StepOfGoodChain == 2) || (i%StepOfGoodChain == 3))
				FlagOfGood = false;
		if (NewStepGCh != StepOfGoodChain) {
			StepOfGoodChain = NewStepGCh;
			//NewStepGCh =StepOfGoodChain ;
			if (!CreatGoodChain(i, NumOfCicles)) {
				cout << "��������� ����������3. ��� �������������� ��� �����  = " << i << endl;
				std::system("pause");
				return 1;
			};
		}
		ChainIndex = FindMinRect(StartRect, GoodChain, i);
		if (ChainIndex == -1) {
			cout << "��������� ����������4.  �� ������ ������������� ��� �����  = " << i << endl;
			calcstat(i);
			std::system("pause");
			return 1;
		};

		if (CLipRect(ChainIndex, StartRect, i, NumOfCicles) == -1) {
			cout << "��������� ����������5. ������� ��������� ��� �����  = " << i << endl;
			calcstat(i);
			std::system("pause");
			return 1;
		};

		if ((MainChain[GoodChain[GoodChain.size() - 1]]->Width <= PF(0.)) ||
			(MainChain[GoodChain[GoodChain.size() - 1]]->Height <= PF(0.))) {
			cout << "��������� ����������6.��������� �������� ������ ��� ����� �������������� � GoodChain ��� ����� n = " << i << endl;

			calcstat(i);
			std::system("pause");
			return 1;
		};
		// ������ ��� ��������	// service for monitoring
		if (i % 100 == 0) {
			FlagWasPrint = true;
		}
		if (i % 100 == 99) {
			if (FlagWasPrint) {
	//			cout << i;
	//			cout << endl;
				ShowTime("End of cicle: ");
				FlagWasPrint = false;
			};
		}
		delete StartRect;
		if (NewStepGCh != StepOfGoodChain) {
			StepOfGoodChain = NewStepGCh;
			if (!CreatGoodChain(i, NumOfCicles)) {
				cout << "��������� ����������. ��� �������������� ��� �����  = " << i << endl;
				std::system("pause");
				return 1;
			};
		}

		// ���������� �� ����� �������// control during calculation
		if (_kbhit() ) {
			cout << i << endl << "�����������? (Y/N)";
			cin >> answer;
			if ((answer == 'Y') || (answer == 'y')) {
				calcstat(i);
				system("pause");
			}
			cout << "Want save? (Y/N)";
			cin >> answer;
			if ((answer == 'Y') || (answer == 'y')) {
				SaveData(i);//��������� ������ � ����
			};
			cout << "Want exit? (Y/N)";
			cin >> answer;
			if ((answer == 'Y') || (answer == 'y')) {
				return 0;
			}
			cout << "��������� ��� �������? (Y/N)" << StepOfGoodChain << endl;
			cin >> answer;
			if ((answer == 'Y') || (answer == 'y')) {
				cin >> NewStepGCh;
			}
		
		};


	};//for

	createstat(i);
	

	
	return 0;
};

