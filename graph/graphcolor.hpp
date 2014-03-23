#ifndef DWS_GRAPH_COLOR_HPP
#define DWS_GRAPH_COLOR_HPP

#include "graph.hpp"
#include <algorithm>
#include <iostream>
#include <unordered_map>

namespace dws
{
	class ColoredGraph
	{
	public:
		ColoredGraph(){}
		ColoredGraph(RebelGraph g_);
		
		void display();
		
		std::unordered_map<std::string,int> getMap(){return colormap;}
		RebelGraph getGraph(){return g;}
	private:
		RebelGraph g;
		int chromatic_number;
		std::vector<int> colors;
		std::unordered_map<std::string,int> colormap;
		std::vector<std::string> best;
		
		void update(std::vector<std::string>& vlist);
		
		
	};
}
#endif