#include "bitmap.h"
#include <iostream>
#include <fstream>

Bitmap::Bitmap(const char * filepath)
{
	std::ifstream file(filepath, std::ios::in | std::ios::binary);

	char m[2];

	colorFactor = 0;

	for(int i = 0; i < 2; i++)
		file.read(&m[i], 1);

	if(m[0] != 'B' && m[1] != 'M')
	{
		std::cout << "The file is not a bitmap image!!" << std::endl;
		exit(3);
	}

	file.read((char *)&size, 4);
	file.read((char *)&reserve1, 2);
	file.read((char *)&reserve2, 2);
	file.read((char *)&offset, 4);
	file.read((char *)&headersize, 4);
	file.read((char *)&width, 4);
	file.read((char *)&height, 4);
	file.read((char *)&planes, 2);
	file.read((char *)&bits, 2);
	file.read((char *)&compression, 4);
	file.read((char *)&byte_size, 4);
	file.read((char *)&hres, 4);
	file.read((char *)&vres, 4);
	file.read((char *)&num_colors, 4);
	file.read((char *)&num_imp_colors, 4);

	file.seekg(offset);

	for(int row = 0; row < height; row++)
	{
		std::vector <Pixel> row_data;
		for(int col = 0; col < width; col++)
		{
			int b = file.get();
			int g = file.get();
			int r = file.get();

			row_data.push_back(Pixel(r, g, b));
		}
		
		file.seekg(width % 4, std::ios::cur);

		pixels.push_back(row_data);
	}

	file.close();
}

void Bitmap::Save(const char * filename)
{
	char temp = 'B', temp2 = 'M';
	std::ofstream file(filename, std::ios::out | std::ios::binary);
	file.write(&temp, 1);
	file.write(&temp2, 1);

	width = pixels[0].size();
	height = pixels.size();

	file.write((char *)&size, 4);
	file.write((char *)&reserve1, 2);
	file.write((char *)&reserve2, 2);
	file.write((char *)&offset, 4);
	file.write((char *)&headersize, 4);
	file.write((char *)&width, 4);
	file.write((char *)&height, 4);
	file.write((char *)&planes, 2);
	file.write((char *)&bits, 2);
	file.write((char *)&compression, 4);
	file.write((char *)&byte_size, 4);
	file.write((char *)&hres, 4);
	file.write((char *)&vres, 4);
	file.write((char *)&num_colors, 4);
	file.write((char *)&num_imp_colors, 4);

	for(int i = 0; i <= pixels.size() - 1; i++ )
	{
		std::vector<Pixel> & row_data = pixels[i];

		for(int j = 0; j < row_data.size(); j++)
		{
			Pixel& pix = row_data[j];
			file.put((char) pix.blue);
			file.put((char) pix.green);
			file.put((char) pix.red);
		}

		for(int k = 0; k < row_data.size() % 4; k++)
		{
			file.put(0);
		}
	}

	file.close();
}


void Bitmap::Dither()
{
	for(int y = 0; y < height - 1; y++)
	{
		for(int x = 1; x < width - 1; x++)
		{
			auto pixel = pixels[y][x];

			int NewR = (colorFactor * pixel.red / 255)   * (255 / colorFactor);
			int NewG = (colorFactor * pixel.green / 255) * (255 / colorFactor);
			int NewB = (colorFactor * pixel.blue / 255)  * (255 / colorFactor);

			
			pixels[y][x].red   =  NewR;
			pixels[y][x].green =  NewG;
			pixels[y][x].blue  =  NewB;

			int ErrorR = pixel.red   -   NewR;
			int ErrorG = pixel.green -   NewG;
			int ErrorB = pixel.blue  -   NewB;

			pixels[y][x + 1].red   = pixels[y][x + 1].red   + ErrorR * (7.0f / 16.0f);
			pixels[y][x + 1].green = pixels[y][x + 1].green + ErrorG * (7.0f / 16.0f);
			pixels[y][x + 1].blue  = pixels[y][x + 1].blue  + ErrorB * (7.0f / 16.0f);

			pixels[y + 1][x - 1].red    = pixels[y + 1][x - 1].red   + ErrorR * (3.0f / 16.0f);
			pixels[y + 1][x - 1].green  = pixels[y + 1][x - 1].green + ErrorG * (3.0f / 16.0f);
			pixels[y + 1][x - 1].blue   = pixels[y + 1][x - 1].blue  + ErrorB * (3.0f / 16.0f);

			pixels[y + 1][x].red    = pixels[y + 1][x].red   + ErrorR * (5.0f / 16.0f);
			pixels[y + 1][x].green  = pixels[y + 1][x].green + ErrorG * (5.0f / 16.0f);
			pixels[y + 1][x].blue   = pixels[y + 1][x].blue  + ErrorB * (5.0f / 16.0f);

			pixels[y + 1][x + 1].red    = pixels[y + 1][x + 1].red   + ErrorR * (1.0f / 16.0f);
			pixels[y + 1][x + 1].green  = pixels[y + 1][x + 1].green + ErrorG * (1.0f / 16.0f);
			pixels[y + 1][x + 1].blue   = pixels[y + 1][x + 1].blue  + ErrorB * (1.0f / 16.0f);

		}
	}
}
