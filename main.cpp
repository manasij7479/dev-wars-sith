#include<iostream>
#include "cipher.hpp"
#include "analyzer.hpp"
int main()
{
	dws::Cipher c=dws::generateRandomCipher();
	std::string line;
	std::string input;
	while(std::getline (std::cin,line))
		input+=(line+'\n');
	
	
	
	return 0;
}