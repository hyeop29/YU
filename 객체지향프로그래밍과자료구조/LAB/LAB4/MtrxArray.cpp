#include "MtrxArray.h"
#include "Class_Mtrx.h"
#define SETW 8
MtrxArray::MtrxArray(int arraySize) // constructor
{
	mtrxArrySize = arraySize;
	pMtrx = new Mtrx[arraySize];
}
MtrxArray::~MtrxArray()
{
	//cout << "MtrxArray :: destructor" << endl;
	if (pMtrx != NULL) {
		delete[] pMtrx;
	}
}
void subError()
{
	cout << "ERROR: Subscript out of range.₩n";
		exit(0);
}
bool MtrxArray::isValidIndex(int index)
{
	if (index < 0 || index >= mtrxArrySize)
		return false;
	else
		return true;
}
Mtrx& MtrxArray::operator [](int sub)
{
	if (isValidIndex(sub)) //범위 안이면
		return pMtrx[sub];
	else
		subError();
}
void MtrxArray::sort()
{
	int i, j, min_st;
	double min_value;
	Mtrx min_Mtrx, tmp;
	for ( i = 0; i < mtrxArrySize; i++)
	{
		min_st = i;
		min_Mtrx = pMtrx[min_st];
		cout << "a";
		min_value = min_Mtrx.dM[min_Mtrx.n_row-1][min_Mtrx.n_col-1];
		cout << "a";
		for (j = i + 1; j < mtrxArrySize; j++)
		{
			if (pMtrx[j].dM[pMtrx[j].n_row-1][pMtrx[j].n_col-1] < min_value)
			{
				min_st = j;
				min_Mtrx = pMtrx[j];
			}
		}
		if (min_st != i)
		{
			tmp = pMtrx[i];
			pMtrx[i] = pMtrx[min_st];
			pMtrx[min_st] = tmp;
		}
	}
}
void MtrxArray::print(ostream& fout)
{
	unsigned char a6 = 0xA6, a1 = 0xA1, a2 = 0xA2;
	unsigned char a3 = 0xA3, a4 = 0xA4, a5 = 0xA5;

	int k;
	for (k = 0; k < getSize(); k++)
	{
		/*unsigned char a6 = 0xA6, a1 = 0xA1, a2 = 0xA2;
		unsigned char a3 = 0xA3, a4 = 0xA4, a5 = 0xA5;*/
		fout << pMtrx[k].name << endl;
		
		for (int i = 0; i < pMtrx[k].n_row; i++) {
			for (int j = 0; j < pMtrx[k].n_col; j++)
			{
				
				fout.setf(ios::fixed);
				fout.precision(2);
				if ((i == 0) && (j == 0))
					fout << a6 << a3 << setw(SETW) << pMtrx[k].dM[i][j];
				else if ((i == 0) && (j == (pMtrx[k].n_col - 1)))
					fout << setw(SETW) << pMtrx[k].dM[i][j] << a6 << a4;
				else if ((i > 0) && (i < (pMtrx[k].n_row - 1)) && (j == 0))
					fout << a6 << a2 << setw(SETW) << pMtrx[k].dM[i][j];
				else if ((i > 0) && (i < (pMtrx[k].n_row - 1)) && (j == (pMtrx[k].n_col - 1)))
					fout << setw(SETW) << pMtrx[k].dM[i][j] << a6 << a2;
				else if ((i == (pMtrx[k].n_row - 1)) && (j == 0))
					fout << a6 << a6 << setw(SETW) << pMtrx[k].dM[i][j];
				else if ((i == (pMtrx[k].n_row - 1)) && (j == (pMtrx[k].n_col - 1)))
					fout << setw(SETW) << pMtrx[k].dM[i][j] << a6 << a5;
				else
					fout << setw(SETW) << pMtrx[k].dM[i][j];
			}
			fout << endl;
		}
		fout << endl;
	}
}