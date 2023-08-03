#include "Scanner.hxx"
#include "Manager.hxx"

#include <chrono>

// {
#include <fstream>
#include <iostream>
// }

Manager::Manager(const string& settings)
{
	Scanner scanner(settings);
	
	scanner.scan("FREQUENCY:", this -> frequency);
	
	scanner.scan("EMPTY_SPACES:", this -> emptySpaces);
	scanner.scan("TOTAL_SPACES:", this -> totalSpaces);
	
	{
		string settings;
		
		scanner.scan("DETECTOR:", settings);
		
		this -> detector = Detector(settings);
	}
	
	{
		vector<string> names;
		vector<string> sources;
		
		scanner.scan("CAMERA_NAMES:", names);
		scanner.scan("CAMERA_SOURCES:", sources);
		
		for(int i = 0; i < names.size(); i++)
		{
			string name = names[i];
			string source = sources[i];
			
			this -> cameras.push_back(Camera(name, source));
		}
	}
	
	this -> tags = {"car", "truck"};
}

void Manager::run()
{
	using namespace std::chrono;
	using timer = std::chrono::high_resolution_clock;
	
	time_point time1 = timer::now();
	time_point time2 = timer::now();
	
	while(true)
	{
		time2 = timer::now();
		
		if(duration_cast<seconds>(time2 - time1).count() >= this -> frequency)
		{
			this -> count();
			
			time1 = time2;
		}
	}
}

void Manager::count()
{
	int carCount = 0;
	
	for(Camera& camera : this -> cameras)
	{
		// {
		std::cout << camera.getName() << ": ";
		// }
		
		vector<BBox> detections = this -> detector.detect(camera.scanImage());
		
		for(const BBox& detection : detections)
		{
			// {
			std::cout << detection.tag << ' ';
			// }
			
			if(this -> tags.contains(detection.tag))
				carCount++;
		}
		
		// {
		std::cout << '\n';
		// }
	}
	
	this -> emptySpaces = this -> totalSpaces;
	this -> emptySpaces -= carCount;
	
	// {
	std::fstream status("./content/status/status.txt");
	
	status << this -> emptySpaces;
	// }
}