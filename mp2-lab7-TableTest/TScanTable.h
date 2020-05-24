#pragma once
#include"TArrayTable.h"

class TScanTable :public TArrayTable {
public:
	TScanTable(int size = TabMaxSize) :TArrayTable(size) {};

	virtual bool FindRecord(TKey k);			//найти запись
	virtual int InsRecord(TKey k, TValue val) ;	//добавить запись
	virtual int DelRecord(TKey k);				//удалить запись

};