#include "rebuild.hpp"
#include <sstream>
#include <cctype>
#include "cipher.hpp"

namespace dws
{
	std::string messages[]=
	{
		"Dummy",
		"Attack",
		"Retreat",
		"Stay",
		"Self Destruct",
		"Hide",
		"Repair",
	};
	
	std::string scase(std::string x)
	{
		if(x[0]==' ')
			x[1]=std::toupper(x[1]);
		else
			x[0]=std::toupper(x[0]);
		return x;
	}
	std::string rebuildMessage(Analyzer& an,ColoredGraph& g,bool includecols)
	{
		std::ostringstream out;
		out<<"News Update\n";
		for(auto x:an.getNews())
			out<<scase(x);
		out<<"\n";
		out<<"\n";
		
		out<<"Rebel Bases\n";
		for(auto x:an.getBases())
			out<<scase(x)<<"\n";
		out<<"\n";
		out<<"Communication Channels\n";
		if(includecols)
			for(auto p:an.getChannels())
				out<<scase(p.first)<<'('<<g.getMap()[p.first]<<") "
				<<scase(p.second)<<'('<<g.getMap()[p.second]<<")\n";
		else
			for(auto p:an.getChannels())
				out<<scase(p.first)<<' '<<scase(p.second)<<"\n";
		out<<"\n";
		out<<"Messages\n";
		for(auto v:an.getBases())
			out<<messages[g.getMap()[v]]<<std::endl;
		return out.str();
	}
}