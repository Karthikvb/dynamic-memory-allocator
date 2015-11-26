#include <iostream>
#include <list>
#include <map>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <stdlib.h>
#include <ctype.h>
#include <cstdlib>

#define MAX_CHARS 1024

bool compare(const std::string& a, const std::string& b) { 
    	int x = std::stoi(a.substr(1, a.length()));
    	int y = std::stoi(b.substr(1, b.length()));
    	return x < y;
  }

class graph {
	int V;
	std::map<std::string, std::list<std::string> > adj;
public:
	graph(int u);
	void addEdge(std::string u, std::string v);
	std::vector<std::string> search(std::string u);
	std::list<std::string> getVertices();
};

graph::graph(int V) {
	this->V  = V;
}

std::list<std::string> graph::getVertices() {
	std::list<std::string> list;
	std::map<std::string, std::list<std::string> >::iterator it = adj.begin();
	while (it != adj.end()) {
		list.push_back(it->first);
		//std::cout<<it->first;
		it++;
	}
	return list;
}

void graph::addEdge(std::string u, std::string v) {
	//std::cout<<"Adding edge from "<<u<<" to "<<v<<std::endl;
	std::map<std::string, std::list<std::string> >::iterator it = adj.find(u);
	if (it == adj.end()) {
		std::list<std::string> list;
		list.push_back(v);
		adj[u] = list;
	} else {
		adj[u].push_back(v);
	}
}

std::vector<std::string> graph::search(std::string u)
{
	int N = 0;

	//std::cout<<"BFS"<<std::endl;
	std::map<std::string, bool> hashMap;
	std::map<std::string, bool> hashMap1;
	
    std::list<std::string> bfsqueue;
 
    hashMap[u] = true;
    bfsqueue.push_back(u);
    //std::cout<<u<<",";

    std::list<std::string> l = getVertices();
    std::list<std::string>::iterator it;
    for (it = l.begin();
    	it != l.end();
    	it++) {
    	hashMap1[*it] = false;
    }
 
    std::list<std::string>::iterator i;
    hashMap1[u] = true;
 
    while(!bfsqueue.empty())
    {
        u = bfsqueue.front();
        //std::cout << u << " ";
        bfsqueue.pop_front();

        for(i = adj[u].begin(); i != adj[u].end(); ++i)
        {
        	
        	std::map<std::string, bool>::iterator it = hashMap.find(*i);
            if(it == hashMap.end())
            {
            	hashMap1[*i] = !hashMap1[u];
                hashMap[*i] = true;
                bfsqueue.push_back(*i);
            }
        }
    }
    //std::cout<<std::endl;
    std::vector<std::string> result;
    for (std::map<std::string, bool>::iterator it = hashMap1.begin();
    	it != hashMap1.end();
    	it++) {
    	if (it->second && !adj[it->first].empty()) {
    		result.push_back(it->first);
    		N++;
    	}
    }
    std::sort(result.begin(), result.end(), compare);

    return result;
}

int main() {

	std::ifstream is;
	is.open("input.txt");

	if (!is.good()) {
		return 1;
	}

	char buf[MAX_CHARS];
	is.getline(buf, MAX_CHARS);
	int V = atoi(buf);
	graph g(V);

	std::string delimiter = "->";
	std::string startVertex;

	int i = 0;
	while (i < V && !is.eof()) {
		i++;
		char buf[MAX_CHARS];
		is.getline(buf, MAX_CHARS);

		size_t pos = 0;
		std::string token;
		std::string s = buf;
		std::string u;

		if ((pos = s.find(delimiter)) != std::string::npos) {
			token = s.substr(0, pos);
			u = token;
			//std::cout<<token<<"->";
			s.erase(0, pos+delimiter.length());
			startVertex = token;
		} else {
			startVertex = s;
			std::string temp;
			g.addEdge(startVertex, temp);
			//std::cout<<s<<std::endl;
			continue;
		}
		while ((pos = s.find(delimiter)) != std::string::npos) {
			token = s.substr(0, pos);
			g.addEdge(startVertex, token);
			//std::cout<<token<<"->";
			s.erase(0, pos+delimiter.length());
		}
		g.addEdge(startVertex, s);
		//std::cout<<s<<std::endl;
	}

	std::ofstream os;
	os.open("output.txt");

	if (!is.eof()) {
		char buf1[MAX_CHARS];
		is.getline(buf1, MAX_CHARS);
		//std::cout<<buf1<<std::endl;
		std::vector<std::string> result  = g.search(buf1);
		//std::cout<<result.size()<<std::endl;
		os<<result.size()<<std::endl;
		int i;
		for (i = 0; i < result.size()-1; i++) {
			//std::cout<<result[i]<<",";
			os<<result[i]<<",";
		}
		os<<result[i]<<std::endl;
		//std::cout<<result[i]<<std::endl;
	}

	is.close();
	os.close();
}
