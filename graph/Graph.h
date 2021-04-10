//
// Created by leexm on 2021/4/10.
//

#ifndef KAOYAN_GRAPH_H
#define KAOYAN_GRAPH_H

#include <iostream>
#include <vector>
#include <queue>

using namespace  std;

class Graph {
    private:
        int vertex;
        int edges;
        vector<vector<int>> adj;


    public:
        Graph(int n){
            adj.resize(n,vector<int>());
            vertex=n;
            edges=0;
        }

        void add_edge(int v,int w){
            adj[v].push_back(w);
            adj[w].push_back(v);
            edges++;
        }

        int V(){
            return vertex;
        }

        int E(){
            return edges;
        }

        vector<int> Adj(int v){
            return adj[v];
        }

        int degree(int v){
            return adj[v].size();
        }

};

#endif //KAOYAN_GRAPH_H
