#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>
#include "meio.h"

typedef struct AdjListNode {
    int dest;
    struct AdjListNode* next;
} AdjListNode;

typedef struct {
    Coords coords;
    AdjListNode* head;
} Vertex;

typedef struct {
    int numVertices;
    Vertex* vertices;
} Graph;

Graph* createGraph();
void addVertex(Graph* graph, double minLat, double maxLat, double minLong, double maxLong);
void addEdge(Graph* graph, int src, int dest);
int findVertex(Graph* graph, double latitude, double longitude);
void freeGraph(Graph* graph);
Graph* inicia_posicao();

#endif
