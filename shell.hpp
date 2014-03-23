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
	
	std::string fileInput(std::string input)
	{
			std ::string result ;
			std::ifstream in(input);
			std::string line;
			while(std::getline(in,line))
				result+=(line+'\n');	
			return result;
	}
	
	std::string decrypt(std::string input)
	{
		Analyzer an(input);
		Cipher c=an.getCipher().invert();
		return c.apply(input);
	}
	
	void display_help()
	{
		std::cout<<"Help text goes here.\n";
	}
	void display_ascii_art()
	{
		std::cout<<"Init-ascii art goes here\n";
	}
	bool prompt()
	{
		std::cout<<"$";
		return true;
	}
	class Shell
	{
	public:
		Shell()
		{
			
		}
		Shell(int argc,char** argv)
		{
			if(argc<2)
			{
				display_ascii_art();
				interactive=true;
			}
			else
			{
				interactive=false;
				current_file_name=argv[1];
			}
// 			std ::string input;
// 			std::ifstream in(argv[1]);
// 			std::string line;
// 			while(std::getline(in,line))
// 				input+=(line+'\n');
// 			
// 			dws::Analyzer an(input);
// 			
// 			dws::Cipher c=an.getCipher().invert();
// 			
// 			std::string output=c.apply(input);
// 			std::cout<<"\n##Plaintext##\n";
// 			std::cout<<output;
// 			
// 			
// 			dws::Analyzer an_(output,true);
// 			auto g=an_.getGraph();
// 			std::cout<<"\n##Graph##\n";
// 			g.display();
// 			dws::ColoredGraph g_(g);
// 			
// 			std::cout<<"\n##Coloured Graph##\n";
// 			g_.display();
// 			
// 			std::cout<<"\n##Rebuilt Message##\n";
// 			std::cout<<rebuildMessage(an_,g_);
		
			
		}
		
		int non_interactive()
		{
			original_data=fileInput(current_file_name);
			generate();
			//decrypted_data=decrypt(original_data);
			std::cout<<decrypted_data;
			//an=Analyzer(decrypted_data,true);
			//g=an.getGraph();
			g.display();
			//cg=ColoredGraph(g);
			cg.display();
			//final_data=rebuildMessage(an,cg);
			std::cout<<final_data;
			
		}
		int operator()()
		{
			if(interactive)
			{
				std::string input;
				while(prompt()&&std::getline(std::cin,input))
				{
					if(input=="")
						continue;
					
					if(input[0]=='l')
					{
						std::istringstream in(input);
						std::string load,name;
						in>>load>>name;
						original_data=fileInput(name);
						
						decrypted_data="";
						final_data="";
						
					}
					if(input[0]=='d')
					{
						generate();
						std::cout<<"Decrypted Data:\n"<<decrypted_data<<std::endl;
					}
					if(input[0]=='g')
					{
						if(decrypted_data=="")generate();
						std::cout<<"Graph of Rebel Bases:\n";
						g.display();
						std::cout<<std::endl;
					}
					if(input[0]=='c')
					{
						if(decrypted_data=="")generate();
						std::cout<<"Coloured Graph of Rebel Bases:\n";
						cg.display();
						std::cout<<std::endl;
					}
					if(input[0]=='r')
					{
						if(decrypted_data=="")generate();
						std::cout<<"Message to be re-transmitted:\n"<<final_data<<std::endl;
					}
					if(input[0]=='q')
						break;
					if(input[0]=='h')
						display_help();
				}
				return 1;
			}
			else return non_interactive();
		}
	private:
		void generate()
		{
			decrypted_data=decrypt(original_data);
			an=Analyzer(decrypted_data,true);
			g=an.getGraph();
			cg=ColoredGraph(g);
			final_data=rebuildMessage(an,cg);
		}
		
		std::string original_data;
		std::string decrypted_data;
		std::string final_data;
		std::string current_file_name;
		
		Analyzer an;
		RebelGraph g;
		ColoredGraph cg;
		
		bool interactive;
		
		
	};
}

#endif