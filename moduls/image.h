// Защита от повторного включения
#pragma once

// Класс картинки
class image
{
private:
	int width;
	int height;
	int channels;
	float** picture;
public:
	image();
	void init(const char* path);
	void getByte(float**& bytes);
	int getWidth();
	int getHeight();
	int getChannels();
	void clear();
};

