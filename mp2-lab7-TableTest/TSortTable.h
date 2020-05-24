#pragma once
#include "TScanTable.h"

enum TSortMethod { SELECT_SORT, QUICK_SORT };

class TSortTable:public TScanTable {
private:
	TSortMethod SortMethod; //индекс метода сортировки
	void SortData();	//сортировка данных
	void SelectSort();	//сортировка выбором
	void QuickSort();	//быстрая сортировка
	void QuickSorter(int first, int last);
public:
	TSortTable(int size = TabMaxSize) :TScanTable(size) {};
	TSortTable(const TScanTable &tab);				//преоб. типа
	TSortTable & operator =(const TScanTable &tab);	//присв. упоряд-ой неупоряд-ой
	
	void SetSortMethod(TSortMethod k) { SortMethod = k; };
	TSortMethod GetSortMethod() { return SortMethod; };

	virtual bool FindRecord(TKey k);			//найти запись
	virtual int InsRecord(TKey k, TValue val);	//добавить запись
	virtual int DelRecord(TKey k);				//удалить запись
};