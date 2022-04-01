// Защита от повторного включения
#pragma once

// Класс матрицы
class matrix
{
private:
	float** data; // Данные матрицы
	int rows, columns; // Количество строк и столбцов
public:
	matrix();
	void init(int rows, int columns);
	void clear();
	float get(int i, int j);
	void set(int i, int j, float element);
	void setRandom(int seed);
	void setNULL();
	void setOnes();
	void multi(float* vector, float*& result);
	int getRows();
	int getColumns();
	void print();
};

