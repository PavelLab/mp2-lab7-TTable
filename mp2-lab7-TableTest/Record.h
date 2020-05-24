#pragma once
#include <iostream>
#include <string>

using namespace std;

typedef int TKey;
typedef string TValue;

struct TTabRecord
{	
	TKey Key;		//ключ записи
	TValue Value;	//значение
	
	TTabRecord() {};
	TTabRecord(TKey k) { Key = k; }
	TTabRecord(TKey k, TValue Val) {Key = k; Value = Val;}
	virtual int operator==(const TTabRecord &tr) { return Key == tr.Key; }
	virtual int operator!=(const TTabRecord &tr) { return Key != tr.Key; }
	virtual int operator>(const TTabRecord &tr) { return Key > tr.Key; }
	virtual int operator<(const TTabRecord &tr) { return Key < tr.Key; }

	friend ostream& operator<<(ostream &os, const TTabRecord &tr) {
		return os << tr.Key << " " << tr.Key;
	}
};