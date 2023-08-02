#include "Scanner.hxx"

Scanner::Scanner(const string& source)
{
	this -> scanner.open(source.c_str());
	
	if(!this -> scanner.is_open())
		exit(0);
}

Scanner::~Scanner()
{
	this -> scanner.close();
}

void Scanner::find(const string& pattern)
{
	this -> scanner.seekg(0);
	
	string aux;
	
	while(this -> scanner >> aux)
	{
		if(aux == pattern)
			return;
	}
}