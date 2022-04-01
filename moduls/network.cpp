// Включаемые файлы
#include <iostream>
#include <math.h>

#include "network.h"
#include "matrix.h"

// Используемые имена
using namespace std;

// Сигмоида
float nueral_network::sigm(float x)
{
	return 1 / (1 + exp(-x));
}

// Производная сигмоиды
float nueral_network::dSigm(float x)
{
	return x * (1 - x);
}

// Конструктор нейронной сети
nueral_network::nueral_network()
{
	n = 0;
	layers = nullptr;

	weights = nullptr;
	d_weights = nullptr;

	nuerals = nullptr;
	nuerals_errs = nullptr;

	alpha = 0;
	betta = 0;
}

// Инициализация нейронной сети
void nueral_network::init(int* layers, int n, float alpha, float betta)
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
		nuerals[i] = new float[this->layers[i]];
		nuerals_errs[i] = new float[this->layers[i]];

		for (int j = 0; j < this->layers[i]; j++)
		{
			nuerals[i][j] = 0;
			nuerals_errs[i][j] = 0;
		}
	}

	weights = new matrix[n - 1];
	d_weights = new matrix[n - 1];

	for (int i = 0; i < n - 1; i++)
	{
		weights[i].init(layers[i + 1], layers[i]);
		d_weights[i].init(layers[i + 1], layers[i]);
		weights[i].setRandom(n - i * 2);
		d_weights[i].setNULL();
	}

	this->alpha = alpha;
	this->betta = betta;
}

// Очистка данных нейросети
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

	alpha = 0;
	betta = 0;
}

// Печать значений синапсов на экран
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

// Печать значений нейронов на экран
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

// Прямое распространение
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

	if (layers[n - 1] == 1)
	{
		if (nuerals[n - 1][0] > 0.6)
			return 1;
		else
			return 0;
	}

	return max;
}

// Обратное распространение
float nueral_network::backPropagetion(float* example, float* p)
{
	float value = 0;

	forwordPropagetion(value, example);

	for (int i = 0; i < layers[n - 1]; i++)
	{
		nuerals_errs[n - 1][i] = (p[i] - nuerals[n - 1][i]) * dSigm(nuerals[n - 1][i]);
	}

	for (int i = n - 2; i >= 0; i--)
	{
		for (int j = 0; j < layers[i]; j++)
		{
			float sum_errs = 0;

			for (int k = 0; k < layers[i + 1]; k++)
			{
				sum_errs += weights[i].get(k, j) * nuerals_errs[i + 1][k];
			}

			nuerals_errs[i][j] = sum_errs * dSigm(nuerals[i][j]);
		}
	}

	value = 0;

	for (int i = 0; i < layers[n - 1]; i++)
	{
		value += (p[i] - nuerals[n - 1][i]) * (p[i] - nuerals[n - 1][i]);
	}

	value /= layers[n - 1];

	return value;
}

// Изменение значений весов
void nueral_network::learn()
{
	for (int k = 0; k < n - 1; k++)
	{
		for (int i = 0; i < layers[k + 1]; i++)
		{
			for (int j = 0; j < layers[k]; j++)
			{
				weights[k].set(i, j, weights[k].get(i, j) + alpha * nuerals[k][j] * nuerals_errs[k + 1][i] + betta * d_weights[k].get(i, j));
				d_weights[k].set(i, j, alpha * nuerals[k][j] * nuerals_errs[k + 1][i] + betta * d_weights[k].get(i, j));
			}
		}
	}
}
