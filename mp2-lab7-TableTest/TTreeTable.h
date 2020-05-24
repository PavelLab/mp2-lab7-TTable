#pragma once
#include "TTreeNode.h"
#include"TTable.h"
#include <fstream>
#include <stack>

class TTreeTable:public TTable {
	protected:
		TTreeNode *pRoot;	//����. �� ������ ������
		TTreeNode *pCurr;	//����. �� �����. �������
		TTreeNode *pPrev;	//����. �� ������. �������
		int CurrPos;		//����� �����. �������
		stack<TTreeNode*> st;//���� ��� ���������
		int level;			//������� ��� ������

		void DeleteTreeTab(TTreeNode *pRoot);//��������
		void PrintTreeTable(ostream &os, TTreeNode *pNode);
public:
	TTreeTable() { CurrPos = 0; pRoot = pCurr = NULL; }
	~TTreeTable() { DeleteTreeTab(pRoot);}

	virtual bool IsFull()const;

	virtual bool FindRecord(TKey k);			//����� ������
	virtual int InsRecord(TKey k, TValue val);	//�������� ������
	virtual int DelRecord(TKey k);				//������� ������

	//������
	virtual TKey GetKey()const;
	virtual TValue GetValue()const;

	//���������
	virtual int Reset();				//���������� �� ������ ������
	virtual int IsTabEnded() const;		//�������� �� ���������� �������
	virtual int GoNext();				//������� � ���� ������
	
	//������
	void PrintTable(string str);
};