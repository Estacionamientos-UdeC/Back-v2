#ifndef DETECTOR_H
#define DETECTOR_H

#include "Types.hxx"

#include <opencv2/dnn.hpp>

namespace cvDNN = cv::dnn;

struct BBox
{
	int x;
	int y;
	
	int w;
	int h;
	
	string tag;
};

class Detector
{
	public:
		Detector();
		Detector(const string& settings);
		
		vector<BBox> detect(const vector<uInt8>& image);
		
		inline void setMinScore(const float minScore) { this -> minScore = minScore; }
		inline void setMinTrust(const float minTrust) { this -> minTrust = minTrust; }
		
		inline float getMinScore() const { return this -> minScore; }
		inline float getMinTrust() const { return this -> minTrust; }
	
	private:
		float minScore;
		float minTrust;
		
		cvDNN::Net network;
		
		vector<string> tags;
};

#endif