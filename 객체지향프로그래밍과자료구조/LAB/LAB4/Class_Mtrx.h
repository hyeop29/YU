#ifndef CLASS_MTRX_H
#define CLASS_MTRX_H
#define MAX_SIZE 100
#include <string>
#include <iostream>
#include <iomanip>
using namespace std; 

typedef struct Statistic //�л����� ������ ǥ���ϱ� ���� ����ü
{
	double min;
	double max;
	double avg;
	double var;
	double std_dev;
} Statistics;

class MtrxArray; 

class Mtrx { 
	friend ostream & operator<< (ostream &, const Mtrx &); 
	friend istream& operator>> (istream&, Mtrx&); 
	friend class MtrxArray; 

public: 
	Mtrx(); // default constructor 
    Mtrx(string nm, int n_row, int n_col);  //������
	Mtrx(string nm, double *pA, int num_row, int num_col); //�����Ͱ� ���޵Ǵ� ������
	Mtrx(istream& fin); //���Ϸ� ���� �Է¹޴� �κ�
	
	~Mtrx(); 
	void init(int n_row, int n_col); //�ʱ�ȭ
	void set_name(string nm) { name = nm; }  //�̸� ����
	string get_name() const { return name; } //�̸� �о��
	int get_n_row() const { return n_row; } //��ũ�� �о��
	int get_n_col() const { return n_col; } //��ũ�� �о��
	Mtrx getstatics(ostream& fout);
	const Mtrx operator+(const Mtrx&); //��� ����
	const Mtrx operator-(const Mtrx&); //����
	const Mtrx operator*(const Mtrx&); //����
	const Mtrx operator~(); // transpose() ��ġ���
	const Mtrx& operator=(const Mtrx&); 
	bool operator==(const Mtrx&); //����� ������ ��
	bool operator!=(const Mtrx&); //����� Ʋ���� ��
private: 
	string name;  //�̸�
	int n_row;  //���� ����
	int n_col;  //���� ����
	double **dM; //�࿭�� ������ ���Ҹ� ������ �� �ֵ��� 2�� ������
};
#endif
