#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "grafo.h"

Graph* createGraph() {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = 0;
    graph->vertices = NULL;
    return graph;
}

void addVertex(Graph* graph, double minLat, double maxLat, double minLong, double maxLong) {
    graph->numVertices++;
    graph->vertices = (Vertex*)realloc(graph->vertices, graph->numVertices * sizeof(Vertex));
    graph->vertices[graph->numVertices - 1].coords.latitude = (minLat + maxLat) / 2.0;
    graph->vertices[graph->numVertices - 1].coords.longitude = (minLong + maxLong) / 2.0;
    graph->vertices[graph->numVertices - 1].head = NULL;
}

AdjListNode* newAdjListNode(int dest) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

void addEdge(Graph* graph, int src, int dest) {
    AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->vertices[src].head;
    graph->vertices[src].head = newNode;
}

int findVertex(Graph* graph, double latitude, double longitude) {
    double minDistance = INFINITY;
    int vertexIndex = -1;

    for (int i = 0; i < graph->numVertices; i++) {
        double distance = sqrt(pow(graph->vertices[i].coords.latitude - latitude, 2) +
                               pow(graph->vertices[i].coords.longitude - longitude, 2));
        if (distance < minDistance) {
            minDistance = distance;
            vertexIndex = i;
        }
    }

    return vertexIndex;
}

void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        AdjListNode* curr = graph->vertices[i].head;
        while (curr != NULL) {
            AdjListNode* next = curr->next;
            free(curr);
            curr = next;
        }
    }
    free(graph->vertices);
    free(graph);
}
