//
// Created by leexm on 2021/4/7.
//

#ifndef KAOYAN_WEIGHTGRAPH_H
#define KAOYAN_WEIGHTGRAPH_H

#include <vector>
#include <iostream>
#include "Edge.h"
#include <string>
#include <fstream>
#include <sstream>
#include <set>
using namespace std;

class WeightGraph{
    private:
        vector<vector<Edge>> adj;
        int vertex;
        int edges;


    public:
        WeightGraph(int v){
           adj.resize(v,vector<Edge>());
           vertex=v;
           edges=0;
        }

        void add_edge(int v,int w,double wei){
            Edge e(v,w,wei);
            adj[v].push_back(e);
            adj[w].push_back(e);
            edges++;
        }

        int E(){
            return edges;
        }

        int V(){
            return vertex;
        }

        vector<Edge> Adj(int v){
            return adj[v];
        }

        set<Edge> Edges(){
            set<Edge> res;
            for(int i=0;i<vertex;i++)
                for(Edge e:adj[i])
                    res.insert(e);
            return res;
        }
};
#endif //KAOYAN_WEIGHTGRAPH_H
