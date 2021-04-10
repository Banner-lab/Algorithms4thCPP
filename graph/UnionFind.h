//
// Created by leexm on 2021/4/10.
//

#ifndef KAOYAN_UNIONFIND_H
#define KAOYAN_UNIONFIND_H

#include <iostream>
#include <vector>

class UF{
    private:
        std::vector<int> id;
        std::vector<int> sz;
        int count;
    public:
        UF(int n){
            id.resize(n);
            sz.resize(n,1);
            for(int i=0;i<n;i++)
                id[i]=i;
            count=n;
        }

        int find(int p){
            while(p!=id[p])
                p=id[p];
            return p;
        }

        bool connected(int i,int j){
            return find(i)==find(j);
        }



        void Union(int i,int j){
            if(connected(i,j))
                return ;
            int iRoot=find(i);
            int jRoot=find(j);
            if(iRoot==jRoot)
                return ;
            if(sz[iRoot]<sz[jRoot]) {
                id[iRoot] = jRoot;
                sz[jRoot]+=sz[iRoot];
            }else {
                id[jRoot]=iRoot;
                sz[iRoot]+=sz[jRoot];
            }
            count--;
        }
};

#endif //KAOYAN_UNIONFIND_H
