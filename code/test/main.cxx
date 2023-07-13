#include "Types.hxx"
#include "Detector.hxx"

#include <fstream>
#include <iterator>

#include <iostream>

vector<uInt8> getImage(const string& path)
{
	vector<uInt8> image;
	
	std::fstream scanner(path.c_str(), std::ios::in);
	
	scanner.unsetf(std::ios::skipws);
	
	if(!scanner)
		exit(-1);
	
	scanner.seekg(0, scanner.end);
	image.reserve(scanner.tellg());
	scanner.seekg(0, scanner.beg);
	
	image.insert(image.begin(), std::istream_iterator<uInt8>(scanner), std::istream_iterator<uInt8>());
	
	scanner.close();
	
	return image;
}

int main()
{
	string imagePath;
	string labelsPath;
	string networkPath;
	
	std::cout << "Image path: ";
	std::cin >> imagePath;
	
	std::cout << "Labels path: ";
	std::cin >> labelsPath;
	
	std::cout << "Network path: ";
	std::cin >> networkPath;
	
	vector<uInt8> image = getImage(imagePath);
	
	Detector detector(0.45, 0.45, networkPath);
	std::fstream scanner(labelsPath.c_str(), std::ios::in);
	
	vector<string> labels;
	{
		string label;
		
		while(getline(scanner, label))
			labels.push_back(label);
	}
	
	vector<BBox> detections = detector.detect(image, labels);
	
	for(BBox box : detections)
		std::cout << box.type << ": [" << box.x << ' ' << box.y << ' ' << box.w << ' ' << box.h << "]" << '\n';
}