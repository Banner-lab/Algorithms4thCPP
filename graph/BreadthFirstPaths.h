//
// Created by leexm on 2021/4/12.
//

#ifndef KAOYAN_BREADTHFIRSTPATHS_H
#define KAOYAN_BREADTHFIRSTPATHS_H

#include "Graph.h"
#include <queue>
#include <stack>

class BreadthFirstPaths{
    private:
        vector<int> edgeTo;
        vector<bool> marked;
        int start;
    public:
        BreadthFirstPaths(Graph* g,int s):start(s){
            edgeTo.resize(g->V());
            marked.resize(g->V(),false);
            start=s;
            bfs(g,s);
        }

        void bfs(Graph* g,int s){
            queue<int> q;
            q.push(s);
            marked[s]=true;
            while(!q.empty()){
                int v=q.front();
                q.pop();

                for(auto w:g->Adj(v)){
                    if(!marked[w]){
                        q.push(w);
                        edgeTo[w]=v;
                        marked[w]=true;
                    }
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

#endif //KAOYAN_BREADTHFIRSTPATHS_H
