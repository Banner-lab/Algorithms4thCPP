//
// Created by leexm on 2021/4/12.
//

#ifndef KAOYAN_DEPTHFIRSTPATHS_H
#define KAOYAN_DEPTHFIRSTPATHS_H

#include "Graph.h"
#include "Edge.h"
#include <stack>

class DepthFirstPaths{
    private:
        vector<int> edgeTo;
        vector<bool> marked;
        int start;
    public:
        DepthFirstPaths(Graph* g,int s){
            edgeTo.resize(g->V());
            marked.resize(g->V(),false);
            start=s;
            dfs(g,s);
        }

        void dfs(Graph* g,int s){
            marked[s]=true;
            for(auto w:g->Adj(s)){
                if(!marked[w]){
                    edgeTo[w]=s;
                    dfs(g,w);
                }
            }
        }

        bool hasPathTo(int v){
            return marked[v];
        }

        stack<int> pathTo(int v){
            stack<int> res;
            if(!hasPathTo(v))
                return res;
            for(int w=v;w!=start;w=edgeTo[w])
                res.push(w);
            res.push(start);
            return res;
        }
};

#endif //KAOYAN_DEPTHFIRSTPATHS_H
