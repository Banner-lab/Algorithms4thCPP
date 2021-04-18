//
// Created by leexm on 2021/4/18.
//

#ifndef KAOYAN_LSD_H
#define KAOYAN_LSD_H

#include <string>
#include <vector>

class LSD{
    private:
        int R=256;
        int N;
        std::vector<std::string> aux;
    public:
        LSD(std::vector<std::string>& s,int w){
            N=s.size();
            aux.resize(N);
            for(int d=w-1;d>=0;d--){
                std::vector<int> cnt(R+1,0);

                for(std::string str:s)
                    cnt[str.at(d)+1]++;

                for(int i=0;i<R;i++)
                    cnt[i+1]+=cnt[i];

                for(int i=0;i<N;i++)
                    aux[cnt[s[i].at(d)]++]=s[i];

                for(int i=0;i<N;i++)
                    s[i]=aux[i];
            }

        }
};

#endif //KAOYAN_LSD_H
