#include "Scanner.hxx"
#include "Detector.hxx"

#include <opencv2/imgcodecs.hpp>

Detector::Detector()
{
}

Detector::Detector(const string& settings)
{
	Scanner scanner(settings);
	
	scanner.scan("MIN_SCORE:", this -> minScore);
	scanner.scan("MIN_TRUST:", this -> minTrust);
	
	{
		string network;
		
		scanner.scan("NETWORK:", network);
		
		this -> network = cvDNN::readNet(network);
	}
	
	scanner.scan("TAGS:", this -> tags);
}

vector<BBox> Detector::detect(const vector<uInt8>& image)
{
	const int IMAGE_W = 640;
	const int IMAGE_H = 640;
	
	const int NMS_THRESHOLD = 0.5;
	
	cv::Mat imageMatrix = cv::imdecode(image, cv::IMREAD_UNCHANGED);
	
	/* ----- */
	
	cv::Mat inferences;
	{
		cv::Mat BLOB = cvDNN::blobFromImage(imageMatrix, 1.0 / 255.0, cv::Size(IMAGE_W, IMAGE_H), cv::Scalar(), true, false);
		
		vector<cv::Mat> results;
		
		this -> network.setInput(BLOB);
		this -> network.forward(results, this -> network.getUnconnectedOutLayersNames());
		
		inferences = results[0].reshape(0, {results[0].size[1], results[0].size[2]});
	}
	
	/* ----- */
	
	vector<BBox> detections;
	{
		vector<int> tagIDs;
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
					int tagID;
					double score;
					{
						cv::Mat scores = inferences(cv::Range(row, row + 1), cv::Range(5, inferences.cols));
						cv::Point ID;
						
						cv::minMaxLoc(scores, 0, &score, 0, &ID);
						
						tagID = ID.x;
					}
					
					if(score >= this -> minScore)
					{
						trusts.push_back(trust);
						tagIDs.push_back(tagID);
						
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
		
		/* ----- */
		
		vector<int> correctBoxesIDs;
		
		cvDNN::NMSBoxes(boxes, trusts, 0, NMS_THRESHOLD, correctBoxesIDs);
		
		for(const int ID : correctBoxesIDs)
		{
			cv::Rect box = boxes[ID];
			
			int w = box.width;
			int h = box.height;
			
			int x = box.x + (w / 2.0);
			int y = box.y + (h / 2.0);
			
			string tag = this -> tags[tagIDs[ID]];
			
			detections.push_back({x, y, w, h, tag});
		}
	}
	
	return detections;
}