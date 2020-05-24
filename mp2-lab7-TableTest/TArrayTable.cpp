#include "TArrayTable.h"

int TArrayTable::Reset() {
	//установить на первую запись
	CurrPos = 0;
	return IsTabEnded();
}	

int TArrayTable::IsTabEnded() const {
	//проверка на завершение таблицы
	return CurrPos >= DataCount;
}

int TArrayTable::GoNext() {
	//перейти к след записи
	if (!IsTabEnded()) CurrPos++;
	return IsTabEnded();
}

int TArrayTable::SetCurrentPos(int pos) {
	//установить тек. позицию
	CurrPos = ((pos > -1) && (pos < DataCount)) ? pos : 0;
	return IsTabEnded();
}	

//доступ
TKey TArrayTable::GetKey() const { 
	if ((DataCount == 0) || (CurrPos >= DataCount))
		throw NULL;
	return pRec[CurrPos].Key; 
}		//получить ключ

TValue TArrayTable::GetValue() const {
	if ((DataCount == 0) || (CurrPos >= DataCount))
		throw NULL;
	return pRec[CurrPos].Value; 
} //получить значение

