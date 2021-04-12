//
// Created by leexm on 2021/4/10.
//

#ifndef KAOYAN_DEPTHFIRSTSEARCH_H
#define KAOYAN_DEPTHFIRSTSEARCH_H

#include "Graph.h"

class DepthFirstSearch{
    private:
        vector<bool> marked;
        vector<vector<int>> allways;
        int count;

    public:
        DepthFirstSearch(Graph* g,int s){
            marked.resize(g->V(),false);
            count=0;
            dfs(g,s);
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

        //find all the way from s to cur
        void findAllways(Graph* g,int v,int cur,vector<int>& temp){
            marked[v]=true;
            if(v==cur){
                allways.push_back(temp);
                marked[v]=false;
                return ;
            }

            for(int w:g->Adj(v)){
                if(!marked[w]){
                    temp.push_back(w);
                    findAllways(g,w,cur,temp);
                    temp.pop_back();
                    marked[w]=false;
                }
            }
        }

        vector<vector<int>> DFS(Graph* g,int s,int e){
            for(int i=0;i<marked.size();i++)
                marked[i]=false;
            vector<int> temp;

            findAllways(g,s,e,temp);
            return allways;
        }
        //
};

#endif //KAOYAN_DEPTHFIRSTSEARCH_H
