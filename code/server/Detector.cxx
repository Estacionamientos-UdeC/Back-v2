#include "Detector.hxx"

#include <opencv2/imgcodecs.hpp>

Detector::Detector(const float minScore, const float minTrust, const string& network) : minScore(minScore), minTrust(minTrust)
{
	this -> network = cvDNN::readNet(network);
}

vector<BBox> Detector::detect(const vector<uInt8>& image, const vector<string>& typeNames)
{
	const int IMAGE_W = 640;
	const int IMAGE_H = 640;
	
	const int NMS_THRESHOLD = 0.5;
	
	cv::Mat imageMatrix = cv::imdecode(image, cv::IMREAD_UNCHANGED);
	
	// Section 1:
	
	cv::Mat inferences;
	{
		cv::Mat BLOB = cvDNN::blobFromImage(imageMatrix, 1.0 / 255.0, cv::Size(IMAGE_W, IMAGE_H), cv::Scalar(), true, false);
		
		vector<cv::Mat> results;
		
		this -> network.setInput(BLOB);
		this -> network.forward(results, this -> network.getUnconnectedOutLayersNames());
		
		inferences = results[0].reshape(0, {results[0].size[1], results[0].size[2]});
	}
	
	// Section 2:
	
	vector<BBox> detections;
	{
		vector<int> typeIDs;
		vector<float> trusts;
		
		vector<cv::Rect> boxes;
		{
			float scaleX = imageMatrix.cols / IMAGE_W;
			float scaleY = imageMatrix.rows / IMAGE_H;
			
			for(int row = 0; row < inferences.rows; row++)
			{
				float trust = inferences.at<float>(row, 4);
				
				if(trust >= this -> minTrust)
				{
					int typeID;
					double score;
					{
						cv::Mat scores = inferences(cv::Range(row, row + 1), cv::Range(5, inferences.cols));
						cv::Point ID;
						
						cv::minMaxLoc(scores, 0, &score, 0, &ID);
						
						typeID = ID.x;
					}
					
					if(score >= this -> minScore)
					{
						trusts.push_back(trust);
						typeIDs.push_back(typeID);
						
						float x = inferences.at<float>(row, 0); // Box center x (in BLOB image coordinates)
						float y = inferences.at<float>(row, 1); // Box center y (in BLOB image coordinates)
						
						float w = inferences.at<float>(row, 2);
						float h = inferences.at<float>(row, 3);
						
						//
						
						int rectX = (x - (w / 2.0)) * scaleX; // Box TOP-LEFT corner x (in original image coordinates)
						int rectY = (y - (h / 2.0)) * scaleY; // Box TOP-LEFT corner y (in original image coordinates)
						
						int rectW = w * scaleX;
						int rectH = h * scaleY;
						
						boxes.push_back({rectX, rectY, rectW, rectH});
					}
				}
			}
		}
		
		vector<int> correctBoxesIDs;
		
		cvDNN::NMSBoxes(boxes, trusts, 0, NMS_THRESHOLD, correctBoxesIDs);
		
		for(const int ID : correctBoxesIDs)
		{
			cv::Rect box = boxes[ID];
			
			int w = box.width;
			int h = box.height;
			
			int x = box.x + (w / 2.0);
			int y = box.y + (h / 2.0);
			
			string type = typeNames[typeIDs[ID]];
			
			detections.push_back({x, y, w, h, type});
		}
	}
	
	return detections;
}