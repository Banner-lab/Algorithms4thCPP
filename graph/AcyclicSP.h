//
// Created by leexm on 2021/4/18.
//

#ifndef KAOYAN_ACYCLICSP_H
#define KAOYAN_ACYCLICSP_H

#include "WeightDirectGraph.h"
#include "Topological.h"
#include <limits>

class AcyclicSP{
    private:
        std::vector<DirectiedEdge> edgeTo;
        std::vector<double> distTo;
        int start;
    public:
        AcyclicSP(WeightDirectGraph* g){
            Topological t(g);
            std::stack<int> order=t.revPos();
            edgeTo.resize(g->V());
            start=order.top();
            distTo.resize(g->V(),std::numeric_limits<double>::max());

            distTo[start]=0.0;

            while(!order.empty()){
                int vertex=order.top();
                order.pop();
                Relax(g,vertex);
            }
        }

        void Relax(WeightDirectGraph* g,int v){
            for(auto e:g->Adj(v)){
                int w=e.to();
                if(distTo[w]>e.Weight()+distTo[v]){
                    distTo[w]=e.Weight()+distTo[v];
                    edgeTo[w]=e;
                }
            }
        }


        double Distto(int v){
            return distTo[v];
        }

        bool Haspathto(int v){
            return distTo[v]<std::numeric_limits<double>::max();
        }

        std::stack<DirectiedEdge> Path(int v){
            std::stack<DirectiedEdge> res;
            if(!Haspathto(v))
                return res;

            DirectiedEdge e=edgeTo[v];
            for(;e.from()!=start;e=edgeTo[e.from()])
                res.push(e);
            res.push(e);
            return res;
        }
};

#endif //KAOYAN_ACYCLICSP_H
