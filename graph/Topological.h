//
// Created by leexm on 2021/4/14.
//

#ifndef KAOYAN_TOPOLOGICAL_H
#define KAOYAN_TOPOLOGICAL_H

#include "Digraph.h"
#include <stack>

class Topological{
    private:
        std::vector<bool> marked;
        std::stack<int> reversePost;
    public:
        Topological(Digraph* g){
            marked.resize(g->V(),false);
            for(int i=0;i<g->V();i++)
                if(!marked[i])
                    dfs(g,i);

        }

        void dfs(Digraph* g,int v){
            marked[v]=true;

            for(int w:g->Adj(v)){
                if(!marked[w])
                    dfs(g,w);
            }
            reversePost.push(v);
        }

        std::stack<int> revPos(){
            return reversePost;
        }
};

#endif //KAOYAN_TOPOLOGICAL_H
