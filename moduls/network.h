// Защита от повторного включения
#pragma once

// Включаемые файлы
#include "matrix.h";

// Класс нейронной сети
class nueral_network
{
private:
	int n; // Количество слоев
	int* layers; // Количсетво нейронов на каждом слое

	matrix* weights; // Массив значений синапсов
	matrix* d_weights; // Массив с изменениями синапсов на предыдущей итерации

	float** nuerals; // Массив с нейронами
	float** nuerals_errs; // Массив с ошибками нейронов

	float** biases; // Массив с нейронами смещения
	float** d_biases; // Массив с изменениями смещений на предыдущей итерации

	float alpha; // Скорость обучения
	float betta; // Момент

	float sigm(float x);
	float dSigm(float x);
public:
	nueral_network(); 
	void init(int* layers, int n, float alpha, float betta);
	void clear();
	void printWeights();
	void printNuerals();
	int forwordPropagetion(float& value, float* vector);
	float backPropagetion(float* example, float* p);
	void learn();
};