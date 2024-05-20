#include <stdio.h>
#include <limits.h>

#define V 5 // Número de vértices no grafo

// Função para encontrar o vértice com a distância mínima, a partir do conjunto de vértices ainda não incluídos no caminho mais curto
int minDistance(int dist[], int sptSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++) {
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Função que implementa o algoritmo de Dijkstra para um grafo representado como uma matriz de adjacências
void dijkstra(int graph[V][V], int src) {
    int dist[V]; // Vetor de distâncias
    int sptSet[V]; // Conjunto de vértices já processados

    // Inicializa as distâncias como infinito e sptSet como falso
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
    }

    // A distância do vértice de origem para ele mesmo é sempre 0
    dist[src] = 0;

    // Encontra o caminho mais curto para todos os vértices
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = 1;

        // Atualiza as distâncias dos vértices adjacentes do vértice escolhido
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Imprime as distâncias do vértice de origem para todos os outros vértices
    printf("Distâncias do vértice %d para os outros vértices:\n", src);
    for (int i = 0; i < V; i++) {
        printf("%d -> %d: %d\n", src, i, dist[i]);
    }
}

int main() {
    // Exemplo de grafo representado como matriz de adjacências
    int graph[V][V] = {
        {0, 4, 0, 0, 0},
        {4, 0, 8, 0, 0},
        {0, 8, 0, 7, 0},
        {0, 0, 7, 0, 9},
        {0, 0, 0, 9, 0}
    };

    int source = 0; // Vértice de origem
    dijkstra(graph, source);

    return 0;
}
