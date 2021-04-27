//
// Created by leexm on 2021/4/27.
//

#ifndef KAOYAN_BST_H
#define KAOYAN_BST_H

#include <vector>
#include <queue>


class BST{
    private:
    class Node{
    public:
        int val;
        Node* left,*right;
        int N;//size of subtree

        Node(int v,int n):val(v),N(n){
            left=nullptr;
            right=nullptr;
        }
    };

        Node* root;
//------------------------------------------------
    public:
        BST(){
            root=nullptr;
        }

        ~BST(){
            std::queue<Node*> sup;
            sup.push(root);
            while(!sup.empty()){
                int n=sup.size();
                for(int i=0;i<n;i++){
                    Node* temp=sup.front();
                    sup.pop();

                    if(temp->left)
                        sup.push(temp->left);
                    if(temp->right)
                        sup.push(temp->right);

                    delete temp;
                }
            }
        }
//-----------------------------------------------------
    private:
        int Size(Node* x){
            if(x==nullptr)
                return 0;
            else
                return x->N;
        }
        int search(Node* x,int target){
            if(x==nullptr)
                return -1;//Not found
            if(x->val<target)
                return search(x->right,target);
            else if(x->val>target)
                return search(x->left,target);
            else
                return x->val;
        }
        Node* put(Node* x,int val){
            if(x==nullptr){
                x=new Node(val,1);
                return x;
            }
            if(x->val<val)
                x->right=put(x->right,val);
            else if(x->val>val)
                x->left=put(x->left,val);
            else
                x->val=val;
            x->N=Size(x->left)+Size(x->right)+1;
            return x;
        }
//---------------------------------------------------
    public:
        int Size(){
            return Size(root);
        }
        bool search(int target){
            return search(root,target)!=-1;
        }
        void put(int val){
            root=put(root,val);
        }
//---------------------------------------
//------------------------------------------
    private:
        Node* min(Node* x){
            if(x->left==nullptr)
                return x;
            else
                return min(x->left);
        }

    public:
        int min(){
            Node* cur=min(root);
            return cur->val;
        }
//------------------------------------------
    private:
        Node* max(Node* x){
            if(x->right==nullptr)
                return x;
            else
                return max(x->right);
        }

    public:
        int max(){
            Node* cur=max(root);
            return cur->val;
        }
//------------------------------------------
    private:
        Node* floor(Node* x,int val){
            if(x==nullptr)
                return nullptr;
            if(x->val>val)
                return floor(x->left,val);
            Node* res=floor(x->right,val);
            if(res!=nullptr)
                return res;
            else
                return x;
        }

    public:
        int floor(int val){
            Node* cur=floor(root,val);
            return cur->val;
        }
//-------------------------------------------
    private:
        Node* ceiling(Node* x,int val){
            if(x==nullptr)
                return nullptr;
            if(x->val<val)
                return ceiling(x->right,val);
            Node* res=ceiling(x->left,val);
            if(res!=nullptr)
                return res;
            else
                return x;
    }

    public:
        int ceiling(int val){
            Node* cur=ceiling(root,val);
            return cur->val;
        }
//-------------------------------------------
    private:
        Node* select(Node* x,int k){
            if(x==nullptr)
                return nullptr;
            int t=Size(x->left);
            if(k<t)
                return select(x->left,k);
            else if(k>t)
                return select(x->right,k-t-1);
            else
                return x;
        }

    public:
        int select(int k){
            Node* cur=select(root,k);
            return cur->val;
        }

    private:
        int rank(int val,Node* x){
            if(x==nullptr)
                return 0;
            if(x->val>val)
            {
                return rank(val,x->left);
            }
            else if(x->val<val)
                return rank(val,x->right)+Size(x->left)+1;
            else
                return Size(x->left);
        }

    public:
        int rank(int val){
            return rank(val,root);
        }
//------------------------------------------------------
    private:
        Node* deleteMin(Node* x){
            if(x->left==nullptr){
                return x->right;
            }
            x->left=deleteMin(x->left);
            x->N=Size(x->left)+Size(x->right)+1;
            return x;
        }
    public:
        void deleteMin(){
            root=deleteMin(root);
        }
//------------------------------------------------------
    private:
        Node* deleteMax(Node* x){
            if(x->right==nullptr){
                return x->right;
            }
            x->right=deleteMin(x->right);
            x->N=Size(x->left)+Size(x->right)+1;
            return x;
        }
    public:
        void deleteMax(){
            root=deleteMax(root);
        }
//------------------------------------------------------
    private:
        Node* del(Node* x,int val){
            if(x==nullptr)
                return nullptr;
            if(x->val>val)
                x->left=del(x->left,val);
            else if(x->val<val)
                x->right=del(x->right,val);
            else{
                if(x->right==nullptr)
                    return x->left;
                if(x->left==nullptr)
                    return x->right;
                Node* temp=x;
                x=min(temp->right);
                x->right=deleteMin(temp->right);
                x->left=temp->left;
                delete temp;
            }
            x->N=Size(x->left)+Size(x->right)+1;
            return x;
        }
    public:
        void del(int val){
           root=del(root,val);
        }

    private:
        void keys(Node* x,int lo,int hi,std::queue<int>& res){
            if(x==nullptr)
                return ;
            if(x->val>lo)
                keys(x->left,lo,hi,res);
            if(x->val>=lo&&hi>=x->val)
                res.push(x->val);
            if(x->val<hi)
                keys(x->right,lo,hi,res);
        }

    public:
        std::queue<int> keys(int lo,int hi){
            std::queue<int> ret;
            keys(root,lo,hi,ret);
            return ret;
        }

        std::queue<int> keys(){
            return keys(min(),max());
        }

};

#endif //KAOYAN_BST_H
