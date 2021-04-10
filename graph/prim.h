//
// Created by leexm on 2021/4/10.
//

#ifndef KAOYAN_PRIM_H
#define KAOYAN_PRIM_H


#include "WeightGraph.h"
#include <map>
#include <limits>

class prim{
    private:
        vector<Edge> edgeTo;
        vector<double>  distTo;
        vector<bool> marked;
        map<int,double> indexpq;
        double totalWeight;

        int delMin(){
            double d=std::numeric_limits<double>::max();
            int    index=0;
            for(auto e:indexpq){
                if(e.second<d)
                {
                    d=e.second;
                    index=e.first;
                }
            }
            return index;
        }

        void delet_e(int v){
            map<int,double>::iterator index=indexpq.find(v);
            indexpq.erase(index);
        }

    public:
        prim(int n):totalWeight(0.0){
            edgeTo.resize(n);
            distTo.resize(n,std::numeric_limits<double>::max());
            marked.resize(n,false);
        }

        vector<Edge> prim_algo(WeightGraph* g){
            distTo[0]=0.0;
            indexpq[0]=0.0;

            while(!indexpq.empty()){
                int i=delMin();
                totalWeight+=indexpq[i];
                delet_e(i);
                visit(g,i);
            }

            return edgeTo;
        }

        void visit(WeightGraph* g,int v){
            marked[v]=true;
            for(Edge e:g->Adj(v)){
                int w=e.other(v);
                if(marked[w])
                    continue;
                if(e.W()<distTo[w]){
                    edgeTo[w]=e;
                    distTo[w]=e.W();

                    indexpq[w]=distTo[w];
                }
            }
        }

        double Weight(){
            return totalWeight;
        }
};

#endif
