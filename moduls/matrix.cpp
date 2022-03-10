#include <iostream>

#include "matrix.h"

matrix::matrix()
{
	rows = 0;
	columns = 0;
	data = nullptr;
}

void matrix::init(int rows, int columns)
{
	data = new float* [rows];

	for (int i = 0; i < rows; i++)
	{
		data[i] = new float[columns];
	}

	this->rows = rows;
	this->columns = columns;
}

void matrix::clear()
{
	for (int i = 0; i < rows; i++)
	{
		delete[] data[i];
	}

	delete[] data;

	rows = 0;
	columns = 0;
}

float matrix::get(int i, int j)
{
	return data[i][j];
}

void matrix::set(int i, int j, float element)
{
	data[i][j] = element;
}

void matrix::setRandom(int seed)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (i != 0 && j != 0)
			{
				data[i][j] = (float)seed / i + (float)seed / j - (float)i * j * seed + (float)i / j;
			}
			else
			{
				data[i][j] = (float)seed * i - (float)seed * j + seed + 1 + pow(i, j);
			}

			data[i][j] /= 10;
		}
	}
}

void matrix::setNULL()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			data[i][j] = 0;
		}
	}
}

void matrix::setOnes()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			data[i][j] = 1;
		}
	}
}

void matrix::multi(float* vector, float*& result)
{
	for (int i = 0; i < rows; i++)
	{
		result[i] = 0;

		for (int j = 0; j < columns; j++)
		{
			result[i] += data[i][j] * vector[j];
		}
	}
}

int matrix::getRows()
{
	return rows;
}

int matrix::getColumns()
{
	return columns;
}

void matrix::print()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			std::cout << data[i][j] << "\t";
		}

		std::cout << std::endl;
	}
}
