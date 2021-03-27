//
// Created by leexm on 2021/3/24.
//

#include <stdio.h>
#include <stdlib.h>

#define  TABLE_SIZE 9
#define  SUCCESS 1
#define  FAIL 0
#define  TRUE 1
#define  FALSE 0

typedef char Vertex;
typedef int  Edge;
typedef int  Weight;


int isVisited[TABLE_SIZE];
char edgeTo[TABLE_SIZE];
char path[TABLE_SIZE];//路径记录
int  Index=0;

typedef struct Vertex_Edge{
    Vertex name;
    Weight edge_weight;
    struct Vertex_Edge *next;
}Vertex_Edge;


typedef struct Vertex_Adj{
    Vertex name;
    Vertex_Edge* first_edge;
}AdjList[TABLE_SIZE];

typedef struct Vertex_Adj AdjHead;

typedef struct Graph{
    int numOfVertex;
    int numOfEdge;
    AdjList adj;

}Graph;

Graph* create_graph(int numV){
    Graph* a=(Graph*)malloc(sizeof(Graph));
    if(!a){
        printf("StackOverFlow!!!\n");
        exit(-1);
    }
    a->numOfVertex=numV;
    a->numOfEdge=0;

    for(int i=0;i<numV;i++)
        a->adj[i].first_edge=NULL;

    return a;
}
 AdjHead*  find_Vertex(Graph* g,Vertex a){
    for(int i=0;i<g->numOfVertex;i++){
        if(g->adj[i].name==a)
            return &g->adj[i];
    }
}

int exist(Vertex a,Vertex b,Graph* g){
    for(int i=0;i<g->numOfVertex;i++){
        if(g->adj[i].name==a){
            Vertex_Edge * edge_v=g->adj[i].first_edge;
            while(edge_v!=NULL){
                if(edge_v->name==b)
                    break;
                edge_v=edge_v->next;
            }
            if(edge_v!=NULL)
            {
                return SUCCESS;
            }
        }
    }
    return FAIL;
}



int add_edges(Vertex front,Vertex back,Graph* g){
    if(g->numOfVertex==0)
    {
        printf("It's empty!!!\n");
        exit(-1);
    }
    if(exist(front,back,g)==SUCCESS){
        printf("It's already exists\n");
        return 0;
    }
    AdjHead* _front=find_Vertex(g,front);
    AdjHead* _back=find_Vertex(g,back);

    Vertex_Edge* new_one=(Vertex_Edge*)malloc(sizeof(Vertex_Edge));
    new_one->name=back;

    new_one->next=_front->first_edge;
    _front->first_edge=new_one;

    Vertex_Edge* add_one=(Vertex_Edge*)malloc(sizeof(Vertex_Edge));
    add_one->name=front;
    add_one->next=_back->first_edge;
    _back->first_edge=add_one;

    g->numOfEdge++;
    return SUCCESS;
}

void print_(Graph *g){
    for(int i=0;i<g->numOfVertex;i++)
    {
        printf("%c\t",g->adj[i].name);
        Vertex_Edge * fedge=g->adj[i].first_edge;

        while(fedge!=NULL){
            printf("%c\t",fedge->name);
            fedge=fedge->next;
        }
        printf("\n");
    }
}

void test(Graph* g){
    for(int i=0;i<g->numOfVertex;i++)
        g->adj[i].name=(char)('a'+i);

    add_edges('a','b',g);
    add_edges('a','c',g);
    add_edges('c','d',g);
    add_edges('c','e',g);
    add_edges('e','g',g);
    add_edges('g','f',g);
    add_edges('g','h',g);
    add_edges('g','i',g);
    print_(g);
}


int hash(Vertex v){
    return v-'a';
}


void dfs(Graph* g,Vertex v){
    AdjHead *head=find_Vertex(g,v);
    isVisited[head->name-'a']=TRUE;
    printf("%c\t",head->name);
    Vertex_Edge * firstedge=head->first_edge;
    while(firstedge!=NULL){
        if(isVisited[firstedge->name-'a']==FALSE)
            dfs(g,firstedge->name);
        firstedge=firstedge->next;
    }

}

void DepthFirstSearch(Graph* g){


    for(int i=0;i<g->numOfVertex;i++)
        isVisited[i]=FALSE;

    for(int i=0;i<g->numOfVertex;i++){
        AdjHead head=g->adj[i];
        int index=hash(head.name);

        if(isVisited[index]==FALSE)
            dfs(g,head.name);
    }

}
/******PATH**********/
//Find all the ways from v
//Also use DepthFirstSearch
//查找从起点v开始的所有路径，使用了edgeTo来记录当前结点的前驱
void dfs_path(Graph* g,Vertex v){
    AdjHead *head=find_Vertex(g,v);
    isVisited[head->name-'a']=TRUE;
    Vertex_Edge * fedge=head->first_edge;

    while(fedge!=NULL){
        if(isVisited[fedge->name-'a']==FALSE){
            edgeTo[fedge->name-'a']=v;
            dfs_path(g,fedge->name);
        }
        fedge=fedge->next;
    }
}

void pathTo(Graph* g,Vertex v,Vertex start){
    if(isVisited[v-'a']==FALSE)
    {
        printf("There is no way to v\n");
        exit(-1);
    }
    Index=0;
    for(char begin=v;begin!=start;begin=edgeTo[begin-'a']){
        path[Index++]=begin;
    }

    path[Index++]=start;
}

void DepthFirstPaths(Graph* g,Vertex v){//looking for all ways from v

    for(int i=0;i<g->numOfVertex;i++)
        isVisited[i]=FALSE;

    dfs_path(g,v);
}
/******PATH************/



int main(void){
    Graph *g=create_graph(9);
    test(g);
    //DepthFirstSearch(g);
    DepthFirstPaths(g,'a');
    for(int i=1;i<g->numOfVertex;i++)
    {
        pathTo(g,'a'+i,'a');
        for(int i=Index-1;i>0;i--){
        printf("%c------>",path[i]);
    }
    printf("%c\n",path[0]);
    }
    printf("\n");
    return 0;
}
