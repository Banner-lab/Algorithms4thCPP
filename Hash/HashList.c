//
// Created by leexm on 2021/3/23.
//

#include <stdio.h>
#include <stdlib.h>

#define Empty 0
#define Has   1

typedef int Pos;
typedef int ElemType;

typedef struct LNode{
    ElemType elem;
    struct LNode * next;
}LNode;

typedef struct HashTable{
    int tableSize;
    LNode** chains;
}HashTable;

typedef struct HashTable* HashTal;

HashTal create_tabl(int size){
    HashTal ht=(HashTal)malloc(sizeof(HashTable));
    if(!ht){
        printf("Stackoverflow");
        exit(-1);
    }
    ht->tableSize=size;
    ht->chains=(LNode**)malloc(sizeof(LNode*)*size);
    if(!ht->chains){
        printf("Stackoverflow");
        exit(-1);
    }
    for(int i=0;i<size;i++){
        ht->chains[i]=(LNode*)malloc(sizeof(LNode));
        ht->chains[i]->elem=Empty;
        ht->chains[i]->next=NULL;
    }
    return ht;
}

int hash(int key,int sz){
    return key%sz;
}

void insert(int key,HashTal ht){
    int h=hash(key,ht->tableSize);
    if(ht->chains[h]->elem==Empty)
        ht->chains[h]->elem=Has;
    LNode* temp=(LNode*)malloc(sizeof(LNode));
    temp->elem=key;

    LNode* prev=ht->chains[h]->next;
    ht->chains[h]->next=temp;
    temp->next=prev;

}

void del_key(int key,HashTal ht){
    int h=hash(key,ht->tableSize);
    LNode* prev=ht->chains[h]->next;
    LNode* cur=NULL;
    while(prev->elem!=key){
        cur=prev;
        prev=prev->next;
    }
    if(prev->next==NULL)
        cur->next=NULL;
    cur->next=prev->next->next;
    free(prev);
}

int search(int key,HashTal ht){
    int h=hash(key,ht->tableSize);
    LNode* head=ht->chains[h]->next;
    while(head->elem!=key&&head!=NULL){
        head=head->next;
    }
    if(!head)
        return -1;
    return head->elem;
}

void show_(HashTal ht){
    printf("IN\n");
    for(int i=0;i<ht->tableSize;i++){
        if(ht->chains[i]->elem==Empty)
            printf("Empty!");
        else {
            printf("Hasmd:");
            LNode* head=ht->chains[i]->next;
            while(head!=NULL){
               printf("%d\t",head->elem);
               head=head->next;
            }
        }
        printf("\n");
    }
}


int main(void){
    HashTal ht=create_tabl(17);
    //printf("Assert\n");
    insert(15,ht);
    insert(89,ht);
    insert(6,ht);
    insert(90,ht);
    insert(26,ht);
    insert(123,ht);
    insert(254,ht);

    show_(ht);    return 0;
}


