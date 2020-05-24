#pragma once
#include "TTable.h"

class TArrayTable : public TTable {
protected:
	TTabRecord *pRec;	//память для записи
	int TabSize;		//размер таблицы
	int CurrPos;		//номер текущей записи(от 0)

public:
	TArrayTable(int size = TabMaxSize) {
		pRec = new TTabRecord[size];
		TabSize = size;
		DataCount = CurrPos = 0;
	}
	~TArrayTable() {
		delete[]pRec;
	}


	//информационные методы
	virtual bool IsFull() const { return DataCount >= TabSize; }
	int GetTabSize()const { return TabSize; }

	//доступ
	virtual TKey GetKey() const;	//получить ключ
	virtual TValue GetValue() const; //получить значение
	TTabRecord Get_pRec(int i) const { return pRec[i]; }

	//навигация
	virtual int Reset();				//установить на первую запись
	virtual int IsTabEnded() const;		//проверка на завершение таблицы
	virtual int GoNext();				//перейти к след записи
	virtual int SetCurrentPos(int pos);	//установить тек. позицию
	int GetCurrentPos() const { return CurrPos; }

};