//
// Created by leexm on 2021/4/11.
//

#ifndef KAOYAN_WEIGHTDIRECTGRAPH_H
#define KAOYAN_WEIGHTDIRECTGRAPH_H

#include "DirectedEdge.h"
#include <vector>


class WeightDirectGraph{
    private:
        int vertex;
        int edges;
        double totalWeight;
        std::vector<std::vector<DirectiedEdge>> adj;
    public:
        WeightDirectGraph(int n):vertex(n),edges(0){
            totalWeight=0.0l;
            adj.resize(n,std::vector<DirectiedEdge>());
        }

        int V(){
            return vertex;
        }

        int E(){
            return edges;
        }

        void add_edge(int v,int w,double val){
            DirectiedEdge e(v,w,val);
            adj[v].push_back(e);
            edges++;
        }

        std::vector<DirectiedEdge> Adj(int v){
            return adj[v];
        }

};


#endif //KAOYAN_WEIGHTDIRECTGRAPH_H
