#pragma once

#include "matrix.h";

class nueral_network
{
private:
	int n;
	int* layers;

	matrix* weights;
	float** nuerals;
	float** nuerals_errs;

	float alpha;

	float sigm(float x);
	float dSigm(float x);
public:
	nueral_network();
	void init(int* layers, int n);
	void clear();
	void printWeights();
	void printNuerals();
	int forwordPropagetion(float& value, float* vector);
	void backPropagetion(float* example, float* p);
	void learn();
};