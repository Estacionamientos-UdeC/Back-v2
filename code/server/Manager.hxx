#ifndef MANAGER_H
#define MANAGER_H

#include "Types.hxx"
#include "Camera.hxx"
#include "Detector.hxx"

class Manager
{
	public:
		Manager(const string& settings);
		
		void run();
	
	private:
		int frequency;
		
		int emptySpaces;
		int totalSpaces;
		
		Detector detector;
		
		set<string> tags;
		vector<Camera> cameras;
	
	private:
		void count();
};

#endif