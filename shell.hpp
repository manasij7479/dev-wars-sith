#ifndef DWS_SHELL_HPP
#define DWS_SHELL_HPP
#include <iostream>
namespace dws
{
	class Shell
	{
	public:
		Shell()
		{
			std::cout<<"Init-ascii art goes here\n";
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
		std::string current_file;
	};
}

#endif