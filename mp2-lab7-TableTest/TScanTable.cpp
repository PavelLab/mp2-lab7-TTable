#include "TScanTable.h"

//����� ������
bool TScanTable::FindRecord(TKey k) {

	int i = 0;
	for (i = 0; i < DataCount; i++) {
		Efficiency++;
		if (pRec[i].Key == k) break;
	}

	if (i < DataCount) {
		CurrPos = i;
		return true;
	}
	return false;
}	

//�������� ������
int TScanTable::InsRecord(TKey k, TValue val) {
	if (IsFull()) {
		return TabFull;
	}
	else {
		bool res = FindRecord(k);
		if (res == true) {
			return TabRecDouble;
		}
		else {
			pRec[DataCount] = TTabRecord(k, val);
			DataCount++;
			return TabOK;
		}
	}
}

//������� ������	
int TScanTable::DelRecord(TKey k) {
	if (IsEmpty()) {
		return TabEmpty;
	}
	else {
		bool res = FindRecord(k);
		if (res == false) {
			return TabNoRec;
		}
		else {
			for (int i = CurrPos; i < DataCount - 1; i++) {
				pRec[i] = pRec[i + 1];//�����������
				Efficiency++;
			}
			DataCount--;
			return TabOK;
		}
	}
}				