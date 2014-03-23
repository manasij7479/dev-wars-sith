#include "cipher.hpp"
namespace dws
{
	Cipher generateRandomCipher()
	{
		Cipher c;
		char arr[26];
		for(int i=0;i<26;++i)
			arr[i]='a'+i;
		std::random_shuffle(arr,arr+26);
		
		return Cipher(arr);
	}
}