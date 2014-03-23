#ifndef DWS_SHELL_HPP
#define DWS_SHELL_HPP

#include "analyzer.hpp"
#include "graph.hpp"
#include "graphcolor.hpp"

namespace dws
{
	class Shell
	{
	public:
		Shell(int argc,char** argv);
		int non_interactive();
		int operator()();
	private:
		void generate();
		
		std::string original_data;
		std::string decrypted_data;
		std::string final_data;
		std::string current_file_name;
		
		Analyzer an;
		RebelGraph g;
		ColoredGraph cg;
		Cipher c;
		bool interactive;

	};
}

#endif