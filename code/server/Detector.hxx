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
	
	string type;
};

class Detector
{
	public:
		Detector(const float minScore, const float minTrust, const string& network);
		
		vector<BBox> detect(const vector<uInt8>& image, const vector<string>& typeNames);
		
		inline void setMinScore(const float minScore) { this -> minScore = minScore; }
		inline void setMinTrust(const float minTrust) { this -> minTrust = minTrust; }
		
		inline float getMinScore() const { return this -> minScore; }
		inline float getMinTrust() const { return this -> minTrust; }
	
	private:
		float minScore;
		float minTrust;
		
		cvDNN::Net network;
};

#endif