#ifndef DWS_ANALYZER_HPP
#define DWS_ANALYZER_HPP
#include <iostream>
#include <stdexcept>
#include <sstream>
#include "cipher.hpp"
#include "graph.hpp"
namespace dws 
{
	
	class Analyzer
	{
	public:
		Analyzer(){}
		Analyzer(std::string input,bool decrypted=false);
		
		void final_stage(std::istringstream& in);
		Cipher getCipher();
		RebelGraph getGraph();
		
		std::vector<std::string> getBases(){return bases;};
		std::vector<std::pair<std::string,std::string>> getChannels(){return channels;};
		std::vector<std::string> getNews(){return news;};
	private:
		std::string s;
		std::vector<std::string> news;
		std::vector<std::string> bases;
		std::vector<std::pair<std::string,std::string>> channels;
		std::vector<std::string> messages;
		
		bool done;
	};
}
#endif