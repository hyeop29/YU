#include <iostream>
#include <fstream>
#include "BigArray.h"

using namespace std;
#define ELEMENTS_PER_LINE 10
#define SAMPLE_LINES 5

void main()
{
	ofstream fout;
	fout.open("output.txt");
	if (fout.fail())
	{
		cout << "Error in opening output.txt !!" << endl;
		exit;
	}
	int base_offset = 0;
	int big_rand_size = 5000;
	BigArray ba_1(big_rand_size);
	fout << "Generating big rand array of " << ba_1.size() << " elements with base_offset " << base_offset << " ... " << endl;
	ba_1.genBigRandArray(base_offset);
	ba_1.fprintSample(fout, ELEMENTS_PER_LINE, SAMPLE_LINES);
	ba_1.fprintStatistics(fout);
	ba_1.selection_sort();
	ba_1.fprintSample(fout, ELEMENTS_PER_LINE, SAMPLE_LINES);
	cout << endl;
	big_rand_size = 500000;
	base_offset = -big_rand_size / 2;
	BigArray ba_2(big_rand_size);
	fout << endl << "Generating big rand array of " << ba_2.size() << " elements with base_offset " << base_offset << " ... " << endl;
	ba_2.genBigRandArray(base_offset);
	ba_2.fprintSample(fout, ELEMENTS_PER_LINE, SAMPLE_LINES);
	ba_2.fprintStatistics(fout);
	ba_2.quick_sort();
	ba_2.fprintSample(fout, ELEMENTS_PER_LINE, SAMPLE_LINES);
	fout.close();
}