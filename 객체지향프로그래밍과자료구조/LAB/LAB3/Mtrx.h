#ifndef MTRX_H
#define MTRX_H
#include <iostream>
#include <fstream>
using namespace std;
#define MAX_SIZE 100

class Mtrx {
public:
	Mtrx(int num_row, int num_col); //생성자, 크기만 지정
	Mtrx(double dA[], int num_data, int num_row, int num_col); //생성자, 원소들의 초기값을 배열로 전달
	Mtrx(istream& fin); //생성자 file로 부터 읽어서 초기화
	~Mtrx(); // destructor
	int getN_row() { return n_row; }
	int getN_col() { return n_col; }
	void fprintMtrx(ostream& fout); //행렬을 형식에 맞게 출력하는 함수
	void setName(string nm) { name = nm; };
	string getName() { return name; };
	Mtrx add(const Mtrx&); // 행렬의 합을 계산 하는 함수
	Mtrx sub(const Mtrx&); // 행렬의 차를 계산 하는 함수
	Mtrx multiply(const Mtrx&); //행렬의 곱을 계산하는 함수
	Mtrx transpose();
private:
	string name;
	int n_row; //행의 개수
	int n_col; //열의 개수
	double** dM; //행열의 데이터 원소를 저장할 수 있도록 2중 포인터
};
#endif