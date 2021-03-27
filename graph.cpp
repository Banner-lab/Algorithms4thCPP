//
// Created by leexm on 2021/3/27.
//

//
// Created by leexm on 2021/3/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <iostream>
#include <vector>

#define  TABLE_SIZE 15
#define  SUCCESS 1
#define  FAIL 0
#define  TRUE 1
#define  FALSE 0

using namespace std;

typedef char Vertex;
typedef int  Edge;
typedef int  Weight;

//int isVisited[TABLE_SIZE]={Undiscovered};
//char parent[TABLE_SIZE];
int  isVisited[TABLE_SIZE];
char edgeTo[TABLE_SIZE];
char path[TABLE_SIZE];
int  Index=0;
bool Visited[TABLE_SIZE];
int  count=0;
int  id[TABLE_SIZE];

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

int hashs(Vertex v){
    return v-'a';
}

Graph* create_graph(int numV);
AdjHead*  find_Vertex(Graph* g,Vertex a);
int exist(Vertex a,Vertex b,Graph* g);
int add_edges(Vertex front,Vertex back,Graph* g);
void print_(Graph *g);
void test(Graph* g);
void dfs(Graph* g,Vertex v);
void DepthFirstSearch(Graph* g);

void dfs_path(Graph* g,Vertex v);
void pathTo(Graph* g,Vertex v,Vertex start);
void DepthFirstPaths(Graph* g,Vertex v);

void BreadthFirstSearch(Graph* g,Vertex v);
void BreadthFirstPath(Graph* g,Vertex v);
vector<char> path2(Graph* g,Vertex v,Vertex start);

/*************************/

bool connected(Vertex v,Vertex w);
void CC(Graph* g);
void dfs_cc(Graph* g,Vertex v);

int main(void){
    Graph *g=create_graph(15);
    test(g);
    //DepthFirstSearch(g);
    //DepthFirstPaths(g,'a');
    /*for(int i=1;i<g->numOfVertex;i++)
    {
        pathTo(g,'a'+i,'a');
        for(int i=Index-1;i>0;i--){
            printf("%c------>",path[i]);
        }
        printf("%c\n",path[0]);
    }*/
    //BreadthFirstSearch(g,'a');
    //BreadthFirstPath(g,'a');
    //vector<char> s=path2(g,'i','a');
    //for(int i=s.size()-1;i>0;i--)
    //{
    //   cout<<s[i]<<"------>";
    //}
    //cout<<s[0]<<endl;

    CC(g);
    if(connected('a','h'))
        printf("Connected\n");
    else
        printf("Success\n");

    cout<<count<<endl;

    printf("\n");
    return 0;
}


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
    return nullptr;
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
    add_edges('j','k',g);
    add_edges('j','l',g);
    add_edges('m','n',g);
    add_edges('m','o',g);

    print_(g);
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
        int index=hashs(head.name);

        if(isVisited[index]==FALSE)
            dfs(g,head.name);
    }
}

/******PATH**********/
//Find all the ways from v
//Also use DepthFirstSearch
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


/******BFS*********/
void BreadthFirstSearch(Graph* g,Vertex v){
    if(g==nullptr){
        cout<<"This graph is EMPTY!\n";
        exit(-1);
    }

    for(int i=0;i<g->numOfVertex;i++)
        isVisited[i]=FALSE;

    queue<Vertex> sup;
    sup.push(v);

    while(!sup.empty()){
        Vertex temp=sup.front();
        sup.pop();
        isVisited[temp-'a']=TRUE;
        cout<<temp<<"\t";
        AdjHead * head=find_Vertex(g,temp);
        Vertex_Edge* cur=head->first_edge;


        while(cur!=nullptr){
            if(isVisited[cur->name-'a']==FALSE)
                sup.push(cur->name);
            cur=cur->next;
        }
    }
}
/******************/

void BreadthFirstPath(Graph* g,Vertex v){
    if(g==nullptr){
        cout<<"This graph is EMPTY!\n";
        exit(-1);
    }

    for(int i=0;i<g->numOfVertex;i++)
    isVisited[i]=FALSE;

    queue<Vertex> sup;
    sup.push(v);

    while(!sup.empty()){
        Vertex temp=sup.front();
        sup.pop();
        isVisited[temp-'a']=TRUE;

        AdjHead * head=find_Vertex(g,temp);
        Vertex_Edge* cur=head->first_edge;


        while(cur!=nullptr){
            if(isVisited[cur->name-'a']==FALSE)
            {
                sup.push(cur->name);
                edgeTo[cur->name-'a']=temp;
            }
            cur=cur->next;
        }
    }
}


vector<char> path2(Graph* g,Vertex v,Vertex start){
    if(isVisited[start-'a']==FALSE){
        exit(-1);
    }
    vector<char> res;
    for(char end=v;end!=start;end=edgeTo[end-'a']){
        res.push_back(end);
    }
    res.push_back(start);
    return res;
}

void CC(Graph* g){
    for(bool v:Visited)
        v=false;
    for(int i=0;i<g->numOfVertex;i++)
    {
        if(Visited[i]==false){
            dfs_cc(g,'a'+i);
            count++;
        }
    }
}

void dfs_cc(Graph* g,Vertex v){
    Visited[v-'a']= true;
    id[v-'a']=count;
    AdjHead * head=find_Vertex(g,v);
    Vertex_Edge* fedge=head->first_edge;
    while(fedge!=nullptr){
        if(Visited[fedge->name-'a']==false)
            dfs_cc(g,fedge->name);
        fedge=fedge->next;
    }
}

bool connected(Vertex v,Vertex w){
    return id[v-'a']==id[w-'a'];
}

