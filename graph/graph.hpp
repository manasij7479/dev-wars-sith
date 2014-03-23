#ifndef DWS_GRAPH_HPP
#define DWS_GRAPH_HPP

#include <vector>
#include <list>
#include <unordered_map>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <memory>

namespace dws
{

	//Sample EdgePolicies
	struct SimpleDigraph
	{
		static const bool multi = false;
		static const bool directed = true;
	};
	
	struct SimpleUndirectedGraph
	{
		static const bool multi = false;
		static const bool directed = false;
	};


	
	template <typename Vertex, typename Edge, typename EdgePolicy=SimpleDigraph>
	class AdjacencyList : private EdgePolicy
	{
		typedef std::list<std::pair<Vertex,Edge>> EdgeList;
		struct VertexData {Vertex v;EdgeList list;};
	public:
		bool isVertex(const Vertex& v)
		{
			return map.find(v)!=map.end();
		}
		std::size_t vi(Vertex v)
		{
			return map[v];
		}
		Vertex iv(std::size_t i)
		{
			return lists[i].v;
		}
		void insertVertex(const Vertex& v)
		{
			if(isVertex(v))return;
			map[v] = lists.size();
			lists.push_back({v,EdgeList()});
		}
		void removeVertex(const Vertex& v)
		{
			bool done = false;
			for(auto x = begin();x!=end();)
			{
				if(done)
					map[x->v]--;
				else if(x->v==v)
				{
					x=lists.erase(x);
					done=true;
					continue;
				}
				for(auto y = x->list.begin();y!=x->list.end();)
				{
					if(y->first == v)
					{
							y=x->list.erase(y);
							continue;
					}
					++y;
				}
				++x;
			}
		}
		void insertEdge(const Vertex& x,const Vertex& y,const Edge& e)
		{
			auto& list = getEdgeList(x);
			auto p = std::make_pair(y,e);
			auto it = std::find_if(list.begin(),list.end(),[&](std::pair<Vertex,Edge> v){return v.first==y;});
			
			if(it->second==e)
				return;
			
			if(it==list.end()||EdgePolicy::multi)
				list.push_back(p);
			else
				it->second = e;
			if(!EdgePolicy::directed)
				insertEdge(y,x,e);
		}
		void removeEdge(const Vertex& x,const Vertex& y,const Edge& e)
		{
			auto& list = getEdgeList(x);
			list.remove(std::make_pair(y,e));
			if(!EdgePolicy::directed)
			{
				list = getEdgeList(y);
				list.remove(std::make_pair(x,e));
			}
		}
		std::size_t size()
		{
			return lists.size();
		}
		
		typedef typename std::vector<VertexData>::iterator vertex_iterator;
		vertex_iterator begin(){return lists.begin();}
		vertex_iterator end(){return lists.end();}
		
		typedef typename EdgeList::iterator edge_iterator;
		edge_iterator nbegin(const Vertex& v){return getEdgeList(v).begin();}
		edge_iterator nend(const Vertex& v){return getEdgeList(v).end();}
		
		EdgeList& getEdgeList(const Vertex& v)
		{
			if(!isVertex(v))
				throw(std::runtime_error("Vertex absent in Graph.\n"));
			return lists[map[v]].list;
		}
		Edge& getEdge(const Vertex& x, const Vertex& y)
		{
			for(auto& elem:getEdgeList(x))
				if(elem.first==y)
					return elem.second;
			return *std::unique_ptr<Edge>();
		}
		
		std::size_t maxDegree()
		{
			int max=0;
			for(auto x=begin();x!=end();++x)
			{
				if(x->list.size()>max)
					max=x->list.size();
			}
			return max;
		}
		void display()
		{
			for(auto x = begin();x!=end();++x)
			{
				std::cout<<"["<<x->v<<"]->";
				for(auto y = nbegin(x->v);y!=nend(x->v);++y)
				{
					std::cout<<"("<< y->first<<","<< y->second<<"),";
				}
				std::cout<<"***\n";
			}
		}
		
	private:		
		std::vector<VertexData> lists; // The data for vertex v is stored in map[v] index of this list
		std::unordered_map<Vertex,std::size_t> map; 
		
	};
	
	typedef AdjacencyList<std::string,bool,SimpleUndirectedGraph> RebelGraph;
	
	
}
#endif
