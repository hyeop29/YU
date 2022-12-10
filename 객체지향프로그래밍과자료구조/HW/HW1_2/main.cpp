/** Homework (1)
*
* - integer print formatting
* - Programmed by Chang-Hyeop LEE
* - Last update: 2020-09-05
*/
#include <iostream>
#include <iomanip>
#include<bitset>
using namespace std;

void main()
{
	cout.setf(ios::showbase); // ������ ��� ���� ǥ��
	cout.setf(ios::right);  //������ �� ����

	for (int i = 0; i <= 32; i++)
	{
		cout << setw(6) << std::dec << i;
		cout << setw(6) << std::oct << i;
		cout << setw(6) << std::hex << i;
		cout << setw(12) << bitset<8>(i) << endl;
	}
}