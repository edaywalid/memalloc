#include "../memalloc.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_NODES 100

typedef struct Edge {
  int dest;
  int weight;
  struct Edge *next;
} Edge;

typedef struct Graph {
  Edge *adjList[MAX_NODES];
  int numNodes;
} Graph;

void initGraph(Graph *graph, int numNodes) {
  graph->numNodes = numNodes;
  for (int i = 0; i < numNodes; i++) {
    graph->adjList[i] = NULL;
  }
}

void insertEdge(Graph *graph, int src, int dest, int weight) {
  Edge *newEdge = (Edge *)malloc(sizeof(Edge));
  newEdge->dest = dest;
  newEdge->weight = weight;
  newEdge->next = graph->adjList[src];
  graph->adjList[src] = newEdge;
}

void deleteEdge(Graph *graph, int src, int dest) {
  Edge *prev = NULL;
  Edge *curr = graph->adjList[src];

  while (curr != NULL && curr->dest != dest) {
    prev = curr;
    curr = curr->next;
  }
  if (curr != NULL) {
    if (prev == NULL) {
      graph->adjList[src] = curr->next;
    } else {
      prev->next = curr->next;
    }
    free(curr);
  }
}

void bfs(Graph *graph, int start) {
  bool visited[MAX_NODES] = {false};
  int queue[MAX_NODES];
  int front = 0, rear = 0;

  visited[start] = true;
  queue[rear++] = start;

  while (front != rear) {
    int current = queue[front++];
    printf("%d ", current);

    for (Edge *edge = graph->adjList[current]; edge != NULL;
         edge = edge->next) {
      if (!visited[edge->dest]) {
        visited[edge->dest] = true;
        queue[rear++] = edge->dest;
      }
    }
  }
  printf("\n");
}

void dfsUtil(Graph *graph, int v, bool visited[]) {
  visited[v] = true;
  printf("%d ", v);

  for (Edge *edge = graph->adjList[v]; edge != NULL; edge = edge->next) {
    if (!visited[edge->dest]) {
      dfsUtil(graph, edge->dest, visited);
    }
  }
}

void dfs(Graph *graph, int start) {
  bool visited[MAX_NODES] = {false};
  dfsUtil(graph, start, visited);
  printf("\n");
}

void dijkstra(Graph *graph, int start) {
  int dist[MAX_NODES];
  bool sptSet[MAX_NODES] = {false};

  for (int i = 0; i < graph->numNodes; i++) {
    dist[i] = INT_MAX;
  }
  dist[start] = 0;

  for (int count = 0; count < graph->numNodes - 1; count++) {
    int minDist = INT_MAX;
    int u;

    for (int v = 0; v < graph->numNodes; v++) {
      if (!sptSet[v] && dist[v] <= minDist) {
        minDist = dist[v];
        u = v;
      }
    }

    sptSet[u] = true;

    for (Edge *edge = graph->adjList[u]; edge != NULL; edge = edge->next) {
      int v = edge->dest;
      int weight = edge->weight;

      if (!sptSet[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
        dist[v] = dist[u] + weight;
      }
    }
  }

  printf("Vertex\tDistance from Source\n");
  for (int i = 0; i < graph->numNodes; i++) {
    printf("%d\t%d\n", i, dist[i]);
  }
}

int main() {
  Graph graph;
  initGraph(&graph, 6);

  insertEdge(&graph, 0, 1, 4);
  insertEdge(&graph, 0, 2, 1);
  insertEdge(&graph, 1, 3, 1);
  insertEdge(&graph, 2, 1, 2);
  insertEdge(&graph, 2, 3, 5);
  insertEdge(&graph, 3, 4, 3);
  insertEdge(&graph, 4, 5, 2);

  bfs(&graph, 0);

  dfs(&graph, 0);

  dijkstra(&graph, 0);

  deleteEdge(&graph, 0, 2);

  bfs(&graph, 0);

  return 0;
}
