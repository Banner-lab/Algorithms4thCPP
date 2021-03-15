//
// Created by leexm on 2021/3/15.
//

#include <iostream>
#define ALTITUDE 1

typedef int ElementType;


struct AVLnode{
    ElementType data;
    AVLnode* left;
    AVLnode* right;
    int height;

    AVLnode(const ElementType& elem,AVLnode* l,AVLnode* r,int h=0):data(elem),left(l),right(r),height(h){}
};

class AVLTree{

   public:
      AVLTree(){}
      ~AVLTree(){};

      int height(AVLnode* node)const{
          return node==nullptr?-1:node->height;
      }

      void insert(const ElementType &ele,AVLnode* &t){
          if(t==nullptr)
              t=new AVLnode(ele,nullptr,nullptr);
          else if(root->data<ele)
              insert(ele,t->right);
          else
              insert(ele,t->left);

          balance(t);
      }

      void balance(AVLnde *&t){
          if(t==nullptr)
              return ;
          if(height(t->left)-height(t->right)>ALTITUDE){//
              if(height(t->left->left)-height(t->left->right)>=ALTITUDE)//LL
                RightRotate(t);
              else
                LeftRotateAndRightRotate(t);//LR
          }else if(height(t->right)-height(t->left)>ALTITUDE){
              if(height(t->right->right)-height(t->right->left)>=ALTITUDE)
                LeftRotate(t);//RR
              else
                RightRotateAndLeftRotate(t);
          }
          t->height=max(height(t->left),height(t->right))+1;
      }

      void RightRotate(AVLnode* &t){
          AVLnode* temp=t->left;

          t->left=temp->right;
          temp->right=t;

          temp->height=max(height(temp->left),height(temp->right))+1;
          t->height=max(height(t->left),height(t->right))+1;

          t=temp;
      }

      void LeftRotate(AVLnode* &t){
          AVLnode* temp=t->right;

          t->right=temp->left;
          temp->left=t;
          temp->height=max(height(temp->left),height(temp->right))+1;
          t->height=max(height(t->left),height(t->right))+1;

          t=temp;
      }

      void LeftRotateAndRightRotate(AVLnode* &t){
          LeftRotate(t->left);
          RightRotate(t);
      }

      void RightRotateAndLeftRotate(AVLnode* &t){
          RightRotate(t->right);
          LeftRotate(t);
      }

      void delete(const ElementType& ele,AVLnode* &root){
          if(t==nullptr)
              return ;
          if(ele<root->data){
              delete(ele,root->left);
          }else if(ele>root->data)
              delete(ele,root->right);
          else if(!root->left&&!root->right){
              root->data=findMin(root->right)->data;
              delete(root->data,root->right)
          }else {
              AVLnode* temp=root;

              root=root->left==nullptr?root->right:root->left;
              delete temp;
          }
          balance(t);
      }

};