//
// Created by leexm on 2021/3/27.
//

#include "WeightGraph.h"
#include <iostream>
#include "PrimMST.h"
#include <vector>
#include "prim.h"
#include "Kurasal.h"
using namespace std;


int main(){
    WeightGraph g(8);
    g.add_edge(4,5,0.35);
    g.add_edge(4,7,0.37);
    g.add_edge(5,7,0.28);
    g.add_edge(0,7,0.16);
    g.add_edge(1,5,0.32);
    g.add_edge(0,4,0.38);
    g.add_edge(2,3,0.17);
    g.add_edge(1,7,0.19);
    g.add_edge(0,2,0.26);
    g.add_edge(1,2,0.36);
    g.add_edge(1,3,0.29);
    g.add_edge(2,7,0.34);
    g.add_edge(6,2,0.40);
    g.add_edge(3,6,0.52);
    g.add_edge(6,0,0.58);
    g.add_edge(6,4,0.93);

    /******
    prim *mst=new prim(g.V());

    vector<Edge> res = mst->prim_algo(&g);
    for(Edge e:res){
        cout<<e.either()<<"--"<<e.other(e.either())<<" "<<e.W()<<endl;
    }
    cout<<"min total_weight = "<<mst->Weight()<<endl;
    cout<<endl;


    PrimMST* m=new PrimMST(&g);
    queue<Edge> s=m->prim(&g);
    while(!s.empty()){
        Edge e=s.front();
        s.pop();
        cout<<e.either()<<"--"<<e.other(e.either())<<" "<<e.W()<<endl;
    }

    cout<<"min total_weight = "<<m->Weight()<<endl;
    cout<<endl;

    ***********/

    Kurasal* mst=new Kurasal(&g);
    queue<Edge> s=mst->kurasal_algo();
    while(!s.empty()){
        Edge e=s.front();
        s.pop();
        cout<<e.either()<<"--"<<e.other(e.either())<<" "<<e.W()<<endl;
    }

    cout<<"min total_weight = "<<mst->Weight()<<endl;


    return 0;
}
