//
// Created by leexm on 2021/4/8.
//

#ifndef KAOYAN_EDGE_H
#define KAOYAN_EDGE_H

class Edge{
    private:
        int v;
        int w;
        double weight;
    public:
        Edge():v(0),w(0),weight(0.0){}
        Edge(int vertex,int wv,double weg):v(vertex),w(wv),weight(weg){}
        ~Edge() { }

        int V(){
            return v;
        }

        double W()const{
            return weight;
        }

        int either(){
            return v;
        }

        int other(int vertex){
            if(vertex==v)
                return w;
            else
                return v;
        }

        friend bool operator<(const Edge& a,const Edge& b){
            return a.weight<b.weight;
        }

        friend bool operator>(const Edge& a,const Edge& b){
            return a.weight>b.weight;
        }

        friend bool operator==(const Edge& a,const Edge& b){
            return a.weight==b.weight;
        }
};

#endif //KAOYAN_EDGE_H
