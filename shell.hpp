#ifndef DWS_SHELL_HPP
#define DWS_SHELL_HPP
#include <iostream>
#include <stdexcept>
#include <fstream>
#include "cipher.hpp"
#include "analyzer.hpp"
#include "graph.hpp"
#include "graphutils.hpp"
#include "graphcolor.hpp"
#include "rebuild.hpp"
namespace dws
{
	class Shell
	{
	public:
		Shell()
		{
			std::cout<<"Init-ascii art goes here\n";
		}
		Shell(int argc,char** argv)
		{
			if(argc!=2)
				throw std::runtime_error("Wrong args");
			
			std ::string input;
			std::ifstream in(argv[1]);
			std::string line;
			while(std::getline(in,line))
				input+=(line+'\n');
			
			dws::Analyzer an(input);
			
			dws::Cipher c=an.getCipher().invert();
			
			std::string output=c.apply(input);
			std::cout<<"\n##Plaintext##\n";
			std::cout<<output;
			
			
			dws::Analyzer an_(output,true);
			auto g=dws::makeGraph(an_);
			std::cout<<"\n##Graph##\n";
			dws::darthGraphDisplay(g,std::cout);
			dws::ColoredGraph g_(g);
			
			std::cout<<"\n##Coloured Graph##\n";
			g_.display();
			
			std::cout<<"\n##Rebuilt Message##\n";
			std::cout<<rebuildMessage(an_,g_);
		
			
		}
		bool prompt()
		{
			std::cout<<"$";
			return true;
		}
		int operator()()
		{
			std::string input;
			while(prompt()&&std::getline(std::cin,input))
			{
				if(input=="")
					continue;
				
				if(input[0]=='l')
				{
					load_handler(input);
				}
				if(input[0]=='d')
				{
					display_handler(input);
				}
				if(input[0]=='r')
				{
					recrypt_handler(input);
				}
				
			}
			return 1;
		}
	private:
		void load_handler(std::string in)
		{
			
		}
		void display_handler(std::string in)
		{
			
		}
		void recrypt_handler(std::string in)
		{
			
		}
		std::string original_data;
		std::string decrypted_data;
		std::string final_data;
		std::string current_file_name;
		
	};
}

#endif