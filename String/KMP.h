//
// Created by leexm on 2021/4/24.
//

#ifndef KAOYAN_KMP_H
#define KAOYAN_KMP_H

#include <string>
#include <vector>

class Kmp{
   private:
        std::string pat;
        std::vector<std::vector<int>> dfa;

   public:
        Kmp(std::string pat_){
            pat=pat_;
            int m=pat.length();
            int r=256;
            dfa.resize(r,std::vector<int>(m));

            dfa[pat.at(0)][0]=1;
            for(int X=0,j=1;j<m;j++){
                for(int c=0;c<r;c++)
                    dfa[c][j]=dfa[c][X];
                dfa[pat.at(j)][j]=j+1;
                X=dfa[pat.at(j)][X];
            }
        }

        int search(std::string txt){
            int i,j,N=txt.length();
            int M=pat.length();
            for(i=0,j=0;i<N&&j<M;i++)
                j=dfa[txt.at(i)][j];
            if(j==M)
                return i-M;
            else
                return N;
        }
};

#endif //KAOYAN_KMP_H
