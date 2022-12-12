#ifndef MTRX_H
#define MTRX_H
#include <iostream>
#include <fstream>
using namespace std;
#define MAX_SIZE 100

class Mtrx {
public:
	Mtrx(int num_row, int num_col); //������, ũ�⸸ ����
	Mtrx(double dA[], int num_data, int num_row, int num_col); //������, ���ҵ��� �ʱⰪ�� �迭�� ����
	Mtrx(istream& fin); //������ file�� ���� �о �ʱ�ȭ
	~Mtrx(); // destructor
	int getN_row() { return n_row; }
	int getN_col() { return n_col; }
	void fprintMtrx(ostream& fout); //����� ���Ŀ� �°� ����ϴ� �Լ�
	void setName(string nm) { name = nm; };
	string getName() { return name; };
	Mtrx add(const Mtrx&); // ����� ���� ��� �ϴ� �Լ�
	Mtrx sub(const Mtrx&); // ����� ���� ��� �ϴ� �Լ�
	Mtrx multiply(const Mtrx&); //����� ���� ����ϴ� �Լ�
	Mtrx transpose();
private:
	string name;
	int n_row; //���� ����
	int n_col; //���� ����
	double** dM; //�࿭�� ������ ���Ҹ� ������ �� �ֵ��� 2�� ������
};
#endif