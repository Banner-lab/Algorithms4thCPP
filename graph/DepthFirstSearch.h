//
// Created by leexm on 2021/4/10.
//

#ifndef KAOYAN_DEPTHFIRSTSEARCH_H
#define KAOYAN_DEPTHFIRSTSEARCH_H

#include "Graph.h"

class DepthFirstSearch{
    private:
        vector<bool> marked;
        int count;
    public:
        DepthFirstSearch(Graph* g,int s){
            marked.resize(g->V(),false);
            count=0;

            (g,0);
        }

        void dfs(Graph* g,int s){
            marked[s]=true;
            count++;
            for(auto v:g->Adj(s))
            {
                if(!marked[v])
                    dfs(g,v);
            }
        }

        int Count(){
            return count;
        }

        bool Marked(int v){
            return marked[v];
        }
};

#endif //KAOYAN_DEPTHFIRSTSEARCH_H
