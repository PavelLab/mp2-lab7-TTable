#pragma once
#include "Record.h"

#define TabOK 0			//ошибок нет
#define TabEmpty -101	//таблица пуста
#define TabFull  -102	//таблица полна
#define TabNoRec -103	//нет записи
#define TabNoMem -104	//нет памяти
#define TabRecDouble -105	//запись уже есть

#define TabMaxSize 30

class TTable {
protected:
	int DataCount;		//количество записей в таблице
	int Efficiency;		//эффективность выполнения операции
public:
	TTable() { DataCount = 0; Efficiency = 0; }
	virtual ~TTable() {};

	int GetDataCount() const { return DataCount; }		
	int GetEfficiency() const{ return Efficiency; }
	void ClearEfficiency() { Efficiency = 0; }
	bool IsEmpty() const { return DataCount == 0; }	//проверка на пустоту
	virtual bool IsFull()const = 0;					//проверка на заполненость

	virtual bool FindRecord(TKey k) = 0;			//найти запись
	virtual int InsRecord(TKey k,TValue val) = 0;	//добавить запись
	virtual int DelRecord(TKey k) = 0;				//удалить запись

	//Навигация
	virtual int Reset() = 0;
	virtual int IsTabEnded() const= 0;
	virtual int GoNext() = 0;

	//Доступ
	virtual TKey GetKey()const = 0;
	virtual TValue GetValue()const = 0;

	//Печать
	friend ostream& operator<<(ostream &os, TTable &tab) {
		os << "Table printing" << endl;
		for (tab.Reset(); !tab.IsTabEnded(); tab.GoNext()) {
			os << "Key: " << tab.GetKey() << " Value: " << tab.GetValue() << endl;
		}
		return os;
	}
};