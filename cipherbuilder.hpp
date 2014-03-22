#ifndef DWS_CIPHER_BUILDER_HPP
#define DWS_CIPHER_BUILDER_HPP

#include "cipher.hpp"
namespace dws
{
	class CipherBuilder
	{
	public:
		CipherBuilder(std::string in):s(in){}
		Cipher& get(){return c;}
		
		void partition()
		{
			
			
			
			
		}
		
		
	private:
		Cipher c;
		std::string s;

	};
}
#endif
