#pragma once
#include <vector>

class Pixel {

	public:
		int red, green, blue;

		Pixel() : red(0), green(0), blue(0) {}
		Pixel(int r, int g, int b) : red(r), green(g), blue(b) {}

};

typedef std::vector< std::vector<Pixel> > PixelMat;

class Bitmap {

	public:
		unsigned int size;
		unsigned int reserve1;
		unsigned int reserve2;
		unsigned int offset;

		unsigned int headersize;
		unsigned int width;
		unsigned int height;
		unsigned short int planes;
		unsigned short int bits;
		unsigned int compression;
		unsigned int byte_size;
		unsigned int hres;
		unsigned int vres;
		unsigned int num_colors;
		unsigned int num_imp_colors;

		unsigned int colorFactor = 0;
		
	private:
		PixelMat pixels;

	public:
		Bitmap(const char *);
		void Save(const char *);
		void Dither();

};
