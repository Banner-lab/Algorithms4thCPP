//
// Created by leexm on 2021/4/25.
//

#ifndef KAOYAN_BOYERMOORE_H
#define KAOYAN_BOYERMOORE_H

#include <vector>
#include <string>

class BoyerMoore{
    private:
        std::vector<int> right;
        std::string pat;
        int R=256;
    public:
        BoyerMoore(std::string Pat){
            pat=Pat;
            right.resize(R,-1);
            int index=0;

            for(char c:pat)
                right[c]=index++;
        }

        int search(std::string txt){
            int N=txt.length();
            int M=pat.length();

            int skip;
            for(int i=0;i<=N-M;i+=skip){
                skip=0;

                for(int j=M-1;j>=0;j--){
                    if(pat[j]!=txt[i+j]){
                        skip=j-right[txt[i+j]];
                        if(skip<1)
                            skip=1;
                        break;
                    }
                }
                if(skip==0)
                    return i;
            }
            return N;
        }
};

#endif //KAOYAN_BOYERMOORE_H

