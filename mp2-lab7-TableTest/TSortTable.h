#pragma once
#include "TScanTable.h"

enum TSortMethod { SELECT_SORT, QUICK_SORT };

class TSortTable:public TScanTable {
private:
	TSortMethod SortMethod; //������ ������ ����������
	void SortData();	//���������� ������
	void SelectSort();	//���������� �������
	void QuickSort();	//������� ����������
	void QuickSorter(int first, int last);
public:
	TSortTable(int size = TabMaxSize) :TScanTable(size) {};
	TSortTable(const TScanTable &tab);				//�����. ����
	TSortTable & operator =(const TScanTable &tab);	//�����. ������-�� ��������-��
	
	void SetSortMethod(TSortMethod k) { SortMethod = k; };
	TSortMethod GetSortMethod() { return SortMethod; };

	virtual bool FindRecord(TKey k);			//����� ������
	virtual int InsRecord(TKey k, TValue val);	//�������� ������
	virtual int DelRecord(TKey k);				//������� ������
};