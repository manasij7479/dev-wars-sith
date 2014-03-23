#include "shell.hpp"
int main(int argc,char** argv)
{
	dws::Shell shell(argc,argv);
	return shell();
}