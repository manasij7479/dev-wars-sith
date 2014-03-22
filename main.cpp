#include<iostream>
#include "cipher.hpp"
#include "analyzer.hpp"
int main()
{
	//dws::Cipher c=dws::generateRandomCipher();
	std::string line;
	std::string input;
	while(std::getline (std::cin,line))
		input+=(line+'\n');
	
	dws::Analyzer an(input);
	dws::Cipher c=an.getCipher().invert();
	
	std::cout<<c.apply(input);
	
	
	return 0;
}