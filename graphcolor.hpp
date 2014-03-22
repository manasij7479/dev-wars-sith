#ifndef DWS_GRAPH_COLOR_HPP
#define DWS_GRAPH_COLOR_HPP

#include "graph.hpp"
#include "graphutils.hpp"
#include "analyzer.hpp"
#include <algorithm>
#include <iostream>
#include <unordered_map>

namespace dws
{
	class ColoredGraph
	{
	public:
		ColoredGraph(RebelGraph g_,Analyzer& an):g(g_)
		{
			auto vlist=an.getBases();
			
			chromatic_number=g.size();
			for(int i=1;i<=g.size();++i)
				colors.push_back(i);
			
			std::sort(vlist.begin(),vlist.end());			
			do
			{
				update(vlist);
			}while(std::next_permutation(vlist.begin(),vlist.end()));
		}
		void update(std::vector<std::string>& vlist)
		{
			std::unordered_map<std::string,int> newmap;
			for(auto v:vlist)
				newmap[v]=0;
			int used=0;
			int flag;
			for(auto v:vlist)
			{
				for(int i=0;i<colors.size();++i)
				{
					for(auto x=g.nbegin(v);x!=g.nbegin(v);++x)
					{
						auto w=x->first;
						if(newmap[w]==colors[i])
						{
							flag=0;
							break;
						}
						else flag=1;
					}
					if(flag==1)
					{
						newmap[v]=colors[i];
						if(i>used)
							used=i;
						break;
					}
				}
			}
			if(used<chromatic_number)
			{
				chromatic_number=used;
				colormap=newmap;
				best=vlist;
			}
		}
		void display()
		{
			for(auto v:best)
			{
				std::cout<<v<<':'<<colormap[v]<<std::endl;
			}
		}
	private:
		RebelGraph g;
		int chromatic_number;
		std::vector<int> colors;
		std::unordered_map<std::string,int> colormap;
		std::vector<std::string> best;
		
	};
}
#endif