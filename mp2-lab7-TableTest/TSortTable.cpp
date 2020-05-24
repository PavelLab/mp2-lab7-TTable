#include "TSortTable.h"

//преоб. типа
TSortTable::TSortTable(const TScanTable &tab) {
	*this = tab;
}

//присв. упоряд-ой таблице неупоряд-ой
TSortTable & TSortTable::operator =(const TScanTable &tab) {

	if (pRec != NULL) {
		delete[] pRec;
		pRec = NULL;
	}
	TabSize = tab.GetTabSize();
	DataCount = tab.GetDataCount();
	pRec = new TTabRecord[TabSize];
	for (int i = 0; i < DataCount; i++) {
		pRec[i] = tab.Get_pRec(i);
	}
	SortData();
	CurrPos = 0;
	return *this;
}	

//выбор метода сортировки
void TSortTable::SortData() {
	switch (SortMethod)
	{
	case SELECT_SORT:
		SelectSort();
		break;
	case QUICK_SORT:
		QuickSort();
		break;
	default:
		break;
	}
}

//сортировка выбором
void TSortTable::SelectSort() {
	int index = 0;
	for (int i = 0; i < DataCount; i++) {
		index = i;//номер текущего мин элемента
		for (int j = i + 1; j < DataCount; j++) {
			Efficiency++;
			if (pRec[j] < pRec[index]) {
				index = j;
			}
		}
		if (i != index) {
			Efficiency++;
			//обмен записей i и index
			TTabRecord tmp = pRec[i];
			pRec[i] = pRec[index];
			pRec[index] = tmp;
		}
	}
}

//быстрая сортировка - вызов рекурсивной функции
void TSortTable::QuickSort() {
	QuickSorter(0, DataCount - 1);
}	

void TSortTable::QuickSorter(int first,int last) {
	int i, j;TTabRecord x;
	i = first; j = last;
	x = pRec[(first + last) / 2];
	while (i < j) {
		Efficiency += 2;
		while (pRec[i] < x) i++;
		while (pRec[j] > x) j--;
		if (i <= j) {
			Efficiency++;
			TTabRecord tmp = pRec[i];
			pRec[i] = pRec[j];
			pRec[j] = tmp;
			i++; j--;
		}
	}
	if (first < j) QuickSorter(first, j);
	if (i < last) QuickSorter(i, last);
}

//найти запись
bool TSortTable::FindRecord(TKey k) {
//двоичный поиск
	int i, i1 = 0, i2 = DataCount - 1;//границы поиска
	while (i1 <= i2) {
		Efficiency++;
		i = (i1 + i2) / 2;
		if (pRec[i].Key == k) {
			i1 = i + 1;
			i2 = i;
			break;
		}
		if (pRec[i].Key > k) i2 = i - 1;
		else i1 = i + 1;
	}
	if ((i2 < 0) || (pRec[i2].Key < k)) i2++;
	CurrPos = i2;
	if ((i2 < DataCount) && (pRec[i].Key == k)) {
		return true;
	}
	return false;
}

//добавить запись
int TSortTable::InsRecord(TKey k, TValue val) {
	if (IsFull()) {
		return TabFull;
	}
	else {
		bool res = FindRecord(k);
		if (res == true) {
			return TabRecDouble;
		}
		else {
			for (int i = DataCount; i > CurrPos; i--) {
				pRec[i] = pRec[i - 1];//перепаковка
				Efficiency++;
			}
			pRec[CurrPos] = TTabRecord(k, val);
			DataCount++;
			return TabOK;
		}
	}
}	

//удалить запись
int TSortTable::DelRecord(TKey k) {
	if (IsEmpty()) {
		return TabEmpty;
	}
	else {
		bool res = FindRecord(k);
		if (res == false) {
			return TabNoRec;
		}
		else {
			for (int i = CurrPos; i <DataCount-1; i++) {
				pRec[i] = pRec[i + 1];//перепаковка
				Efficiency++;
			}
			DataCount--;
			return TabOK;
		}
	}
}