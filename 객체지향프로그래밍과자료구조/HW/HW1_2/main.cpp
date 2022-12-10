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
	cout.setf(ios::showbase); // 정수의 출력 형식 표시
	cout.setf(ios::right);  //오른쪽 줄 맞춤

	for (int i = 0; i <= 32; i++)
	{
		cout << setw(6) << std::dec << i;
		cout << setw(6) << std::oct << i;
		cout << setw(6) << std::hex << i;
		cout << setw(12) << bitset<8>(i) << endl;
	}
}