#ifndef GRAPH_JRB_H
#define GRAPH_JRB_H

#include "dllist.h"
#include "fields.h"
#include "jval.h"
#include "jrb.h"

#define true 1
#define false 0
#define UNDIRECTED 0
#define DIRECTED 1
#define INT_MAX 2147483647
#define INFINITIVE_VALUE 10000000

typedef struct
{
    JRB edges;
    JRB vertices;
} Graph;

Graph createGraph();

// flag = 1 neu vo huong flag = 0  neu co huong
void addVertex(Graph graph, int id, char *name);
void *getVertex(Graph graph, int id);
int getNumOfV(Graph graph);
void delVertex(Graph graph,int v);

void addEdge(Graph graph, int v1, int v2, double weight,int flag);
double getEdgeValue(Graph graph, int v1, int v2);
int hasEdge(Graph graph, int v1, int v2);
int getNumOfEdge(Graph graph);
void delEdge(Graph graph,int v1,int v2, int flag);
void updateWeight (Graph graph,int v1,int v2,double n_weight,int flag);

int indegree(Graph graph, int v, int *output);
int outdegree(Graph graph, int v, int *output);

// return 0: co chu trinh 
// return 1: khong co chu trinh
int DAG(Graph graph);
int DFS_DAG(Graph graph, int start);

int topologicalSort(Graph graph, int *output);

int DFS(Graph graph, int start, int stop, int *path);
//BFS
int shortest_noWeight_path(Graph graph, int start, int stop, int *path);

//Dijisktra
double shortestPath(Graph graph, int start, int stop, int *path, int *numVertices); 

void dropGraph(Graph graph);

#endif /* GRAPH_JRB_H */