#include "shell.hpp"

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include "../text/rebuild.hpp"


namespace dws
{
	std::string fileInput(std::string input)
	{
			std ::string result ;
			std::ifstream in(input);
			if(!in)
				throw std::runtime_error("File "+input+" not found.\n");
			std::string line;
			while(std::getline(in,line))
				result+=(line+'\n');	
			return result;
	}
	void fileOutput(std::string name,std::string data)
	{
		std::ofstream out(name);
		if(!out)
				throw std::runtime_error("File "+data+" not found.\n");
		out<<data;
	}
	Cipher decrypt(std::string input)
	{
		Analyzer an(input);
		Cipher c=an.getCipher().invert();
		return c;
	}
	
	void display_help()
	{
		std::cout<<
"The operations supported are:  \n\
  1. load filename : File 'filename' containing the encrypted text is loaded.\n\
  2. decrypt: Decrypts the file and displays the plaintext.\n\
  3. graph: Shows a graph denoting the communication channels between the rebel bases.\n\
  4. color: Shows the same graph, but numbers(traditionally called colors) are appended\n\
  to them in such a way that no two adjacent base has the same color.\n\
  5. rebuild (optional filename): Reconstructs the message in such a way \n\
  that no two adjacent rebel bases recieve the same message.\n\
  If a filename is provided, the text is re-encrypted and saved in the given file.\n\
  6. help: Displays this message \n\
  7. quit: Ends the application\n";
	}
	void display_ascii_art()
	{
		std::ifstream in("../shell/ascii.txt");
		if(in)
			std::cout<<in.rdbuf();
		std::cout<<"\n\t\t    ***Death Star Control System***\n";
	}
	bool prompt()
	{
		std::cout<<"$";
		return true;
	}
	
	Shell::Shell(int argc,char** argv)
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
		
	}
	
	int Shell::non_interactive()
	{
		original_data=fileInput(current_file_name);
		generate();
		std::cout<<decrypted_data<<std::endl;
		g.display();
		cg.display();
		std::cout<<final_data<<std::endl;
		std::cout<<c.invert().apply(rebuildMessage(an,cg,false));
	}
	
	int Shell::operator()()
	{
		if(interactive)
		{
			std::string input;
			
			while(prompt()&&std::getline(std::cin,input))
			{
				try
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
						std::cout<<"File '"<<name<<"' loaded.\n";
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
						
						std::istringstream in(input);
						std::string r,name;
						in>>r;
						if(in>>name)
							fileOutput(name,c.invert().apply(rebuildMessage(an,cg,false)));
						
					}
					if(input[0]=='q')
						break;
					if(input[0]=='h')
						display_help();
					
				}
				catch(const std::exception& e)
				{
				std::cerr<<e.what()<<std::endl;
				}
			}
			return 0;
		
			
		}
		else return non_interactive();
	}
	void Shell::generate()
	{
		c=decrypt(original_data);
		decrypted_data=c.apply(original_data);
		an=Analyzer(decrypted_data,true);
		g=an.getGraph();
		cg=ColoredGraph(g);
		final_data=rebuildMessage(an,cg);
	}
	
}