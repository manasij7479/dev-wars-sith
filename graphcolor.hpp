#ifndef DWS_GRAPH_COLOR_HPP
#define DWS_GRAPH_COLOR_HPP

#include "graph.hpp"
#include "graphutils.hpp"
#include <algorithm>
#include <iostream>
#include <unordered_map>

namespace dws
{
	class ColoredGraph
	{
	public:
		ColoredGraph(RebelGraph g_):g(g_)
		{
			std::vector<std::string> vlist;
			for(auto x=g.begin();x!=g.end();++x)
				vlist.push_back(x->v);
			
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
			{
				newmap[v]=0;
				//std::cout<<v<<' ';
			}
			//std::cout<<std::endl;
			int used=0;
			
			for(auto v:vlist)
			{
				for(int i=0;i<colors.size();++i)
				{
					int flag=1;
					for(auto x=g.nbegin(v);x!=g.nend(v);++x)
					{
						auto w=x->first;
						//std::cout<<w<<std::endl;
						if(newmap[w]==colors[i])
						{
							flag=0;
							break;
						}
					}
					if(flag==1)
					{
						newmap[v]=colors[i];
						if(i>=used)///FIXME
							used++;
						break;
					}
				}
			}
			if(used<chromatic_number)
			{
// 				std::cout<<chromatic_number;
				chromatic_number=used;
				colormap=newmap;
				best=vlist;
			}
		}
		void display()
		{
			for(auto x = g.begin();x!=g.end();++x)
			{
				std::cout<<"["<<x->v<<" @ "<<colormap[x->v]<<"]->";
				for(auto y = g.nbegin(x->v);y!=g.nend(x->v);++y)
				{
					std::cout<<"("<< y->first<<" @ "<< colormap[y->first]<<"),";
				}
				std::cout<<"***\n";
			}
		}
		std::unordered_map<std::string,int> getMap(){return colormap;}
	private:
		RebelGraph g;
		int chromatic_number;
		std::vector<int> colors;
		std::unordered_map<std::string,int> colormap;
		std::vector<std::string> best;
		
	};
}
#endif