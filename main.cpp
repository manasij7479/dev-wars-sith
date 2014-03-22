#include<iostream>
#include "cipher.hpp"
#include "analyzer.hpp"
#include "graph.hpp"
#include "graphutils.hpp"
#include "graphcolor.hpp"
int main()
{
	//dws::Cipher c=dws::generateRandomCipher();
	std::string line;
	std::string input;
	while(std::getline (std::cin,line))
		input+=(line+'\n');
	
	dws::Analyzer an(input);
	
	dws::Cipher c=an.getCipher().invert();
	
	std::string output=c.apply(input);
	std::cout<<output;
	
	
	dws::Analyzer an_(output,true);
	auto g=dws::makeGraph(an_);
	
	dws::darthGraphDisplay(g,std::cout);
	dws::ColoredGraph g_(g,an_);
	
	g_.display();
	
	
	return 0;
	
	
	
}