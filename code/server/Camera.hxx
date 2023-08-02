#ifndef CAMERA_H
#define CAMERA_H

#include "Types.hxx"

class Camera
{
	public:
		Camera(const string& name, const string& source);
		
		vector<uInt8> getImage();
		vector<uInt8> scanImage();
	
	private:
		string name;
		string source;
		
		vector<uInt8> currentImage;
};

#endif