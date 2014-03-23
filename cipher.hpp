#ifndef DWS_CIPHER_HPP
#define DWS_CIPHER_HPP

#include <stdexcept>
#include <algorithm>
#include <cctype>

namespace dws
{
	class Cipher
	{
	public:
		Cipher()
		{
			std::fill(map,map+26,0);
			std::fill(known,known+26,false);
			numknown=0;
		}
		Cipher(char m[26])
		{
			std::copy(m,m+26,map);
			std::fill(known,known+26,true);
			numknown=26;
		}
		void add(char a,char b)
		{
			a=std::tolower(a);
			b=std::tolower(b);
			
			if(!std::isalpha(a))
				return;
			if(known[a-'a'])
			{
				if(map[a-'a']==b)
					return;
				throw std::runtime_error("Inconsistent mapping");
			}
			map[a-'a']=b;
			known[a-'a']=true;
			numknown++;
		}
		void add(std::string a,std::string b)
		{
			for(int i=0;i<a.length();++i)
				add(a[i],b[i]);
		}
		Cipher invert()
		{
			if(numknown!=26)
				throw std::runtime_error("Can't invert incomplete map.");
			Cipher c;
			for(int i=0;i<26;++i)
				c.add(map[i],i+'a');
			return c;
		}
		std::string apply(std::string input)
		{
			std::string output;
			if(numknown!=26)
				throw std::runtime_error("Can't apply incomplete map.");
			for(int i=0;i<input.length();++i)
			{
				char x=std::tolower(input[i]);
				if(std::isalpha(x))
					output+=map[x-'a'];
				else output+=x;
			}
			return output;
		}
	private:
		char map[26];
		bool known[26];
		int numknown;
	};
	
	Cipher generateRandomCipher();
	
	
}
#endif