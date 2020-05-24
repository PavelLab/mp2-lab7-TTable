#pragma once
#include "TTable.h"

class THashTable : public TTable {
protected:
	virtual unsigned int HashFunc(const TKey key);//вычисление номера записи
public:
	THashTable() :TTable(){}
};