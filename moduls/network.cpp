#include <iostream>
#include <math.h>

#include "network.h"
#include "matrix.h"

using namespace std;

float nueral_network::sigm(float x)
{
	return 1 / (1 + exp(-x));
}

float nueral_network::dSigm(float x)
{
	return x * (1 - x);
}

nueral_network::nueral_network()
{
	n = 0;
	layers = nullptr;

	weights = nullptr;
	nuerals = nullptr;
	nuerals_errs = nullptr;

	alpha = 5;
}

void nueral_network::init(int* layers, int n)
{
	this->n = n;

	this->layers = new int[n];

	for (int i = 0; i < n; i++)
	{
		this->layers[i] = layers[i];
	}

	nuerals = new float* [n];
	nuerals_errs = new float* [n];

	for (int i = 0; i < n; i++)
	{
		nuerals[i] = new float[layers[i]];
		nuerals_errs[i] = new float[layers[i]];

		for (int j = 0; j < layers[i]; j++)
		{
			nuerals[i][j] = 0;
			nuerals_errs[i][j] = 0;
		}
	}

	weights = new matrix[n - 1];

	for (int i = 0; i < n - 1; i++)
	{
		weights[i].init(layers[i + 1], layers[i]);
		weights[i].setRandom(i);
	}
}

void nueral_network::clear()
{
	for (int i = 0; i < n; i++)
	{
		delete[] nuerals[i];
		delete[] nuerals_errs[i];
	}

	delete[] nuerals;
	delete[] nuerals_errs;
	delete[] weights;
	delete[] layers;

	n = 0;
}

void nueral_network::printWeights()
{
	cout << endl;

	cout << "====================================" << endl;

	for (int i = 0; i < n - 1; i++)
	{
		cout << "Веса " << i << "->" << i + 1 << " : " << endl;
		weights[i].print();
	}

	cout << "====================================" << endl;

	cout << endl;
}

void nueral_network::printNuerals()
{
	cout << endl;

	cout << "************************************" << endl;

	cout << "Нейроны: " << endl;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < layers[i]; j++)
		{
			cout << "(" << nuerals[i][j] << " : " << nuerals_errs[i][j] << ")\t";
		}

		cout << endl;
	}

	cout << "************************************" << endl;

	cout << endl;
}

int nueral_network::forwordPropagetion(float& value, float* vector)
{
	for (int i = 0; i < layers[0]; i++)
	{
		nuerals[0][i] = vector[i];
	}

	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < layers[i]; j++)
		{
			float sum = 0;

			for (int k = 0; k < layers[i - 1]; k++)
			{
				sum += nuerals[i - 1][k] * weights[i - 1].get(j, k);
			}

			nuerals[i][j] = sigm(sum);
		}
	}

	int max = 0;

	for (int i = 0; i < layers[n - 1]; i++)
	{
		if (nuerals[n - 1][max] < nuerals[n - 1][i])
		{
			max = i;
		}
	}

	value = nuerals[n - 1][max];

	return max;
}

void nueral_network::backPropagetion(float* example, float* p)
{
	float value = 0;

	forwordPropagetion(value, example);

	float** current = new float* [n];

	for (int i = 0; i < n; i++)
	{
		current[i] = new float[layers[i]];
	}

	for (int i = 0; i < layers[n - 1]; i++)
	{
		current[n - 1][i] = (nuerals[n - 1][i] - p[i]) * dSigm(nuerals[n - 1][i]);
	}

	for (int i = n - 2; i >= 0; i--)
	{
		for (int j = 0; j < layers[i]; j++)
		{
			float sum_errs = 0;

			for (int k = 0; k < layers[i + 1]; k++)
			{
				sum_errs += nuerals[i + 1][k] * weights[i].get(k, j);
			}

			current[i][j] = sum_errs * dSigm(nuerals[i][j]);
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < layers[i]; j++)
		{
			nuerals_errs[i][j] += current[i][j];
		}

		delete[] current[i];
	}

	delete[] current;
}

void nueral_network::learn()
{
}
