//
// Created by leexm on 2021/4/12.
//

#ifndef KAOYAN_CC_H
#define KAOYAN_CC_H

#include "Graph.h"

class CC{
    private:
        vector<bool> marked;
        vector<int> id;
        int count;
    public:
        CC(Graph *g){
            marked.resize(g->V(),false);
            id.resize(g->V());
            count=0;
            for(auto v=0;v<g->V();v++){
                if(!marked[v]){
                    dfs(g,v);
                    count++;
                }
            }
        }

        void dfs(Graph *g,int v){
            marked[v]=true;
            id[v]=count;
            for(auto w:g->Adj(v)){
                if(!marked[w]){
                    dfs(g,w);
                }
            }
        }

        bool connected(int v,int w){
            return id[v]==id[w];
        }

        int Id(int v){
            return id[v];
        }

        int Count(int v){
            return count;
        }
};

#endif //KAOYAN_CC_H
