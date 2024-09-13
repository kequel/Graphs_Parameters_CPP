#include <cstdio>
#include <cstdlib>
#include "queue.h"
#define LEFT -1
#define RIGHT 1

using namespace std;

void insertionSort(int* degreeArray, int* vertexesArray, long long size) {
    for (int i = 1; i < size; ++i) {
        int key = degreeArray[i];
        int keyV = vertexesArray[i];
        int j = i - 1;
        while (j >= 0 && degreeArray[j] < key) {
            degreeArray[j + 1] = degreeArray[j];
            vertexesArray[j + 1] = vertexesArray[j];
            --j;
        }
        degreeArray[j + 1] = key;
        vertexesArray[j + 1] = keyV;
    }
}

void bfsCheck(int** arr, long long size, int start, bool* visited, Queue* q) {
    addToQueue(q, start);
    visited[start] = true;

    while (!isQueueEmpty(q)) {
        int toCheck = front(q);
        popQueue(q);
        for (int i = 0; arr[toCheck][i] != -1; i++) {
            int neighbor = arr[toCheck][i];
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                addToQueue(q, neighbor);
            }
        }
    }
}

int findNumberOfComponents(int** arr, long long size) {
    bool* visited = (bool*)malloc(size * sizeof(bool));
    for (int i = 0; i < size; i++) visited[i] = false;
    int count = 0;
    Queue q;
    initQueue(&q);

    for (int i = 0; i < size; i++) {
        if (!visited[i]) {
            bfsCheck(arr, size, i, visited, &q);
            count++;
        }
    }
    free(visited);
    clearQueue(&q);
    return count;
}

bool giveOppositeSide(int* arr, int neighbor_side, int* divider, Queue* q) {
    int side = (neighbor_side == LEFT) ? RIGHT : LEFT;
    for (int i = 0; arr[i] != -1; i++) {
        int neighbor = arr[i];
        if (divider[neighbor] == 0) {
            divider[neighbor] = side;
            addToQueue(q, neighbor);
        } else if (divider[neighbor] == neighbor_side) {
            return false;
        }
    }
    return true;
}

char isBipart(int** arr, long long size) {
    Queue q;
    initQueue(&q);
    int* divider = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) divider[i] = 0; // 0 - unvisited, LEFT - -1, RIGHT - 1

    for (int i = 0; i < size; ++i) {
        if (divider[i] == 0) {
            divider[i] = LEFT;
            addToQueue(&q, i);

            while (!isQueueEmpty(&q)) {
                int check = front(&q);
                popQueue(&q);
                if (!giveOppositeSide(arr[check], divider[check], divider, &q)) {
                    free(divider);
                    clearQueue(&q);
                    return 'F';
                }
            }
        }
    }
    free(divider);
    clearQueue(&q);
    return 'T';
}

long long countComplementsEdges(int* degreeArray, long long size) {
    long long full_edges = (size * (size - 1) / 2);
    long long original_edges = 0;
    for (int i = 0; i < size; i++) {
        long long toadd = degreeArray[i];
        original_edges += toadd;
    }
    original_edges /= 2;
    return full_edges - original_edges;
}

bool checkNeighbourVerticesForColor(int** arr, int vertex, int color, int* colorsArray) {
    for (int i = 0; arr[vertex][i] != -1; i++) {
        int neighbour = arr[vertex][i];
        if (colorsArray[neighbour] == color) {
            return false;
        }
    }
    return true;
}

void colorVerticesGreedy(int** arr, long long size, int* colorsArray) {
    colorsArray[0] = 1;
    for (int i = 1; i < size; ++i) {
        int color = 1;
        while (!checkNeighbourVerticesForColor(arr, i, color, colorsArray)) {
            color++;
        }
        colorsArray[i] = color;
    }
}

void colorVerticesLargestFirst(int** arr, long long size, int* colorsArray, int* verticesArray) {
    for (int i = 0; i < size; ++i) {
        int ver = verticesArray[i];
        int color = 1;
        while (!checkNeighbourVerticesForColor(arr, ver, color, colorsArray)) {
            color++;
        }
        colorsArray[ver] = color;
    }
}


int findNumberOfC4subgraphs(int** arr, long long size) {
    int count = 0;

    for (int start = 0; start < size; start++) {
        for (int i = 0; arr[start][i] != -1; i++) {
            for (int j = i + 1; arr[start][j] != -1; j++) {
                int v1 = arr[start][i];
                int v2 = arr[start][j];

                for (int k = 0; arr[v1][k] != -1; k++) {
                    int v3 = arr[v1][k];
                    if (v3 == start || v3 == v2) continue;

                    for (int l = 0; arr[v2][l] != -1; l++) {
                        int v4 = arr[v2][l];
                        if (v4 == start || v4 == v1) continue;
                        if (v3 == v4) {
                            count++;
                        }
                    }
                }
            }
        }
    }

    return count / 4;
}

int main() {
    int number_of_sets;
    scanf("%d", &number_of_sets);
    for (int i = 0; i < number_of_sets; i++) {
        long long number_of_vertexes;
        scanf("%lld", &number_of_vertexes);

        int** graph_number_of_neighbours = (int**)malloc(number_of_vertexes * sizeof(int*));
        int* degree_sequence = (int*)malloc(number_of_vertexes * sizeof(int));
        int* vertexes_sequence = (int*)malloc(number_of_vertexes * sizeof(int));

        for (int j = 0; j < number_of_vertexes; j++) {
            int number_of_neighbours;
            scanf("%d", &number_of_neighbours);
            vertexes_sequence[j] = j;
            degree_sequence[j] = number_of_neighbours;

            graph_number_of_neighbours[j] = (int*)malloc((number_of_neighbours + 1) * sizeof(int));
            for (int k = 0; k < number_of_neighbours; k++) {
                int neighbour;
                scanf("%d", &neighbour);
                graph_number_of_neighbours[j][k] = neighbour - 1; // 0-n
            }
            graph_number_of_neighbours[j][number_of_neighbours] = -1; // end of list
        }

        insertionSort(degree_sequence, vertexes_sequence, number_of_vertexes);

        //1.
        for (int j = 0; j < number_of_vertexes; j++) {
            printf("1: %d ", degree_sequence[j]);
        }
        printf("\n");

        //2.
        int number_of_components;
        number_of_components = findNumberOfComponents(graph_number_of_neighbours, number_of_vertexes);
        printf("2: %d\n", number_of_components);

        //3.
        char bipartiteness;
        bipartiteness = isBipart(graph_number_of_neighbours, number_of_vertexes);
        printf("3: %c\n", bipartiteness);

        //4a.
        int* colorsArrayA = (int*)malloc(number_of_vertexes * sizeof(int));
        for (int j = 0; j < number_of_vertexes; j++) colorsArrayA[j] = 0;
        colorVerticesGreedy(graph_number_of_neighbours, number_of_vertexes, colorsArrayA);
        for (int j = 0; j < number_of_vertexes; j++) {
            printf("4a: %d ", colorsArrayA[j]);
        }
        printf("\n");
        free(colorsArrayA);

        //4b.
        int* colorsArrayB = (int*)malloc(number_of_vertexes * sizeof(int));
        for (int j = 0; j < number_of_vertexes; j++) colorsArrayB[j] = 0;
        colorVerticesLargestFirst(graph_number_of_neighbours, number_of_vertexes, colorsArrayB, vertexes_sequence);
        for (int j = 0; j < number_of_vertexes; j++) {
            printf("4b: %d ", colorsArrayB[j]);
        }
        printf("\n");
        free(colorsArrayB);

        //4c. - TO DO

        //5. - TO DO BETTER
        int C4_subgraphs;
        C4_subgraphs = findNumberOfC4subgraphs(graph_number_of_neighbours, number_of_vertexes);
        printf("5: %d\n", C4_subgraphs);

        //6.
        long long graph_complements_edges;
        graph_complements_edges = countComplementsEdges(degree_sequence, number_of_vertexes);
        printf("6: %lld\n", graph_complements_edges);

        // Free memory
        for (int j = 0; j < number_of_vertexes; j++) {
            free(graph_number_of_neighbours[j]);
        }
        free(graph_number_of_neighbours);
        free(degree_sequence);
        free(vertexes_sequence);
    }

    return 0;
}
