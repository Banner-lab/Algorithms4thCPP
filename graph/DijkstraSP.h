//
// Created by leexm on 2021/4/11.
//

#ifndef KAOYAN_SP_H
#define KAOYAN_SP_H

#include "WeightDirectGraph.h"
#include <limits>
#include <stack>
#include <map>

class DijkstraSP{
private:
    std::vector<DirectiedEdge> edgeTo;
    std::vector<double> distTo;
    double totalWeight;
    std::map<int,double> minpq;

    int delMin(){
        int index=0;
        int minval=std::numeric_limits<int>::max();
        for(auto v:minpq){
            if(v.second<minval){
                minval=v.second;
                index=v.first;
            }
        }
        return index;
    }

    void Delete(int v){
        std::map<int,double>::iterator it=minpq.find(v);
        minpq.erase(it);
    }

public:
    DijkstraSP(WeightDirectGraph *g,int s){
        edgeTo.resize(g->V());
        distTo.resize(g->V(),std::numeric_limits<double>::max());
        totalWeight=0.0;

        minpq[s]=0.0;
        distTo[s]=minpq[s];
        while(!minpq.empty()){
            int v=delMin();
            Delete(v);
            Relax(g,v);
        }
    }

    void relax(DirectiedEdge e){
        int v=e.from();
        int w=e.to();
        if(e.Weight()+distTo[v]<distTo[w])
        {
            edgeTo[w]=e;
            distTo[w]=distTo[v]+e.Weight();
        }
    }

    void Relax(WeightDirectGraph *g,int v){
        for(DirectiedEdge e:g->Adj(v)){
            int w=e.to();

            if(e.Weight()+distTo[v]<distTo[w]){
                edgeTo[w]=e;
                distTo[w]=e.Weight()+distTo[v];
                minpq[w]=distTo[w];
            }
        }
    }

    double DistTo(int v){
        return distTo[v];
    }

    bool hasPathTo(int v){
        return DistTo(v)<std::numeric_limits<double>::max();
    }

    std::stack<DirectiedEdge> pathTo(int v){
        std::stack<DirectiedEdge> res;

        if(!hasPathTo(v))
            return res;
        DirectiedEdge e=edgeTo[v];
        for(;e.from()!=0;e=edgeTo[e.from()])
            res.push(e);
        res.push(e);
        return res;
    }
};

#endif
