#ifndef CAMERA_H
#define CAMERA_H

#include "Types.hxx"

class Camera
{
	public:
		Camera(const string& name, const string& source);
		
		vector<uInt8> scanImage();
		
		inline string getName() const { return this -> name; }
		inline string getSource() const { return this -> source; }
	
	private:
		string name;
		string source;
		
		vector<uInt8> currentImage;
};

#endif