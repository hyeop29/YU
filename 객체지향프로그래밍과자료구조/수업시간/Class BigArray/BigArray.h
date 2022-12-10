/* BigArray.h (1) */
#ifndef BIG_ARRAY_H
#define BIG_ARRAY_H
#include <iostream>
#include <fstream>
using namespace std;
typedef struct
{
	int min;
	int max;
	double avg; // average
	double var; // variance
	double std_dev; // standard deviation
} ArrayStatistics; //통계 분석

class BigArray
{
public:
	BigArray(int n); // constructor
	~BigArray(); // destructor
	void genBigRandArray(int base_offset);
	int size() { return num_elements; }
	void suffle();
	void selection_sort();
	void quick_sort();
	void getStatistics(ArrayStatistics&);
	void fprintStatistics(ostream& fout);
	void fprintBigArray(ostream& fout, int elements_per_line);
	void fprintSample(ostream& fout, int elements_per_line, int num_sample_lines);
private:
	int* big_array; //큰 배열을 동적으로 생성해서 사용할 수 있는 포인터
	int num_elements; //개수
};
#endif
