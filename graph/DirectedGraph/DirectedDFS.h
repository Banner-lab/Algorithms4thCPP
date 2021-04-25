//
// Created by leexm on 2021/4/13.
//

#ifndef KAOYAN_DIRECTEDDFS_H
#define KAOYAN_DIRECTEDDFS_H

#include "Digraph.h"

class DirectedDFS{
    private:
        std::vector<bool> marked;
    public:
        DirectedDFS(Digraph* g,int s){
            marked.resize(g->V(),false);
            dfs(g,s);
        }

        DirectedDFS(Digraph* g,std::vector<int> vec){
            marked.resize(g->V(),false);
            for(int v:vec){
                if(!marked[v])
                    dfs(g,v);
            }
        }

        void dfs(Digraph* g,int s){
            marked[s]=true;
            for(int w:g->Adj(s)){
                if(!marked[w])
                    dfs(g,w);
            }
        }

        bool Marked(int v){
            return marked[v];
        }

};

#endif //KAOYAN_DIRECTEDDFS_H
