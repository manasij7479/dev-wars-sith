#ifndef DWS_REBUILD_HPP
#define DWS_REBUILD_HPP

#include "../graph/graphcolor.hpp"
#include "analyzer.hpp"

namespace dws
{
	std::string rebuildMessage(Analyzer& an,ColoredGraph& g,bool includecols=true);
}


#endif