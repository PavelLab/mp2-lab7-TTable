#include "TTreeTable.h"

//��������
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


//����� ������
bool TTreeTable::FindRecord(TKey k) {
	pPrev = NULL;
	pCurr = pRoot;
	while (pCurr!=NULL){//�� ������ �� �����
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

//�������� ������
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

//������� ������
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
				//� �������-�� ���� ������� �����
				if (pPrev == NULL)		
					pRoot = pNode->pLeft;//�������� �����
				else {
					if (pPrev->pRight == pNode)			//�������-�� ������
						pPrev->pRight = pNode->pLeft;
					else pPrev->pLeft = pNode->pLeft;
				}
				Efficiency++;
			}
			else if (pNode->pLeft == NULL) {
				//� �������-�� ���� ������� ������
				if (pPrev == NULL)
					pRoot = pNode->pRight;//�������� �����
				else {
					if (pPrev->pRight == pNode)			//�������-�� ������
						pPrev->pRight = pNode->pRight;
					else pPrev->pLeft = pNode->pRight;	//�����
				}
				Efficiency++;
			}
			else {
				//� �������-�� ��� �������
				TTreeNode *pN = pNode->pLeft;
				pPrev = pNode;
				while (pN->pRight != NULL) {
					//����� �������� ������ � ������ ���������
					pPrev = pN;
					pN = pN->pRight;
					Efficiency++;
				}
				//����������� pN � �������-��
				pNode->Value = pN->Value;
				pNode->Key = pN->Key;
				if (pPrev->pRight == pN)
					pPrev->pRight = pN->pLeft;
				else pPrev->pLeft = pN->pLeft;//����� � ������ ��������� ���� �����
				pNode = pN;
				Efficiency++;
			}
			delete pNode;
			DataCount--;
			return TabOK;
		}
	}
}


//������
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


//���������
int TTreeTable::Reset() {
	TTreeNode *pNode = pCurr = pRoot;
	while (!st.empty()) st.pop();	//������� �����
	CurrPos = 0;
	while (pNode != NULL) {			//������� � ������ ����� �������
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
		TTreeNode *pNode = pCurr = pCurr->pRight;//������� � ������� �������
		st.pop();
		while (pNode!=NULL){
			//������� � ������� ����� �������
			st.push(pNode);
			pCurr = pNode;
			pNode = pNode->pLeft;
		}
		//���� ��� ������� �������, ��. ������� �����
		if ((pCurr == NULL) && !st.empty()) {
			pCurr = st.top();
		}
		CurrPos++;
	}
	return IsTabEnded();
}


//������
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