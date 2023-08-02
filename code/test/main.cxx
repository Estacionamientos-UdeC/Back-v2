#include "Manager.hxx"

#include <iostream>

using namespace std;

int main()
{
	string settings;
	cin >> settings;
	
	Manager manager(settings);
	
	manager.run();
}