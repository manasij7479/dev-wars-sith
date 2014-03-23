#include "analyzer.hpp"
namespace dws
{
	std::vector<std::string> sentences(std::string s)
	{
		std::istringstream in(s);
		std::vector<std::string> result;
		std::string line;
		while(std::getline(in,line,'.'))
			result.push_back(std::string(line+'.'));
		return result;
	}
	std::pair<std::string,std::string> split(std::string s)
	{
		std::istringstream in(s);
		std::pair<std::string,std::string> p;
		in>>p.first>>p.second;
		return p;
	}
	
	bool analogous(std::string a,std::string b)
	{
		std::istringstream x(a),y(b);
		std::string x_,y_;
		while(x>>x_ && y>>y_)
			if(x_.length()!=y_.length())
				return false;
		return true;
	}
	bool consistent(std::string a,std::string b)
	{
		///TODO
		return true;
	}
	
	Analyzer::Analyzer(std::string input,bool decrypted):s(input),done(false)
	{
		std::istringstream in(s);
		
		std::string nu;
		std::getline(in,nu);
// 			c.add(nu,"News Update");
		
		std::string msg;
		std::getline(in,msg);
		news=sentences(msg);
		
		if(decrypted)
			final_stage(in);
	}
	
	void Analyzer::final_stage(std::istringstream& in)
	{
		std::string line,blank;
		std::getline(in,blank);
		//assert(blank=="");
		
		std::string rb;
		std::getline(in,rb);
// 			c.add(rb,"Rebel Bases");
		while(std::getline(in,line))
		{
			if(line=="")
				break;
			else bases.push_back(line);
		}
		
		std::string cc;
		std::getline(in,cc);
// 			c.add(cc,"Communication Channels");
		while(std::getline(in,line))
		{
			if(line=="")
				break;
			else channels.push_back(split(line));
		}
		
		std::string ms;
		std::getline(in,ms);
// 			c.add(rb,"Messages");
		while(std::getline(in,line))
		{
			if(line=="")
				break;
			else messages.push_back(line);
		}
		done=true;
	}
	
	
	Cipher Analyzer::getCipher()
	{
		Cipher c;
		std::string k="The quick brown fox jumps over the lazy dog.";
		std::string m;
		for(auto& s:news)
		{
			if(analogous(s,k))
			{
				m=s;
				break;
			}
		}
		if(m=="")
			throw std::runtime_error("No match.");
		
		if(m[0]==' ')
			m=m.substr(1,m.length()-1);

		c.add(k,m);
		
		return c;
	}
	RebelGraph Analyzer::getGraph()
	{
		auto vlist=getBases();
		auto elist=getChannels();
		RebelGraph rb;
		
		for(auto v:vlist)
			rb.insertVertex(v);
	
		for(auto e:elist)
			rb.insertEdge(e.first,e.second,true);
	
		return rb;
	}
	
	
}