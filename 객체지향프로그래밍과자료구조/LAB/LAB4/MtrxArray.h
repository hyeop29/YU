/*��� ��ü�� �迭�� ���������� �κ� */
#ifndef MTRX_ARRAY_H
#define MTRX_ARRAY_H
#include <iostream>
#include "Class_Mtrx.h"
using namespace std;
class Mtrx;
class MtrxArray
{
public:
	MtrxArray(int array_size); // constructor
	~MtrxArray(); // destructor
	Mtrx& operator[](int);
	int getSize() {return mtrxArrySize;}
	//Mtrx* get_pMtrx() { return pMtrx; }
	void print(ostream& fout);
	void sort();
private:
	Mtrx* pMtrx; //
	int mtrxArrySize;//���� ����
	bool isValidIndex(int index);
};
#endif
