#include "Mtrx.h"
#include <iostream>
#include <iomanip>
using namespace std;

typedef double* DBLPTR;
Mtrx::Mtrx(int num_row, int num_col)
{
	int i, j;
	//cout <<"Mtrx constructor (int size: "
	// << size << ")₩n";
	n_row = num_row;
	n_col = num_col;
	dM = new DBLPTR[n_row]; //포인터 배열 생성, row 개수만큼 더블 포인터를 가지는 1차원 포인터를 생성

	for (i = 0; i < n_row; i++)
	{
		dM[i] = new double[n_col]; //
	}
	for (i = 0; i < n_row; i++) {
		for (j = 0; j < n_col; j++) {
			dM[i][j] = 0.0;
		}
	}
	// cout <<"End of Mtrx constructor...₩n";
}
Mtrx::Mtrx(double* dA, int num_data, int num_row, int num_col)
{
	n_row = num_row;
	n_col = num_col;

	dM = new double* [n_row];
	for (int i = 0; i < n_row; i++)
		for (int j = 0; j < n_col; j++)
			dM[i] = new double[n_col];

	for (int i = 0; i < n_row; i++)
		for (int j = 0; j < n_col; j++)
			dM[i][j] = dA[j];
}
Mtrx::~Mtrx()
{
	// cout << "destructor of Mtrx ("
	// << name << ")" << endl;
	/*for (int i=0; i<n_row; i++)
		delete [] dM[i];
	delete [] dM;*/
}
Mtrx::Mtrx(istream& fin)
{
	// DBLPTR *dM; /* defined in class, as private data member
	int i, j, size_row, size_col, num_data, cnt;
	double d;
	//cout <<"Mtrx constructor (double **dA, int size: " << size << ")₩n";
	fin >> size_row >> size_col; //파일로부터 행과 열의 값을 가져온다
	n_row = size_row;
	n_col = size_col;
	dM = new DBLPTR[n_row];
	for (i = 0; i < n_row; i++)
	{
		dM[i] = new double[n_col];
	}
	for (i = 0; i < n_row; i++) {
		for (j = 0; j < n_col; j++) {
			if (fin.eof())
				dM[i][j] = 0.0;
			else
			{
				fin >> d;
				dM[i][j] = d;
			}
		}
	}
	//cout <<"End of Mtrx constructor... ₩n";
}
#define SETW 6 //6칸
void Mtrx::fprintMtrx(ostream& fout)
{
	unsigned char a6 = 0xA6, a1 = 0xA1, a2 = 0xA2;
	unsigned char a3 = 0xA3, a4 = 0xA4, a5 = 0xA5;
	for (int i = 0; i < n_row; i++) {
		for (int j = 0; j < n_col; j++)
		{
			fout.setf(ios::fixed);
			fout.precision(1); //소수점 한자리
			if ((i == 0) && (j == 0))
				fout << a6 << a3 << setw(SETW) << dM[i][j];
			else if ((i == 0) && (j == (n_col - 1)))
				fout << setw(SETW) << dM[i][j] << a6 << a4;
			else if ((i > 0) && (i < (n_row - 1)) && (j == 0))
				fout << a6 << a2 << setw(SETW) << dM[i][j];
			else if ((i > 0) && (i < (n_row - 1)) && (j == (n_col - 1)))
				fout << setw(SETW) << dM[i][j] << a6 << a2;
			else if ((i == (n_row - 1)) && (j == 0))
				fout << a6 << a6 << setw(SETW) << dM[i][j];
			else if ((i == (n_row - 1)) && (j == (n_col - 1)))
				fout << setw(SETW) << dM[i][j] << a6 << a5;
			else
				fout << setw(SETW) << dM[i][j];
		}
		fout << endl;
	}
	fout << endl;
}
Mtrx Mtrx::add(const Mtrx& mA)
{
	int i, j;
	Mtrx mR(n_row, n_col);
	mR.setName("R"); //
	for (i = 0; i < n_row; i++) {
		for (j = 0; j < n_col; j++) {
			mR.dM[i][j] = dM[i][j] + mA.dM[i][j];
		}
	}
	return mR;
}
Mtrx Mtrx::sub(const Mtrx& mA)
{
	int i, j;
	Mtrx mR(n_row, n_col);
	mR.setName("R");
	for (i = 0; i < n_row; i++) {
		for (j = 0; j < n_col; j++) {
			mR.dM[i][j] = dM[i][j] - mA.dM[i][j];
		}
	}
	return mR;
}
Mtrx Mtrx::multiply(const Mtrx& mA)
{
	int i, j, k;
	Mtrx mR(n_row, mA.n_col);
	mR.setName("R");
	for (i = 0; i < n_row; i++) {
		for (j = 0; j < mA.n_col; j++) {
			mR.dM[i][j] = 0.0;
			for (k = 0; k < n_col; k++) {
				mR.dM[i][j] += dM[i][k] * mA.dM[k][j];
			}
		}
	}
	return mR;
}
Mtrx Mtrx::transpose()
{
	int a, b, i, j;
	a = getN_row();
	b = getN_col();
	Mtrx mR(b,a);
	for (i = 0; i < b; i++) 
	{
		for (j = 0; j < a; j++)
		{
			//mR.dM[i][j] = 0.0;
			mR.dM[i][j] = dM[j][i];
		}
	}	
	return mR;
}