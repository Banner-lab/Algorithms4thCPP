//
// Created by leexm on 2021/4/10.
//

#ifndef KAOYAN_KURASAL_H
#define KAOYAN_KURASAL_H

#include "WeightGraph.h"
#include "UnionFind.h"
#include <queue>

class Kurasal{
    private:
        queue<Edge> mst;
        priority_queue<Edge,vector<Edge>,greater<Edge>> minpq;
        double totalWeight;
    public:
        Kurasal(WeightGraph* g){
            UF *uf=new UF(g->V());
            totalWeight=0.0;

            for(Edge e:g->Edges())
                minpq.push(e);
            while(!minpq.empty()&&mst.size()<g->E()-1){
                Edge e=minpq.top();
                minpq.pop();

                int v=e.either();
                int w=e.other(v);
                if(uf->connected(v,w))
                    continue;
                uf->Union(v,w);
                totalWeight+=e.W();
                mst.push(e);
            }
        }

        queue<Edge> kurasal_algo(){
                return mst;
        }

        double Weight(){
            return totalWeight;
        }
};

#endif //KAOYAN_KURASAL_H
