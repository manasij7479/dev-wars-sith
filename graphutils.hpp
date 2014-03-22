#ifndef DWS_GRAPH_UTILS_HPP
#define DWS_GRAPH_UTILS_HPP
#include <algorithm>
#include "graph.hpp"
#include "analyzer.hpp"
namespace dws
{
	
	typedef AdjacencyList<std::string,bool,SimpleUndirectedGraph> RebelGraph;
	
	template<typename Graph>
	void darthGraphDisplay(Graph& g,std::ostream& out)
	{
		for(auto x = g.begin();x!=g.end();++x)
		{
			out<<"["<<x->v<<"]->";
			for(auto y = g.nbegin(x->v);y!=g.nend(x->v);++y)
			{
				out<<"("<< y->first<<","<< y->second<<")->";
			}
			out<<"***\n";
		}
	}
	
	
	RebelGraph makeGraph(Analyzer& an)
	{
		auto vlist=an.getBases();
		auto elist=an.getChannels();
		RebelGraph rb;
		
		for(auto v:vlist)
			rb.insertVertex(v);
		
		for(auto e:elist)
			rb.insertEdge(e.first,e.second,true);
		
		return rb;
	}
	
	
}
#endif