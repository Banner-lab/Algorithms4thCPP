//
// Created by leexm on 2021/4/28.
//

#ifndef KAOYAN_AVLTREE_H
#define KAOYAN_AVLTREE_H

#include <algorithm>
#include <cmath>
#include <queue>
#include <iostream>

static const int ALLOWED_IMBALANCE=1;

class AVLTree{
    private:
        class Node{
        public:
            int val;
            int height;
            Node* left;
            Node* right;

            Node(int v,int h=0,Node* l=nullptr,Node* r=nullptr):val(v),height(h),left(l),right(r){

            }
        };

        int height_(Node* x){
            return x==nullptr?-1:x->height;
        }

        Node* root;

//----------------------------------------------
    public:
        AVLTree(){
            root=nullptr;
        }

        ~AVLTree(){
            delete root;
        }

    private:
        Node* insert(Node* x,int value){
            if(x==nullptr)
            {
                x=new Node(value);
                return x;
            }

            if(x->val>value)
                    x->left=insert(x->left,value);
            else if(x->val<value)
                    x->right=insert(x->right,value);
            x=balance(x);
            return x;
        }

    public:
        void insert(int val){
            root=insert(root,val);
        }
//------------------------------------------------
    private:
        Node* rotateWithLeftChild(Node* x){
            Node* tmp=x->left;
            x->left=tmp->right;
            tmp->right=x;
            x->height=std::max(height_(x->left),height_(x->right))+1;
            tmp->height=std::max(height_(tmp->left),x->height);
            return tmp;
        }

        Node* rotateWithRightChild(Node* x){
            Node* tmp=x->right;
            x->right=tmp->left;
            tmp->left=x;
            x->height=std::max(height_(x->left),height_(x->right))+1;
            tmp->height=std::max(height_(tmp->left),x->height);
            return tmp;
        }

        Node* doubleRotateWithLeftChild(Node* x){
            x->left=rotateWithRightChild(x->left);
            x=rotateWithLeftChild(x);
            return x;
        }

        Node* doubleRotateWithRightChild(Node* x){
            x->right=rotateWithLeftChild(x->right);
            x=rotateWithRightChild(x);
            return x;
        }
//-----------------------------------------------
    private:
        Node* balance(Node* x){
            if(x==nullptr)
                return nullptr;
            if(height_(x->left)-height_(x->right)>ALLOWED_IMBALANCE){
                if(height_(x->left->left)>=height_(x->left->right))
                    x=rotateWithLeftChild(x);
                else
                    x=doubleRotateWithLeftChild(x);
            }else if(height_(x->right)-height_(x->left)>ALLOWED_IMBALANCE){
                if(height_(x->right->right)>=height_(x->right->left))
                    x=rotateWithRightChild(x);
                else
                    x=doubleRotateWithRightChild(x);
            }

            x->height=std::max(height_(x->left),height_(x->right))+1;
            return x;
        }


    private:
        Node* removeMin(Node* x){
            if(x->left==nullptr)
                return x->right;
            x->left=removeMin(x->left);
            x->height=std::max(height_(x->left),height_(x->right))+1;
            return x;
        }

        Node* min(Node* x){
            if(x==nullptr)
                return nullptr;
            Node* tmp=x;
            while(tmp->left!=nullptr)
                tmp=tmp->left;
            return tmp;
        }

        Node* remove(Node* x,int target){
            if(x==nullptr)
                return nullptr;
            if(x->val>target)
                x->left=remove(x->left,target);
            else if(x->val<target)
                x->right=remove(x->right,target);
            else {
                if(x->left==nullptr)
                    return x->right;
                if(x->right==nullptr)
                    return x->left;
                Node* tmp=x;
                x=min(tmp->right);
                x->right=removeMin(tmp->right);
                x->left=tmp->left;
                delete tmp;
            }
            x=balance(x);
            return x;
        }
    public:
        void remove(int target){
            root=remove(root,target);
        }
    
};

#endif //KAOYAN_AVLTREE_H
