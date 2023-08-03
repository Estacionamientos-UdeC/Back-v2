#ifndef SCANNER_H
#define SCANNER_H

#include "Types.hxx"

#include <fstream>
#include <sstream>

class Scanner
{
	public:
		Scanner(const string& source);
		~Scanner();
		
		inline void scan(const string& pattern, auto& var)
		{
			this -> find(pattern);
			
			this -> scanner >> var;
		}
		
		inline void scan(const string& pattern, vector<string>& vars)
		{
			this -> find(pattern);
			
			int size;
			this -> scanner >> size;
			
			vars.resize(size);
			
			for(string& var : vars)
			{
				this -> scanner.ignore(1e3, '\t');
				
				getline(this -> scanner, var);
			}
		}
	
	private:
		std::fstream scanner;
	
	private:
		void find(const string& pattern);
};

#endif