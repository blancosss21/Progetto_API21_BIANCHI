#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LENGTH 1000000

void AggiungiGrafo();
//void StampaGrafo(int vertices);

//int Graph[LENGTH][LENGTH];

int main(void) {
    int d;
    int k;
    //int vertices, edges;
//u is the current or source vertex
//v is the next or destination vertex
//w is the edge weight or path cost
    //int u, v, w;
    int i;
    //int j;
//Graph is the graph representation in adjacency matrix

    if (scanf("%d %d", &d, &k)){};
    printf("%d %d", d, k);


    for (i = 0; i < d; i++) {
        AggiungiGrafo(d);
        //StampaGrafo(d);
    }

    return 0;

}

void AggiungiGrafo() {
    char *res;
    //char s;
    //int d;

    char riga[LENGTH];

    res=(char*)malloc(sizeof(char));

    /* legge e stampa ogni riga */
    while (res != NULL) {
        res = fgets(riga, LENGTH, stdin);
        if(res == NULL)
            break;
        printf("%s", riga);
    }
    /*int i;
    int j;
    int edges, u, v, w;
    //if(scanf("%d%d", &vertices, &edges)){};

    // Reset graph
    for (i = 0; i < vertices; ++i)
        for (j = 0; j < vertices; ++j)
            Graph[i][j] = 0;

    // Input Graph
    for (i = 0; i < edges; ++i) {
        res = fgets(riga, LENGTH, stdin);
        //if(scanf("%d%d%d", &u, &v, &w)){};
        Graph[u][v] = w;
    }*/
}
/*void StampaGrafo(int vertices) {
    int i;
    int j;
    // Print the current Graph
    //printf("\n");
    printf("Graph:\n");
    for (i = 0; i < vertices; ++i) {
        for (j = 0; j < vertices; ++j)
            printf("%d ", Graph[i][j]);
        printf("\n");
            }
}*/