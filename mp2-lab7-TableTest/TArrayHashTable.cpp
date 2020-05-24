#include "TArrayHashTable.h"

TArrayHashTable::TArrayHashTable(int size, int Step) {
	TabSize = size; HashStep = Step;
	pRec = new TTabRecord[TabSize];
	Empty = TTabRecord(-1);
	Mark = TTabRecord(-2);
	for (int i = 0; i < TabSize; i++) {
		pRec[i] = Empty;
	}
}

TArrayHashTable::~TArrayHashTable() {
	delete[]pRec;
}


//найти запись
bool TArrayHashTable::FindRecord(TKey k) {
	bool res = false;
	FreePos = -1;
	CurrPos = HashFunc(k) % TabSize;
	for (int i = 0; i < TabSize; i++) {
		Efficiency++;
		if (pRec[CurrPos] == Empty)			//свободная запись-нет записи-конец поиска
			break;
		else if (pRec[CurrPos] == Mark) {	//удаленная запись-запоминаем 1ую-продолжаем поиск
			if (FreePos == -1)
				FreePos = CurrPos;
		}
		else if(pRec[CurrPos].Key==k){		//нашли ключ
			res = true;
			break;
		}
		CurrPos = GetNextPos(CurrPos);		//хэширование
	}
	return res;
}			

//добавить запись
int TArrayHashTable::InsRecord(TKey k, TValue val) {
	if (IsFull()) {
		return TabFull;
	}
	else {
		bool res = FindRecord(k);
		if (res == true) {
			return TabRecDouble;
		}
		else {
			if (FreePos = !- 1)
				CurrPos = FreePos;//используем 1ую пустую строку
			pRec[CurrPos] = TTabRecord(k, val);
			DataCount++;
			return TabOK;
		}
	}
}

//удалить запись
int TArrayHashTable::DelRecord(TKey k) {
	if (IsEmpty()) {
		return TabEmpty;
	}
	else {
		bool res = FindRecord(k);
		if (res == false) {
			return TabNoRec;
		}
		else {
			pRec[CurrPos] = Mark;
			DataCount--;
			return TabOK;
		}
	}
}


//Навигация
int TArrayHashTable::Reset() {
	CurrPos = 0;
	while (CurrPos < TabSize){	//поиск 1ой занятной строки
		if ((pRec[CurrPos] != Empty) && (pRec[CurrPos] != Mark))//не удал-ая и не пуста-нашли
			break;
		else CurrPos++;
	}
	return IsTabEnded();
}

int TArrayHashTable::IsTabEnded() const {
	return CurrPos >= TabSize;
}

int TArrayHashTable::GoNext() {
	CurrPos++;
	while (CurrPos < TabSize) {	//поиск след. занятной строки
		if ((pRec[CurrPos] != Empty) && (pRec[CurrPos] != Mark))//не удал-ая и не пуста-нашли
			break;
		else CurrPos++;
	}
	return IsTabEnded();
}


//Доступ
TKey TArrayHashTable::GetKey()const { 
	if ((DataCount == 0) || (CurrPos >= TabSize))
		throw NULL;
	return pRec[CurrPos].Key; 
}

TValue TArrayHashTable::GetValue()const { 
	if ((DataCount == 0) || (CurrPos >= TabSize))
		throw NULL;
	return pRec[CurrPos].Value; 
}