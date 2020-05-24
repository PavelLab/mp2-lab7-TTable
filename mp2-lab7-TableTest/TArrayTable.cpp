#include "TArrayTable.h"

int TArrayTable::Reset() {
	//���������� �� ������ ������
	CurrPos = 0;
	return IsTabEnded();
}	

int TArrayTable::IsTabEnded() const {
	//�������� �� ���������� �������
	return CurrPos >= DataCount;
}

int TArrayTable::GoNext() {
	//������� � ���� ������
	if (!IsTabEnded()) CurrPos++;
	return IsTabEnded();
}

int TArrayTable::SetCurrentPos(int pos) {
	//���������� ���. �������
	CurrPos = ((pos > -1) && (pos < DataCount)) ? pos : 0;
	return IsTabEnded();
}	

//������
TKey TArrayTable::GetKey() const { 
	if ((DataCount == 0) || (CurrPos >= DataCount))
		throw NULL;
	return pRec[CurrPos].Key; 
}		//�������� ����

TValue TArrayTable::GetValue() const {
	if ((DataCount == 0) || (CurrPos >= DataCount))
		throw NULL;
	return pRec[CurrPos].Value; 
} //�������� ��������

