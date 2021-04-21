//
// Created by leexm on 2021/4/21.
//

#ifndef KAOYAN_TST_H
#define KAOYAN_TST_H

#include <string>
#define R 26

class TST{
    private:
        class TSTNode{
            public:
                int val;//key with value
                TSTNode* left;
                TSTNode* mid;
                TSTNode* right;
                char c;

                TSTNode(){
                    val=-1;
                    left=nullptr;
                    mid=nullptr;
                    right=nullptr;
                }

                ~TSTNode(){
                    delete left;
                    delete mid;
                    delete right;
                }
        };
//------------------------------------------
    private:
        TSTNode* root;
//------------------------------------------
    public:
        TST(){
            root=nullptr;
        }

        ~TST(){
            delete root;
        }
//------------------------------------------
    private:
        TSTNode* get(TSTNode* node,std::string key,int d){
            if(node==nullptr)
                return nullptr;
            char c=key[d];
            if(c<node->c)
                return get(node->left,key,d);
            else if(c>node->c)
                return get(node->right,key,d);
            else if(d<key.length()-1)
                return get(node->mid,key,d+1);
            else
                return node;
        }


        TSTNode* put(TSTNode* node,std::string key,int val,int d){
            char c=key[d];
            if(node==nullptr) {
                node = new TSTNode();
                node->c=c;
            }
            if(c<node->c){
                node->left=put(node->left,key,val,d);
            }else if(c>node->c){
                node->right=put(node->right,key,val,d);
            }else if(d<key.length()-1){
                node->mid=put(node->mid,key,val,d+1);
            }else
                node->val=val;
            return node;
        }


//-----------------------------------------
    public:
        int get(std::string key){
            TSTNode* node=get(root,key,0);
            if(node==nullptr)
                return -1;
            return node->val;
        }

        void put(std::string key,int val){
            root=put(root,key,val,0);
        }
};


#endif //KAOYAN_TST_H
