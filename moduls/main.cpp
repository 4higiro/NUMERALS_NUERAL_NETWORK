// ���������� �����
#include <iostream>

#include "network.h"
#include "image.h"

// ������������ �����
using namespace std;

// ����� ����� � ���������
void main()
{
	image example;
	example.init("resources/numeral.png");
	float** bytes;
	example.getByte(bytes);
	for (int i = 0; i < example.getWidth(); i++)
	{
		for (int j = 0; j < example.getHeight(); j++)
		{
			cout << bytes[i][j] << "  ";
		}

		cout << endl;
	}
}