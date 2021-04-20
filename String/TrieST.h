//
// Created by leexm on 2021/4/19.
//

#ifndef KAOYAN_TRIEST_H
#define KAOYAN_TRIEST_H

#include <vector>
#include <iostream>
#include <string>

#define R 256

class TrieNode{
    public:
        int val;
        std::vector<TrieNode*> next;

        TrieNode(){
            val=-1;
            next.resize(R,nullptr);
        }

        ~TrieNode() {
            for(int i=0;i<R;i++)
                delete next[i];
        }
};
class Trie{
    private:
        TrieNode* root;

        TrieNode* get(TrieNode* node,std::string key,int d){
            if(node==nullptr)
                return nullptr;
            if(d==key.length())
                return node;
            char c=key[d];
            return get(node->next[c],key,d+1);

        }

        TrieNode* put(TrieNode* node,std::string key,int val,int d){
            if(node==nullptr)
                node=new TrieNode();
            if(d==key.length())
            {
                node->val=val;
                return node;
            }

            char c=key[d];
            node->next[c]=put(node->next[c],key,val,d+1);
            return node;
        }

        public:
            Trie(){
            root=new TrieNode();
        }

        ~Trie(){
            delete root;
        }

        int get(std::string key){
            TrieNode* node=get(root,key,0);
            if(node==nullptr)
                return -1;
            return node->val;
        }

        void put(std::string key,int val){
            root=put(root,key,val,0);
        }

        void collect(std::string pre,TrieNode* node,std::vector<std::string> & res){
            if(node==nullptr)
                return  ;

            if(node->val!=-1){
                res.push_back(pre);
            }

            for(int c=0;c<R;c++){
                std::string re(1,c);

                collect(pre+re,node->next[c],res);
            }
        }

        void keysWithPrefix(std::string pre,std::vector<std::string>& res){
            TrieNode* node=get(root,pre,0);
            collect(pre,node,res);
        }

        std::vector<std::string> keysThatMatch(std::string pat){
            std::vector<std::string> ret;
            collect(root,pat,"",ret);
            return ret;
        }

        void collect(TrieNode* node,std::string pat,std::string pre,std::vector<std::string>& ret){
            if(node==nullptr)
                return ;
            int d=pre.length();

            if(d==pat.length()&&node->val!=-1)
                ret.push_back(pre);
            if(d==pat.length())
                return ;
            char c=pat[d];
            for(int i=0;i<R;i++)
            {
                std::string temp(1,i);
                if(c=='.'||i==c)
                    collect(node->next[i],pat,pre+temp,ret);
            }
        }

        std::string longestPrefixOf(std::string s){
            int length=search(root,s,0,0);
            std::string res=s.substr(0,length);
            return res;
        }

        int search(TrieNode* node,std::string s,int d,int length){
            if(node==nullptr)
                return length;
            if(node->val!=-1)
                length=d;
            if(d==s.length())
                return length;
            char c=s[d];
            return search(node->next[c],s,d+1,length);
        }

        void delete_(std::string key){
            root=delete_(key,root,0);
        }

        TrieNode* delete_(std::string key,TrieNode* node,int d){
            if(node==nullptr)
                return nullptr;
            if(d==key.length())
                node->val=-1;
            else{
                char c=key[d];
                node->next[c]=delete_(key,node->next[c],d+1);
            }

            if(node->val!=-1)
                return node;

            for(int i=0;i<R;i++)
                if(node->next[i]!=nullptr)
                    return node;
            return nullptr;
        }
};

#endif //KAOYAN_TST_H
