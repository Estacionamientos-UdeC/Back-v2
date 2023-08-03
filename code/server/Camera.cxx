#include "Camera.hxx"

#include <fstream>
#include <iterator>

Camera::Camera(const string& name, const string& source) : name(name), source(source)
{
}

vector<uInt8> Camera::scanImage()
{
	vector<uInt8> newImage;
	{
		std::fstream scanner(this -> source, std::ios::in | std::ios::binary);
		
		scanner.unsetf(std::ios::skipws);
		
		if(!scanner.is_open())
			exit(-1);
		
		scanner.seekg(0, scanner.end);
		newImage.reserve(scanner.tellg());
		scanner.seekg(0, scanner.beg);
		
		newImage.insert(newImage.begin(), std::istream_iterator<uInt8>(scanner), std::istream_iterator<uInt8>());
		
		scanner.close();
	}
	
	this -> currentImage = newImage;
	
	return this -> currentImage;
}