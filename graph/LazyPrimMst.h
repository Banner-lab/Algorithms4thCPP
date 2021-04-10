//
// Created by leexm on 2021/4/7.
//

#ifndef KAOYAN_PRIMMST_H
#define KAOYAN_PRIMMST_H

#include "WeightGraph.h"
#include <queue>

class PrimMST{
private:
    queue<Edge> mst;
    double TotalWeight;
    priority_queue<Edge,vector<Edge>,greater<Edge>> minpq;
    vector<bool> marked;
public:
    PrimMST(WeightGraph* g):TotalWeight(0.0){
        marked.resize(g->V(),false);
    }

    void visit(WeightGraph* g,int v){
        marked[v]=true;
        for(Edge e:g->Adj(v)){
            if(!marked[e.other(v)])
                minpq.push(e);
        }
    }

    queue<Edge> prim(WeightGraph* g){
        visit(g,0);
        while(!minpq.empty()){
            Edge e=minpq.top();
            minpq.pop();
            int v=e.either();
            int w=e.other(v);

            if(marked[v]&&marked[w])
                continue;
            mst.push(e);
            TotalWeight+=e.W();
            if(!marked[v])
                visit(g,v);
            if(!marked[w])
                visit(g,w);
        }
        return mst;
    }

    double Weight(){
        return TotalWeight;
    }
};

#endif //KAOYAN_PRIMMST_H
