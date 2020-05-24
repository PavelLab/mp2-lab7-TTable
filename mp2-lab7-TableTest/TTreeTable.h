#pragma once
#include "TTreeNode.h"
#include"TTable.h"
#include <fstream>
#include <stack>

class TTreeTable:public TTable {
	protected:
		TTreeNode *pRoot;	//указ. на корень дерева
		TTreeNode *pCurr;	//указ. на текущ. вершину
		TTreeNode *pPrev;	//указ. на предыд. вершину
		int CurrPos;		//номер текущ. вершины
		stack<TTreeNode*> st;//стэк для итератора
		int level;			//уровень для печати

		void DeleteTreeTab(TTreeNode *pRoot);//удаление
		void PrintTreeTable(ostream &os, TTreeNode *pNode);
public:
	TTreeTable() { CurrPos = 0; pRoot = pCurr = NULL; }
	~TTreeTable() { DeleteTreeTab(pRoot);}

	virtual bool IsFull()const;

	virtual bool FindRecord(TKey k);			//найти запись
	virtual int InsRecord(TKey k, TValue val);	//добавить запись
	virtual int DelRecord(TKey k);				//удалить запись

	//Доступ
	virtual TKey GetKey()const;
	virtual TValue GetValue()const;

	//навигация
	virtual int Reset();				//установить на первую запись
	virtual int IsTabEnded() const;		//проверка на завершение таблицы
	virtual int GoNext();				//перейти к след записи
	
	//печать
	void PrintTable(string str);
};