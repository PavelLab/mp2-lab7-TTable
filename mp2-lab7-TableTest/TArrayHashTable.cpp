#include "TArrayHashTable.h"

TArrayHashTable::TArrayHashTable(int size, int Step) {
	TabSize = size; HashStep = Step;
	pRec = new TTabRecord[TabSize];
	Empty = TTabRecord(-1);
	Mark = TTabRecord(-2);
	for (int i = 0; i < TabSize; i++) {
		pRec[i] = Empty;
	}
}

TArrayHashTable::~TArrayHashTable() {
	delete[]pRec;
}


//����� ������
bool TArrayHashTable::FindRecord(TKey k) {
	bool res = false;
	FreePos = -1;
	CurrPos = HashFunc(k) % TabSize;
	for (int i = 0; i < TabSize; i++) {
		Efficiency++;
		if (pRec[CurrPos] == Empty)			//��������� ������-��� ������-����� ������
			break;
		else if (pRec[CurrPos] == Mark) {	//��������� ������-���������� 1��-���������� �����
			if (FreePos == -1)
				FreePos = CurrPos;
		}
		else if(pRec[CurrPos].Key==k){		//����� ����
			res = true;
			break;
		}
		CurrPos = GetNextPos(CurrPos);		//�����������
	}
	return res;
}			

//�������� ������
int TArrayHashTable::InsRecord(TKey k, TValue val) {
	if (IsFull()) {
		return TabFull;
	}
	else {
		bool res = FindRecord(k);
		if (res == true) {
			return TabRecDouble;
		}
		else {
			if (FreePos = !- 1)
				CurrPos = FreePos;//���������� 1�� ������ ������
			pRec[CurrPos] = TTabRecord(k, val);
			DataCount++;
			return TabOK;
		}
	}
}

//������� ������
int TArrayHashTable::DelRecord(TKey k) {
	if (IsEmpty()) {
		return TabEmpty;
	}
	else {
		bool res = FindRecord(k);
		if (res == false) {
			return TabNoRec;
		}
		else {
			pRec[CurrPos] = Mark;
			DataCount--;
			return TabOK;
		}
	}
}


//���������
int TArrayHashTable::Reset() {
	CurrPos = 0;
	while (CurrPos < TabSize){	//����� 1�� �������� ������
		if ((pRec[CurrPos] != Empty) && (pRec[CurrPos] != Mark))//�� ����-�� � �� �����-�����
			break;
		else CurrPos++;
	}
	return IsTabEnded();
}

int TArrayHashTable::IsTabEnded() const {
	return CurrPos >= TabSize;
}

int TArrayHashTable::GoNext() {
	CurrPos++;
	while (CurrPos < TabSize) {	//����� ����. �������� ������
		if ((pRec[CurrPos] != Empty) && (pRec[CurrPos] != Mark))//�� ����-�� � �� �����-�����
			break;
		else CurrPos++;
	}
	return IsTabEnded();
}


//������
TKey TArrayHashTable::GetKey()const { 
	if ((DataCount == 0) || (CurrPos >= TabSize))
		throw NULL;
	return pRec[CurrPos].Key; 
}

TValue TArrayHashTable::GetValue()const { 
	if ((DataCount == 0) || (CurrPos >= TabSize))
		throw NULL;
	return pRec[CurrPos].Value; 
}