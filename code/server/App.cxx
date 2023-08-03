#include "Manager.hxx"

#include <iostream>

#define scanner std::cin
#define printer std::cout

int main()
{
	string settings = "./content/settings/manager/";
	
	{
		string aux;
		
		printer << "settings: " << settings;
		scanner >> aux;
		
		settings += aux;
	}
	
	Manager manager(settings);
	
	manager.run();
}