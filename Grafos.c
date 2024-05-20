#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar um nó do grafo
struct Node {
    int vertex;
    struct Node* next;
};

// Estrutura para representar o grafo
struct Graph {
    int numVertices;
    struct Node** adjLists;
};

struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    graph->adjLists = (struct Node**)malloc(vertices * sizeof(struct Node*));

    int i;
    for (i = 0; i < vertices; i++)
        graph->adjLists[i] = NULL;

    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    // Adiciona uma aresta do vértice src para o vértice dest

    // Adiciona o vértice dest à lista de adjacência do vértice src
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Se o grafo for não-direcionado, adicione também uma aresta do vértice dest para o vértice src
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void printGraph(struct Graph* graph) {
    int v;
    for (v = 0; v < graph->numVertices; v++) {
        struct Node* temp = graph->adjLists[v];
        printf("Adjacency list of vertex %d: ", v);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

// Busca em profundidade

void DFS(struct Graph* graph, int vertex, int* visited) {
    // Marca o vértice como visitado
    visited[vertex] = 1;
    printf("%d ", vertex);

    // Percorre todos os vértices adjacentes ao vértice atual
    struct Node* temp = graph->adjLists[vertex];
    while (temp) {
        int adjVertex = temp->vertex;
        if (!visited[adjVertex]) {
            DFS(graph, adjVertex, visited);
        }
        temp = temp->next;
    }
}

void depthFirstSearch(struct Graph* graph, int startVertex) {
    // Cria um array para marcar os vértices visitados
    int* visited = (int*)calloc(graph->numVertices, sizeof(int));

    printf("DFS traversal starting from vertex %d: ", startVertex);
    DFS(graph, startVertex, visited);
    printf("\n");

    free(visited);
}

// Busca em largura

void BFS(struct Graph* graph, int startVertex, int* visited) {
    // Cria uma fila para a busca em largura
    int* queue = (int*)malloc(graph->numVertices * sizeof(int));
    int front = 0;
    int rear = 0;

    // Marca o vértice inicial como visitado e enfileira-o
    visited[startVertex] = 1;
    queue[rear++] = startVertex;

    printf("BFS traversal starting from vertex %d: ", startVertex);

    while (front < rear) {
        // Desenfileira um vértice da fila e imprime-o
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        // Percorre todos os vértices adjacentes ao vértice atual
        struct Node* temp = graph->adjLists[currentVertex];
        while (temp) {
            int adjVertex = temp->vertex;
            if (!visited[adjVertex]) {
                // Marca o vértice adjacente como visitado e o enfileira
                visited[adjVertex] = 1;
                queue[rear++] = adjVertex;
            }
            temp = temp->next;
        }
    }

    free(queue);
}

int main() {
    // Cria um grafo com 5 vértices
    struct Graph* graph = createGraph(5);

    // Adiciona arestas
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    // Imprime o grafo
    printGraph(graph);

    return 0;
}
