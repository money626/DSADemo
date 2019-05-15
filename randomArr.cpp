#include <fstream>
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
int main()
{
	int size, max;
	cin >> size >> max;
	ofstream oup;
	oup.open("file.txt");
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			if(i == j)
			{
				oup << 0 << " ";
			}
			else
			{
				oup << rand() % max << " ";
			}
		}
		oup << endl;
	}
}
