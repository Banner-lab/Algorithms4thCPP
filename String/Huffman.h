//
// Created by leexm on 2021/4/26.
//

#ifndef KAOYAN_HUFFMAN_H
#define KAOYAN_HUFFMAN_H

#include <string>
#include <vector>
#include <iostream>
#include <queue>

class Huffman{
    private:
        const int R=256;

        class Node{
            public:
                char ch;
                int freq;
                Node* left,*right;

                Node(char c,int fre,Node* l,Node* r):ch(c),freq(fre),left(l),right(r){

                }

                bool isLeaf(){
                    return left==nullptr&&right==nullptr;
                }

                friend bool operator<(const Node& t1,const Node& t2){
                    return t1.freq<t2.freq;
                }

                friend bool operator>(const Node&t1,const Node& t2){
                    return t1.freq>t2.freq;
                }


        };

        class Compare_Node_Pointer{
            public:
                bool operator()(Node* &a,Node* &b)const{
                    return a->freq>b->freq;
                }
        };

        std::string bitStream;

        std::string charToBinary(char c){
            std::string res;
            unsigned char l=0x80;
            for(int i=0;i<8;i++,l>>=1){
                if(l&c)
                    res+='1';
                else
                    res+='0';
            }

            return res;
        }


        int binaryToChar(std::string bin){
            int sum=0;
            for(int i=bin.length()-1;i>=0;i--){
                sum=sum*2+(bin[i]-'0');
            }

            return sum;
        }

    //-----------------------------------------------


    //------------------------------------------
    private:
        void buildCode(std::vector<std::string>& st,Node* x,std::string s){
            if(x->isLeaf())
            {
                st[x->ch]=s;
                return ;
            }

            buildCode(st,x->left,s+'0');
            buildCode(st,x->right,s+'1');
        }
    //--------------------------------------------------
        Node* buildTrie(std::vector<int>& freqs){
            std::priority_queue<Node*,std::vector<Node*>,Compare_Node_Pointer> minPq;
            for(int c=0;c<R;c++){
                if(freqs[c]>0)
                {
                    Node* p=new Node(c,freqs[c], nullptr,nullptr);
                    minPq.push(p);

                }
            }

            while(minPq.size()>=2){
                Node* x=minPq.top();
                minPq.pop();

                Node* y=minPq.top();
                minPq.pop();

                Node* parent=new Node('/0',x->freq+y->freq,x,y);
                minPq.push(parent);
            }



            Node* res=minPq.top();
            minPq.pop();
            return res;
        }
     private:
        void writeTrie(Node* root){
            if(root->isLeaf()){
                bitStream+='1';
                std::string ascii=charToBinary(root->ch);
                bitStream+=ascii;
                return ;
            }
            bitStream+='0';
            writeTrie(root->left);
            writeTrie(root->right);
        }


      //---------------------------------------------------
    public:
      void compress(std::string stdin){
            std::string s=stdin;
            std::vector<int> fre(R,0);

            for(char c:s){
                fre[c]++;
            }

            Node* root=buildTrie(fre);
            std::vector<std::string> st;
            st.resize(R,"");
            buildCode(st,root,"");
            writeTrie(root);
            for(int i=0;i<bitStream.length();i++){
                std::cout<<bitStream[i];
                if(i==29)
                    std::cout<<std::endl;

            }


        }


        Huffman(){}
};

#endif //KAOYAN_HUFFMAN_H
