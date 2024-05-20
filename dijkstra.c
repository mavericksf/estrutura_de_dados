#include <stdio.h>
#include <limits.h>

#define V 5 // N�mero de v�rtices no grafo

// Fun��o para encontrar o v�rtice com a dist�ncia m�nima, a partir do conjunto de v�rtices ainda n�o inclu�dos no caminho mais curto
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

// Fun��o que implementa o algoritmo de Dijkstra para um grafo representado como uma matriz de adjac�ncias
void dijkstra(int graph[V][V], int src) {
    int dist[V]; // Vetor de dist�ncias
    int sptSet[V]; // Conjunto de v�rtices j� processados

    // Inicializa as dist�ncias como infinito e sptSet como falso
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
    }

    // A dist�ncia do v�rtice de origem para ele mesmo � sempre 0
    dist[src] = 0;

    // Encontra o caminho mais curto para todos os v�rtices
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = 1;

        // Atualiza as dist�ncias dos v�rtices adjacentes do v�rtice escolhido
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Imprime as dist�ncias do v�rtice de origem para todos os outros v�rtices
    printf("Dist�ncias do v�rtice %d para os outros v�rtices:\n", src);
    for (int i = 0; i < V; i++) {
        printf("%d -> %d: %d\n", src, i, dist[i]);
    }
}

int main() {
    // Exemplo de grafo representado como matriz de adjac�ncias
    int graph[V][V] = {
        {0, 4, 0, 0, 0},
        {4, 0, 8, 0, 0},
        {0, 8, 0, 7, 0},
        {0, 0, 7, 0, 9},
        {0, 0, 0, 9, 0}
    };

    int source = 0; // V�rtice de origem
    dijkstra(graph, source);

    return 0;
}
