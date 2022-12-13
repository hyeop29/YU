#ifndef CLASS_MTRX_H
#define CLASS_MTRX_H
#define MAX_SIZE 100
#include <string>
#include <iostream>
#include <iomanip>
using namespace std; 

typedef struct Statistic //학생들의 정보를 표현하기 위한 구조체
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
    Mtrx(string nm, int n_row, int n_col);  //생성자
	Mtrx(string nm, double *pA, int num_row, int num_col); //데이터가 전달되는 생성자
	Mtrx(istream& fin); //파일로 부터 입력받는 부분
	
	~Mtrx(); 
	void init(int n_row, int n_col); //초기화
	void set_name(string nm) { name = nm; }  //이름 설정
	string get_name() const { return name; } //이름 읽어내기
	int get_n_row() const { return n_row; } //행크기 읽어내기
	int get_n_col() const { return n_col; } //열크기 읽어내기
	Mtrx getstatics(ostream& fout);
	const Mtrx operator+(const Mtrx&); //행렬 덧셈
	const Mtrx operator-(const Mtrx&); //뺄셈
	const Mtrx operator*(const Mtrx&); //곱셈
	const Mtrx operator~(); // transpose() 전치행렬
	const Mtrx& operator=(const Mtrx&); 
	bool operator==(const Mtrx&); //행렬이 같은지 비교
	bool operator!=(const Mtrx&); //행렬이 틀린지 비교
private: 
	string name;  //이름
	int n_row;  //행의 개수
	int n_col;  //열의 개수
	double **dM; //행열의 데이터 원소를 저장할 수 있도록 2중 포인터
};
#endif
