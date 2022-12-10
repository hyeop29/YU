/* BigArray.cpp (1) */
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include "BigArray.h"
using namespace std;

BigArray::BigArray(int n) // constructor
:num_elements(n)
{
	big_array = (int*) new int[num_elements]; //동적 생성
	if (big_array == NULL) //에러 메시지 출력
	{
		cout << "Error in creation of dynamic array of size(" << num_elements << ") !!" << endl;
		exit;
	}
}
BigArray::~BigArray() // destructor
{
	if (big_array != NULL)
		delete[] big_array; //반환, 소멸
}
void BigArray::genBigRandArray(int base_offset)
{
	char* flag; //생성 된 난수가 중복인지 아닌지 확인하기 위한 char 
	int count = 0;
	int rand_h, rand_l, big_rand, biased_big_rand;
	srand(time(0));
	flag = (char*) new char[num_elements];//flag를 배열로 사용할 수 있도록 동적 생성
	while (count < num_elements)
	{
		rand_h = rand();
		rand_l = rand();
		big_rand = ((long)rand_h << 15) | rand_l; //bitwise or 연산으로 30비트 난수
		big_rand = big_rand % num_elements;// 0 ~ num_elements - 1
		if (flag[big_rand] == 1)//생성된 적 있는 난수
			continue;
		else
		{
			flag[big_rand] = 1;
			biased_big_rand = big_rand + base_offset;
			big_array[count] = biased_big_rand;
			count++;
		}
	}
	delete[] flag; //더 이상 필요없기에 delete
}
void BigArray::getStatistics(ArrayStatistics & stats) //통계분석
{
	int min = INT_MAX;
	int max = INT_MIN;
	double mean = 0.0;
	double sum = 0.0;
	double sq_sum_avg = 0.0;
	double diff_sq_sum = 0.0;
	double var, std_dev;
	int element;
	for (int i = 0; i < num_elements; i++)
	{
		element = big_array[i];
		sum += element;
		if (element > max)
			max = element;
		if (element < min)
			min = element;
	}
	mean = sum / (double)num_elements;
	diff_sq_sum = 0.0;
	for (int i = 0; i < num_elements; i++)
	{
		element = big_array[i];
		diff_sq_sum +=
			(element - mean) * (element - mean);
	}
	var = diff_sq_sum / (double)num_elements; //분산
	std_dev = sqrt(var); //표준편차
	stats.min = min; //구조체에 담는 과정
	stats.max = max;
	stats.avg = mean;
	stats.var = var;
	stats.std_dev = std_dev;
}
void BigArray::fprintStatistics(ostream& fout) //통계분석 출력 함수
{
	ArrayStatistics stats;
	fout.setf(ios::fixed);
	fout.setf(ios::showpoint);
	fout.precision(2);

	getStatistics(stats);
	fout << "Statistics: " << endl;
	fout << " min (" << stats.min << "), max ("
		<< stats.max << "), avg (" << stats.avg;
	fout << "), var (" << stats.var << "), std_dev ("
		<< stats.std_dev << ")" << endl;
}
void BigArray::suffle() //배열 섞어주기
{
	srand(time(0));
	int index1, index2;
	int rand_1, rand_2;
	int temp;
	for (int i = 0; i < num_elements; i++)
	{
		rand_1 = rand();
		rand_2 = rand();
		index1 = ((rand_1 << 15) | rand_2)
			% num_elements;
		rand_1 = rand();
		rand_2 = rand();
		index2 = ((rand_1 << 15) | rand_2)
			% num_elements;
		temp = big_array[index1];
		big_array[index1] = big_array[index2];
		big_array[index2] = temp;
	}
}
void BigArray::selection_sort() //선택 정렬
{
	int min; // index of the element with minimum value
	double minValue; // minimum value
	for (int i = 0; i < num_elements - 1; i++)
	{
		min = i;
		minValue = big_array[i];
		for (int j = i + 1; j < num_elements; j++)
		{
			if (minValue > big_array[j])
			{
				min = j;
				minValue = big_array[j];
			}
		}
		if (min != i) // if a smaller element is found, then swap
		{
			/* minValue is dA[min] */
			big_array[min] = big_array[i];
			big_array[i] = minValue;
		}
	} // end for
}
int _partition(int* array, int size, int left, int right, int pivotIndex, int level) //분활 하는 기능(퀵소팅을 위해)
{
	int pivotValue; // pivot value
	int newPI; // store index
	double temp;
	int i;
#ifdef DEBUG_QUICKSORT
	for (i = 0; i < level; i++) // put indentation
		fout << " ";
	fout << " Partition (left " << left << ", right "
		<< right << ", pivotIdex "
		<< pivotIndex << "(pV:"
		<< array[pivotIndex]
		<< ") ) =>";
#endif
	pivotValue = array[pivotIndex];

	temp = array[pivotIndex];
	array[pivotIndex] = array[right];
	array[right] = temp; // Move pivot to end
	newPI = left;
	for (i = left; i <= (right - 1); i++) {
		if (array[i] <= pivotValue) {
			temp = array[i];
			array[i] = array[newPI];
			array[newPI] = temp;
			newPI = newPI + 1;
		}
	}
	// swap array[newPI] and array[right];
	// Move pivot to its final place
	temp = array[newPI];
	array[newPI] = array[right];
	array[right] = temp;
	return newPI;
}
void _quick_sort(int* array, int size, int left, int right, int level)
{
	int pI, newPI; // pivot index
	if (left >= right) {
		return;
	}
	else if (left < right)
	{ // subarray of 0 or 1 elements already sorted
	//select a pI (pivotIndex) in the range left ≤ pI ≤ right
		pI = (left + right) / 2;
	}
	newPI = _partition(array, size, left, right, pI, level);
	if (left < (newPI - 1))
	{
		_quick_sort(array, size, left, newPI - 1, level + 1);
		// recursively sort elements on the left of pivotNewIndex
	}
	if ((newPI + 1) < right)
	{
		_quick_sort(array, size, newPI + 1, right, level + 1);
		// recursively sort elements on the right of pivotNewIndex
	}
} // end _quick_sort()
void BigArray::quick_sort()
{
	int pI, newPI; // pivot index
	_quick_sort(big_array, num_elements, 0, num_elements - 1, 0);
}
void BigArray::fprintBigArray(ostream& fout, int elements_per_line)
{
	int count = 0;
	while (count < num_elements)
	{
		fout << setw(5) << big_array[count];
		count++;
		if (count % elements_per_line == 0)
			fout << endl;
	}
	fout << endl;
}
void BigArray::fprintSample(ostream& fout, int elements_per_line, int num_sample_lines)
{
	int last_block_start;
	int count = 0;
	for (int i = 0; i < num_sample_lines; i++)
	{
		for (int j = 0; j < elements_per_line; j++)
		{
			if (count > num_elements)
			{
				fout << endl;
				return;
			}
			fout << setw(10) << big_array[count];
			count++;
		}
		fout << endl;
	}
	if (count < (num_elements - elements_per_line * num_sample_lines))
		count = num_elements - elements_per_line * num_sample_lines;
	fout << endl << " . . . . . " << endl;
	for (int i = 0; i < num_sample_lines; i++)
	{
		for (int j = 0; j < elements_per_line; j++)
		{
			if (count > num_elements)
			{
				fout << endl;
				return;
			}
			fout << setw(10) << big_array[count];
			count++;
		}
		fout << endl;
	}
	fout << endl;
}
