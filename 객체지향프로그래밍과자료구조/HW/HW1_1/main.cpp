/** Homework (1)
*
* - File input, output and getStatistics
* - Programmed by Chang-Hyeop LEE
* - Last update: 2020-09-05
*/
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;
#define INPUT_FILE_NAME "Input_data.txt"
#define OUTPUT_FILE_NAME "output.txt"

int fileInputData(ifstream& fin, int* data_array, int max_num_data); //10개의 정수 데이터를 입력 받는 함수
void getStatistics_fileOut(int* data_array, int num_data, ofstream& fout); //입력된 데이터의 통계 분석 함수

void main()
{
	ifstream fin;
	ofstream fout;
	int data_array[10] = {0};
	int max_num_data = 0;
	fin.open(INPUT_FILE_NAME);
	if (fin.fail()) //파일 열기 실패했을 때 아래문구 출력
	{
		cout << "Fail to open an input file (" << INPUT_FILE_NAME << ") \n";
		exit(1);
	}
	fout.open(OUTPUT_FILE_NAME);
	if (fout.fail()) //파일 열기 실패했을 때 아래문구 출력
	{
		cout << "Fail to open an output file (" << OUTPUT_FILE_NAME << ") \n";
		exit(1);
	}
	max_num_data = fileInputData(fin, data_array, max_num_data); //10개의 정수 데이터를 입력 받는 함수
	fout << "Total " << max_num_data << " input from input data file." << endl;
	fout << "Total " << max_num_data << " inpteger data : {";
	for (int i = 0; i < max_num_data; i++)
		fout << data_array[i] << " ,";
	fout << "}" << endl;
	getStatistics_fileOut(data_array, max_num_data, fout);
	fin.close();
	fout.close();
}
int fileInputData(ifstream& fin, int* data_array, int max_num_data)
{
	int num_data = 0;

	while (!fin.eof())
	{
		fin >> data_array[num_data];
		num_data++;
	}
	max_num_data = num_data;
	return max_num_data;
}
void getStatistics_fileOut(int* data_array, int num_data, ofstream& fout)
{
	int data;
	int min = INT_MAX;
	int max = INT_MIN;
	double sum = 0.0, var, diff, avg, sq_diff_sum = 0.0, std_dev;
	for (int i = 0; i < num_data; i++)
	{
		data = data_array[i];
		sum += data;
		if (data<min)
			min = data;
		if (data > max)
			max = data;
	}
	avg = sum / (double)num_data;
	for (int i = 0; i < num_data; i++)
	{
		diff = data_array[i] - avg;           // diff는 각 배열의 값에서 평균을 빼준다(평균과 배열의 차이 구하기)
		sq_diff_sum += diff * diff;           //  sq_diff_sum은 각 배열과 평균의 차이의 제곱의 합
	}
	var = sq_diff_sum / (double)num_data;
	std_dev = sqrt(var);
	
	fout << "min(" << min << "), max(" << max << "), sum(" << sum << "), avg(" << avg << "), var(" << var << "), std_dev(" << std_dev << ")";
}