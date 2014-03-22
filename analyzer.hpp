#ifndef DWS_ANALYZER_HPP
#define DWS_ANALYZER_HPP
#include <iostream>
#include <cassert>
namespace dws 
{
	std::vector<std::string> sentences(std::string s)
	{
		std::istringstream in(s);
		std::vector<std::string> result;
		std::string line;
		while(std::getline(in,line,'.'))
			result.push_back(std::string(line+'.'));
		return result;
	}
	std::pair<std::string,std::string> split(std::string s)
	{
		std::istringstream in(s);
		std::pair<std::string,std::string> p;
		in>>p.first>>p.second;
		return p;
	}
	
	
	class Analyzer
	{
	public:
		Analyzer(std::string in):s(in)
		{
			std::istringstream in(s);
			std::string line,blank;
			
			std::string nu;
			std::getline(in,nu);
// 			c.add(nu,"News Update");
			
			std::string msg;
			std::getline(in,msg);
			news=sentences(msg);
			
			std::getline(in,blank);
			assert(blank=="");
			
			std::string rb;
			std::getline(in,rb);
// 			c.add(rb,"Rebel Bases");
			while(std::getline(in,line))
			{
				if(line=="")
					break;
				else bases.push_back(line);
			}
			
			std::string cc;
			std::getline(in,cc);
// 			c.add(cc,"Communication Channels");
			while(std::getline(in,line))
			{
				if(line=="")
					break;
				else channels.push_back(split(line));
			}
			
			std::string ms;
			std::getline(in,ms);
// 			c.add(rb,"Messages");
			while(std::getline(in,line))
			{
				if(line=="")
					break;
				else messages.push_back(line);
			}
		}
		
		
	private:
		std::string s;
		std::vector<std::string> news;
		std::vector<std::string> bases;
		std::vector<std::pair<std::string,std::string>> channels;
		std::vector<std::string> messages;
	};
}
#endif