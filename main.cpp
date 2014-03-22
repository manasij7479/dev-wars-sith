#include<iostream>
#include "cipher.hpp"
int main()
{
	dws::Cipher c=dws::generateRandomCipher();
	std::cout<<c.invert().apply(c.apply("Manasij"));
}