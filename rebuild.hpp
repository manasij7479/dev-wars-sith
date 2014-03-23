#ifndef DWS_REBUILD_HPP
#define DWS_REBUILD_HPP
#include "graph.hpp"
#include "graphcolor.hpp"
#include "cipher.hpp"
#include "analyzer.hpp"

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
		"Repair"
	};
	std::string rebuildMessage(Analyzer& an,ColoredGraph& g)
	{
		std::string out;
		///TODO
		return out;
	}
}


#endif