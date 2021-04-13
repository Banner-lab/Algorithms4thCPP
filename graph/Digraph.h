//
// Created by leexm on 2021/4/13.
//

#ifndef KAOYAN_DIGRAPH_H
#define KAOYAN_DIGRAPH_H

#include <vector>

class Digraph{
    private:
        std::vector<std::vector<int>>   adj;
        int edges;
        int vertex;
    public:
        Digraph(int n){
            adj.resize(n,std::vector<int>());
            edges=0;
            vertex=n;
        }

        void addEdge(int v,int w){
            adj[v].push_back(w);
            edges++;
        }

        int V(){
            return vertex;
        }

        int E(){
            return edges;
        }

        std::vector<int> Adj(int v){
            return adj[v];
        }
};

#endif //KAOYAN_DIGRAPH_H
