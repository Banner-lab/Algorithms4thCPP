//
// Created by leexm on 2021/3/12.
//

#include <iostream>
#include <queue>
#include <vector>

using namespace std;
typedef int ElementType;

struct TreeNode{
    ElementType elem;
    TreeNode* lchild;
    TreeNode* rchild;
};

class BST{
    private:
        TreeNode* root;
        int num;
    public:
        BST():num(0){
            root=new TreeNode;
            root->lchild=nullptr;
            root->rchild=nullptr;
        }

        ElementType findMin(){
            TreeNode* temp=root;
            if(temp==nullptr)
                return 0;
            else {
                while(!temp->lchild)
                    temp=temp->lchild;
                return temp->lchild->elem;
            }
        }

        ElementType findMax(){
            TreeNode* temp=root;
            if(temp==nullptr)
                return 0;
            else {
                while(!temp->rchild)
                    temp=temp->rchild;
                return temp->rchild->elem;
            }
        }

        bool find(ElementType target,TreeNode *roo){
            if(!roo)
                return false;
            if(roo->elem==target)
                return true;
            else if(roo->elem<target)
                return find(target,roo->rchild);
            else
                return find(target,roo->lchild);
        }

        bool search(ElementType target){
            TreeNode* temp=root;
            while(temp){
                if(temp->elem==target)
                    return true;
                else if(temp->elem<target)
                    temp=temp->rchild;
                else
                    temp=temp->lchild;;
            }
            return false;
        }

        void insert(ElementType ins){
            if(num==0){
                root->elem=ins;
                num++;
                return ;
            }else{
                TreeNode* temp=root;
                while(temp){
                    if(temp->elem<ins){
                        if(!temp->rchild)
                        {
                            temp->rchild=new TreeNode;
                            temp->rchild->elem=ins;
                            return ;
                        }
                        temp=temp->rchild;
                    }else if(temp->elem>ins){
                        if(!temp->lchild)
                        {
                            temp->lchild=new TreeNode;
                            temp->lchild->elem=ins;
                            return ;
                        }
                        temp=temp->lchild;
                    }
                }
            }
        }

        void delete_(ElementType target){
            //TreeNode* temp=roo;
            if(!root){
                return ;
            }
            TreeNode* del=root;
            TreeNode* del_father;
            while(del!=nullptr&&del->elem!=target){
                del_father=del;
                if(del->elem<target)
                    del=del->rchild;
                else
                    del=del->lchild;
            }
            if(!del)
                return ;//not found
            if(del->lchild!=nullptr&&del->rchild!=nullptr){
                TreeNode* min_del_r=del->rchild;
                TreeNode* min_del_r_father=del;
            while(!min_del_r->lchild){
                    min_del_r_father=min_del_r;
                    min_del_r=min_del_r->lchild;

                }
                del->elem=min_del_r->elem;
                del=min_del_r;
                del_father=min_del_r_father;
            }

            TreeNode* child;
            if(!del->lchild)
                child=del->rchild;
            else if(!del->rchild)
                child=del->lchild;

            if(!del_father)
                root=child;
            else if(del_father->lchild==del)
                del_father->lchild=child;
            else
                del_father->rchild=child;
            delete del;
        }

        void display(){
            queue<TreeNode*> sup;
            vector<ElementType> res;
            sup.push(root);
            while(true){
                if(sup.empty())
                    break;
                int sz=sup.size();
                for(int i=0;i<sz;i++){
                    TreeNode* temp=sup.front();
                    sup.pop();
                    cout<<temp->elem<<" ";
                    res.push_back(temp->elem);
                    if(temp->lchild)
                        sup.push(temp->lchild);
                    if(temp->rchild)
                        sup.push(temp->rchild);
                }
                cout<<endl;
            }
            
        }

};

