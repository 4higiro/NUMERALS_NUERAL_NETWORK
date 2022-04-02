// ���������� �����
#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STBI_ONLY_PNG

// ����������� ��������
image::image()
{
	width = 0;
	height = 0;
	channels = 0;
	picture = nullptr;
}

// ������������� ��������
void image::init(const char* path)
{
	unsigned char* pixels = stbi_load(path, &width, &height, &channels, 1);

	picture = new float* [width];

	for (int i = 0; i < width; i++)
	{
		picture[i] = new float[height];

		for (int j = 0; j < height; j++)
		{
			picture[i][j] = (float)pixels[j + i * height];
		}
	}
}

// ��������� ���������� � ��������
void image::getByte(float**& bytes)
{
	bytes = new float* [width];

	for (int i = 0; i < width; i++)
	{
		bytes[i] = new float[height];

		for (int j = 0; j < height; j++)
		{
			bytes[i][j] = picture[i][j] / 255;

			if (bytes[i][j] >= 0.5)
				bytes[i][j] = 1;
			else
				bytes[i][j] = 0;
		}
	}
}

// ������ ������ ��������
int image::getWidth()
{
	return width;
}

// ������ ������ ��������
int image::getHeight()
{
	return height;
}

// ������ ���������� ������� �����������
int image::getChannels()
{
	return channels;
}

// ������� ������ � ��������
void image::clear()
{	
	for (int i = 0; i < width; i++)
	{
		delete[] picture[i];
	}

	width = 0;
	height = 0;
	channels = 0;

	delete[] picture;
}
