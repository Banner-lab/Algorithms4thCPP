//
// Created by leexm on 2021/4/25.
//

#ifndef KAOYAN_NFA_H
#define KAOYAN_NFA_H

#include <stack>
#include "../graph/Digraph.h"
#include "../graph/DirectedDFS.h"
#include <string>

class NFA{
    private:
        std::string re;
        Digraph* g;
        int M;
    public:
        NFA(std::string regexp){
            std::stack<int> ops;
            re=regexp;
            M=regexp.length();
            g=new Digraph(M+1);

            for(int i=0;i<M;i++) {
                int lp = i;
                if (re[i] == '(' || re[i] == '|')
                    ops.push(i);
                else if (re[i] == ')')
                {
                    int Or=ops.top();
                    ops.pop();
                    if(re[Or]=='|'){
                    lp=ops.top();
                    ops.pop();
                    g->addEdge(lp,Or+1);
                    g->addEdge(Or,i);
                    }else
                        lp=Or;
                }
                if(i<M-1&&re[i+1]=='*'){
                    g->addEdge(lp,i+1);
                    g->addEdge(i+1,lp);
                }
                if(re[i]=='('||re[i]=='*'||re[i]==')')
                    g->addEdge(i,i+1);
            }
        }

        bool recognizes(std::string txt){
            std::vector<int> pc;
            DirectedDFS *dfs=new DirectedDFS(g,0);
            for(int v=0;v<g->V();v++)
                if(dfs->Marked(v))
                    pc.push_back(v);

            for(int i=0;i<txt.length();i++){
                std::vector<int> match;
                for(int v:pc)
                    if(v<M)
                        if(re[v]==txt[i]||re[v]=='.')
                            match.push_back(v+1);
                dfs=new DirectedDFS(g,match);
                pc.clear();
                for(int v=0;v<g->V();v++)
                    if(dfs->Marked(v))
                        pc.push_back(v);
            }
            for(int v:pc)
                if(v==M)
                    return true;
            return false;
        }
};

#endif //KAOYAN_NFA_H
