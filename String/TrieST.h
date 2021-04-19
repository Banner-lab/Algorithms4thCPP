//
// Created by leexm on 2021/4/19.
//

#ifndef KAOYAN_TRIEST_H
#define KAOYAN_TRIEST_H

#include <string.h>
#include <string>
#define R 256

using std::string;

class TrieSTNode{
    public:
        int val;
        TrieSTNode* next[R];
    public:
        TrieSTNode(){
            memset(next,NULL,sizeof(next));
            val=-1;
        }

        ~TrieSTNode(){
            for(int i=0;i<R;i++)
                if(next[i])
                    delete next[i];
        }
};

class TrieST{
    private:
        TrieSTNode* root;
    public:
        TrieST(){
            root=new TrieSTNode();
        }

        ~TrieST(){
            delete root;
        }

        int get(string key){
            TrieSTNode* x=get(root,key,0);
            if(x==NULL)
                return -1;
            return x->val;
        }

        TrieSTNode* get(TrieSTNode* node,string key,int d){
            if(node==NULL)
                return NULL;
            if(d==key.size())
                return node;
            char c=key.at(d);
            return get(node->next[c],key,d+1);
        }

        void put(string key,int val){
            root=put(root,key,val,0);
        }

        TrieSTNode* put(TrieSTNode* node,string key,int val,int d){
            if(node==NULL)
                node=new TrieSTNode();
            if(d==key.size())
            {
                node->val=val;
                return node;
            }
            char c=key.at(d);
            node->next[c]=put(node->next[c],key,val,d+1);
            return node;
        }
};

#endif //KAOYAN_TRIEST_H
