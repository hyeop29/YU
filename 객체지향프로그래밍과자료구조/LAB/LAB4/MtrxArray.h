/*행렬 자체를 배열로 만들어쓰기위한 부분 */
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
	int mtrxArrySize;//원소 개수
	bool isValidIndex(int index);
};
#endif
