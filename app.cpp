#include "bitmap.h"
#include <iostream>
#include <cstdlib>

int main(int argc, char**argv)
{
	const char * Name = "Out.BMP";
	Bitmap b(argv[2]);

	if(argc < 3)
	{
		std::cout << "Usage " << argv[0] << " <Colorfactor> " << "<ImageFile> <Name of the out file(Optional)>\n";
		return 1;
	}

	if(argc == 4)
		Name = argv[3];

	b.colorFactor = atoi(argv[1]);
	std::cout << "colorFactor = " << b.colorFactor << std::endl;

	std::cout << "size of the file is: " << b.size << std::endl;
	std::cout << "offset to data: " << b.offset << std::endl;
	std::cout << "Header size: " << b.headersize << std::endl;
	std::cout << "width x height = " << b.width << "x" << b.height << std::endl;

	std::cout << "Number of planes present: " << b.planes << std::endl;
	std::cout << "bits per pixel: " << b.bits << std::endl;
	std::cout << "compression type: " << b.compression << std::endl;
	std::cout << "resolution per meter: " << b.hres << "x" << b.vres << std::endl;
	std::cout << "Number of colors: " << b.num_colors << std::endl;
	std::cout << "Number of imp colors: " << b.num_imp_colors << std::endl;

	b.Dither();
	b.Save(Name);

	return 0;
}
