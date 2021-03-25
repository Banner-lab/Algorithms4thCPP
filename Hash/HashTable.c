//
// Created by leexm on 2021/3/16.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define Deleted -1
#define Had 1
#define Empty 0

typedef struct{
    int key;
    int status;
}Cell;

typedef struct{
    int tableSize;
    Cell* cells;
}HashTable;


HashTable *create(int size){
    HashTable* ht=(HashTable*)malloc(sizeof(HashTable));
    if(!ht){
        printf("Error in create!!!\n");
        exit(-1);
    }
    ht->tableSize=size;
    ht->cells=(Cell*)malloc(sizeof(Cell)*ht->tableSize);
    for(int i=0;i<ht->tableSize;i++){
        ht->cells[i].status=Empty;
    }
    return ht;
}

int hash(int key,int size){
    return key%size;
}

int Find(int key,HashTable* ht){
    int cur,prev;
    cur=prev=hash(key,ht->tableSize);
    int cnt=0;
    while(ht->cells[cur].status!=Empty&&ht->cells[cur].key!=key){
        if(++cnt%2){
            cur=prev+(cnt+1)/2+(cnt+1)/2;
            while(cur>=ht->tableSize)
                cur-=ht->tableSize;
        }else{
            cur=prev-(cnt+1)/2-(cnt+1)/2;
            while(cur<0)
                cur+=ht->tableSize;
        }
    }
    return cur;
}

void insert(int key,HashTable* ht){
    int h=Find(key,ht);
    if(ht->cells[h].status!=Had){
        ht->cells[h].status=Had;
        ht->cells[h].key=key;
    }
}


void del_(int key,HashTable* ht){
    int h=Find(key,ht);
    if(ht->cells[h].status!=Deleted&&ht->cells[h].status!=Empty)
        ht->cells[h].status=Deleted;
}

int main(int argc,char* ahargv[]){
    HashTable* ht=create(11);
    srand((unsigned)time(NULL));
    for(int i=0;i<11;i++){
        int temp=rand();
        printf("%d--%d\t",temp,hash(temp,ht->tableSize));
        insert(temp,ht);
    }
    printf("\n");
    for(int i=0;i<11;i++){
        printf("%d--%d\t",ht->cells[i].key,i);
    }
    printf("\n");
}
