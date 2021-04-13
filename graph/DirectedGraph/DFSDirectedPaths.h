//
// Created by leexm on 2021/4/13.
//

#ifndef KAOYAN_DFSDIRECTEDPATHS_H
#define KAOYAN_DFSDIRECTEDPATHS_H

#include "Digraph.h"
#include <stack>

class DFSDirectedPaths{
    private:
        std::vector<bool>  marked;
        std::vector<int>   edgeTo;
        std::vector<std::vector<int>> paths;
        int start;
    public:
        DFSDirectedPaths(Digraph* g,int s){
            marked.resize(g->V(),false);
            edgeTo.resize(g->V());
            start=s;
            dfs(g,s);
        }

        void dfs(Digraph* g,int v){
            marked[v]=true;
            for(int w:g->Adj(v)){
                if(!marked[w]){
                    edgeTo[w]=v;
                    dfs(g,w);
                }
            }
        }

        bool hasPathto(int v){
            return marked[v];
        }

        std::stack<int> pathTo(int v){
            std::stack<int> path;
            if(!hasPathto(v))
                return path;
            for(int w=v;w!=start;w=edgeTo[w]){
                path.push(w);
            }
            path.push(start);
            return path;
        }

        std::vector<std::vector<int>> allPathto(Digraph* g,int v){
            for(int i=0;i<g->V();i++)
                marked[i]=false;
            std::vector<int>    temp;
            dfs_p(g,start,v,temp);
            return paths;
        }

        void dfs_p(Digraph* g,int v,int u,std::vector<int>& res){
            marked[v]=true;
            if(v==u){
                paths.push_back(res);
                marked[v]=false;
                return ;
            }
            for(int w:g->Adj(v)){
                if(!marked[w]){
                    res.push_back(w);
                    dfs_p(g,w,u,res);
                    res.pop_back();
                    marked[w]=false;
                }
            }

        }
};

#endif //KAOYAN_DFSDIRECTEDPATHS_H
