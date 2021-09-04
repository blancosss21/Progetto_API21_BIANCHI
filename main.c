#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define MAX 30000

unsigned int **Matrice;

struct prestazioneGrafo {
    unsigned int numeroGrafo;
    unsigned int costoGrafo;
};

unsigned int minDistance(unsigned int dist[], bool sptSet[], unsigned int d) {
    // Initialize min value
    unsigned int min = INT_MAX, min_index =0;

    for (unsigned int v = 0; v < d; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

unsigned int myAtoi(char *str) {
    unsigned int res = 0;
    for (unsigned int i = 0; str[i] != '\0' && str[i] != '\n'; ++i)
        res = res * 10 + str[i] - '0';
    return res;
}

unsigned int dijkstra(unsigned int d) {
    unsigned int dist[d];
    bool sptSet[d];
    unsigned int somma = 0;
    for (unsigned int i = 0; i < d; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
    dist[0] = 0;
    for (unsigned int count = 0; count < d - 1; count++) {
        unsigned int u = minDistance(dist, sptSet, d);
        sptSet[u] = true;
        for (unsigned int v = 0; v < d; v++)
            if (!sptSet[v] && Matrice[u][v] && dist[u] != INT_MAX
                && dist[u] + Matrice[u][v] < dist[v])
                dist[v] = dist[u] + Matrice[u][v];
    }
    for (unsigned int i = 0; i < d; i++)
        somma = somma + dist[i];
    return somma;
}

unsigned int AggiungiGrafo(unsigned int d) {
    char riga[MAX];
    char *tok;
    unsigned int c;
    for (c = 0; c < d; c++) {
        if (fgets(riga, MAX, stdin) == NULL) {
            exit(1);
        }
        tok = strtok(riga, ",");
        Matrice[c][0] = myAtoi(tok);
        for (unsigned int e = 1; e < d; e++) {
            tok = strtok(NULL, ",");
            Matrice[c][e] = myAtoi(tok);
        }
    }
    return dijkstra(d);
}


void aggiornaCamminiMinimi(struct prestazioneGrafo *camminiMinimi, unsigned int k, unsigned int nuovoCammino, unsigned int numGrafo) {
    unsigned int i;
    for (i = 0; i < k; i++) {
        if(camminiMinimi[i].numeroGrafo == 0){
            camminiMinimi[i].numeroGrafo = numGrafo;
            camminiMinimi[i].costoGrafo = nuovoCammino;
            return;
        }
    }
    unsigned int posMax = 0;
    unsigned int max = camminiMinimi[0].costoGrafo;
    for (i = 0; i < k; i++) {
        if(camminiMinimi[i].costoGrafo > max){
            max = camminiMinimi[i].costoGrafo;
            posMax = i;
        }
    }
    if (nuovoCammino < max){
        camminiMinimi[posMax].costoGrafo = nuovoCammino;
        camminiMinimi[posMax].numeroGrafo = numGrafo;
    }
    return;
}


int main() {
    unsigned int d;
    unsigned int k;

    unsigned int i;
    unsigned int nuovoCammino;
    unsigned int numGrafo = 1;


    if (scanf("%u %u\n", &d, &k) != 2) {
        return -1;
    }
    struct prestazioneGrafo camminiMinimi[k];
    if (d == 0) {
        return -1;
    }
    Matrice = (unsigned int **) malloc(d * sizeof(unsigned int *));
    for (i = 0; i < d; i++) {
        Matrice[i] = (unsigned int *) malloc(d * sizeof(unsigned int));
    }

    for (i = 0; i < k; i++) {
        camminiMinimi[i].numeroGrafo = 0;
        camminiMinimi[i].numeroGrafo = 0;
    }
    char str1[] = "AggiungiGrafo";
    char str2[] = "TopK";
    char *res = malloc(14 * sizeof(char));  //prima per 13
    while (1) {
        if (scanf("%s\n", res) != 1) {
            return -1;
        }
        if (feof(stdin))
            break;
        if (!strcmp(res, str1)) {
            nuovoCammino = AggiungiGrafo(d);
            aggiornaCamminiMinimi(camminiMinimi, k, nuovoCammino, numGrafo);
        } else if (!strcmp(res, str2))
            printf("ciao");
        else
            break;
        numGrafo++;
    }
    return 0;
}




