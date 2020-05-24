#pragma once
#include "TTable.h"

class TArrayTable : public TTable {
protected:
	TTabRecord *pRec;	//������ ��� ������
	int TabSize;		//������ �������
	int CurrPos;		//����� ������� ������(�� 0)

public:
	TArrayTable(int size = TabMaxSize) {
		pRec = new TTabRecord[size];
		TabSize = size;
		DataCount = CurrPos = 0;
	}
	~TArrayTable() {
		delete[]pRec;
	}


	//�������������� ������
	virtual bool IsFull() const { return DataCount >= TabSize; }
	int GetTabSize()const { return TabSize; }

	//������
	virtual TKey GetKey() const;	//�������� ����
	virtual TValue GetValue() const; //�������� ��������
	TTabRecord Get_pRec(int i) const { return pRec[i]; }

	//���������
	virtual int Reset();				//���������� �� ������ ������
	virtual int IsTabEnded() const;		//�������� �� ���������� �������
	virtual int GoNext();				//������� � ���� ������
	virtual int SetCurrentPos(int pos);	//���������� ���. �������
	int GetCurrentPos() const { return CurrPos; }

};