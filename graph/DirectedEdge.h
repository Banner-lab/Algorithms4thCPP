//
// Created by leexm on 2021/4/11.
//

#ifndef KAOYAN_DIRECTEDEDGE_H
#define KAOYAN_DIRECTEDEDGE_H



class DirectiedEdge{
    private:
        double weight;
        int v;
        int w;
    public:
        DirectiedEdge(int start,int end,double val):weight(val),v(start),w(end){}
        DirectiedEdge(){}
        double Weight(){
            return weight;
        }

        int from(){
            return v;
        }

        int to(){
            return w;
        }
};

#endif //KAOYAN_DIRECTEDEDGE_H
