#pragma once

class matrix
{
private:
	float** data;
	int rows, columns;
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

