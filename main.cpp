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
	
// 	std::cout<<input;
	
	dws::Analyzer an(input);
	
	for(auto x:an.news)
		std::cout<<x<<std::endl;
	
	for(auto x:an.bases)
		std::cout<<x<<std::endl;
	
	for(auto x:an.messages)
		std::cout<<x<<std::endl;
	
	
	return 0;
}