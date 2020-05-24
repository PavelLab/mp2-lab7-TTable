#include "TTreeTable.h"

//удаление
void TTreeTable::DeleteTreeTab(TTreeNode *pNode) {
	if (pNode != NULL) {
		DeleteTreeTab(pNode->pLeft);
		DeleteTreeTab(pNode->pRight);
		delete pNode;
	}
}

bool TTreeTable::IsFull()const {
	TTreeNode *pNode = new TTreeNode();
	bool tmp = pNode == NULL;
	delete pNode;
	return tmp;
}


//найти запись
bool TTreeTable::FindRecord(TKey k) {
	pPrev = NULL;
	pCurr = pRoot;
	while (pCurr!=NULL){//не дойдем до листа
		Efficiency++;
		if (pCurr->Key == k) break;
		pPrev = pCurr;
		if (pCurr->Key < k)pCurr = pCurr->pRight;
		else pCurr = pCurr->pLeft;
	}
	if (pCurr != NULL) {
		return true;
	}
	else {
		pCurr = pPrev;
		return false;
	}
}	

//добавить запись
int TTreeTable::InsRecord(TKey k, TValue val) {
	if (IsFull()) {
		return TabFull;
	}
	else {
		bool res = FindRecord(k);
		if (res == true) {
			return TabRecDouble;
		}
		else {
			TTreeNode *tmp = new TTreeNode(k, val);
			if (pRoot == NULL)
				pRoot = tmp;
			else {
				if (k < pCurr->Key)
					pCurr->pLeft = tmp;
				else
					pCurr->pRight = tmp;
			}
			Efficiency++;
			DataCount++;
			return TabOK;
		}
	}
}

//удалить запись
int TTreeTable::DelRecord(TKey k) {
	if (IsEmpty()) {
		return TabEmpty;
	}
	else {
		bool res = FindRecord(k);
		if (res == false) {
			return TabNoRec;
		}
		else {
			TTreeNode *pNode = pCurr;
			if (pNode->pRight == NULL) {
				//у удал€ем-ой один потомок слева
				if (pPrev == NULL)		
					pRoot = pNode->pLeft;//удаление корн€
				else {
					if (pPrev->pRight == pNode)			//удал€ем-а€ справа
						pPrev->pRight = pNode->pLeft;
					else pPrev->pLeft = pNode->pLeft;
				}
				Efficiency++;
			}
			else if (pNode->pLeft == NULL) {
				//у удал€ем-ой один потомок справа
				if (pPrev == NULL)
					pRoot = pNode->pRight;//удаление корн€
				else {
					if (pPrev->pRight == pNode)			//удал€ем-а€ справа
						pPrev->pRight = pNode->pRight;
					else pPrev->pLeft = pNode->pRight;	//слева
				}
				Efficiency++;
			}
			else {
				//у удал€ем-ой два потомка
				TTreeNode *pN = pNode->pLeft;
				pPrev = pNode;
				while (pN->pRight != NULL) {
					//поиск крайнего справа у левого поддерева
					pPrev = pN;
					pN = pN->pRight;
					Efficiency++;
				}
				//копирование pN в удал€ем-ый
				pNode->Value = pN->Value;
				pNode->Key = pN->Key;
				if (pPrev->pRight == pN)
					pPrev->pRight = pN->pLeft;
				else pPrev->pLeft = pN->pLeft;//когда у левого поддерева одно звено
				pNode = pN;
				Efficiency++;
			}
			delete pNode;
			DataCount--;
			return TabOK;
		}
	}
}


//ƒоступ
TKey TTreeTable::GetKey()const {
	if (pCurr == NULL)
		throw NULL;
	return pCurr->Key;
}

TValue TTreeTable::GetValue()const {
	if (pCurr == NULL)
		throw NULL;
	return pCurr->Value;
}


//Ќавигаци€
int TTreeTable::Reset() {
	TTreeNode *pNode = pCurr = pRoot;
	while (!st.empty()) st.pop();	//очистка стэка
	CurrPos = 0;
	while (pNode != NULL) {			//переход к райней левой вершине
		st.push(pNode);
		pCurr = pNode;
		pNode = pNode->pLeft;
	}
	return IsTabEnded();
}

int TTreeTable::IsTabEnded() const {
	return CurrPos >= DataCount;
}

int TTreeTable::GoNext() {
	if (!IsTabEnded() && pCurr != NULL) {
		TTreeNode *pNode = pCurr = pCurr->pRight;//переход к правому потомку
		st.pop();
		while (pNode!=NULL){
			//переход к крайней левой вершине
			st.push(pNode);
			pCurr = pNode;
			pNode = pNode->pLeft;
		}
		//если нет правого потомка, см. вершину стэка
		if ((pCurr == NULL) && !st.empty()) {
			pCurr = st.top();
		}
		CurrPos++;
	}
	return IsTabEnded();
}


//печать
void TTreeTable::PrintTable(string str) {
	ofstream os(str);
	os << "Table printing" << endl;
	level = 0;
	PrintTreeTable(os, pRoot);
}

void TTreeTable::PrintTreeTable(ostream &os, TTreeNode* pNode) {
	if (pNode != NULL) {
		for (int i = 0; i < level; i++)
			os << " ";
		os << pNode->Key << endl;
		level++;
		PrintTreeTable(os, pNode->pRight);
		PrintTreeTable(os, pNode->pLeft);
		level--;
	}

}