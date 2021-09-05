#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define MAX 30000

int **Matrice;

struct prestazioneGrafo {
    int numeroGrafo;
    int costoGrafo;
};

int minDistance(int dist[], bool sptSet[], int d) {
    int min = INT_MAX, min_index = 0;
    for (int v = 0; v < d; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

int myAtoi(char *str) {
    int res = 0;
    for (int i = 0; str[i] != '\0' && str[i] != '\n'; ++i)
        res = res * 10 + str[i] - '0';
    return res;
}

int dijkstra(int d) {
    int dist[d];
    bool sptSet[d];
    int somma = 0;
    for (int i = 0; i < d; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
    dist[0] = 0;
    for (int count = 0; count < d - 1; count++) {
        int u = minDistance(dist, sptSet, d);
        sptSet[u] = true;
        for (int v = 0; v <= d; v++)
            if (!sptSet[v] && Matrice[u][v] && dist[u] != INT_MAX
                && dist[u] + Matrice[u][v] < dist[v]) {
                dist[v] = Matrice[u][v] + dist[u];
            }
    }
    for (int i = 0; i < d; i++) {
        if (dist[i] < INT_MAX) {
            somma = somma + dist[i];
        }
    }
    return somma;
}

void aggiungiGrafo(int d) {
    char riga[MAX];
    char *tok;
    for (int c = 0; c < d; c++) {
        if (fgets(riga, MAX, stdin) == NULL) {
            exit(1);
        }
        tok = strtok(riga, ",");
        Matrice[c][0] = myAtoi(tok);
        for (int e = 1; e < d; e++) {
            tok = strtok(NULL, ",");
            Matrice[c][e] = myAtoi(tok);
        }
    }
}


void aggiornaCamminiMinimi(struct prestazioneGrafo *camminiMinimi, int k, int nuovoCammino, int numGrafo) {
    for (int i = 0; i < k; i++) {
        if (camminiMinimi[i].numeroGrafo == -1) {
            camminiMinimi[i].numeroGrafo = numGrafo;
            camminiMinimi[i].costoGrafo = nuovoCammino;
            return;
        }
    }
    int posMax = 0;
    int max = camminiMinimi[0].costoGrafo;
    for (int i = 0; i < k; i++) {
        if (camminiMinimi[i].costoGrafo > max) {
            max = camminiMinimi[i].costoGrafo;
            posMax = i;
        }
    }
    if (nuovoCammino < max) {
        camminiMinimi[posMax].costoGrafo = nuovoCammino;
        camminiMinimi[posMax].numeroGrafo = numGrafo;
    }
}

/*void topkCompleto(struct prestazioneGrafo *camminiMinimi, int k) {
    for (int i = 0; i < k; ++i) {
        if (camminiMinimi[i].numeroGrafo != -1)
            printf("il grafo %d ha un percorso di %d\n", camminiMinimi[i].numeroGrafo, camminiMinimi[i].costoGrafo);
    }
}*/

void topk(struct prestazioneGrafo *camminiMinimi, int k) {

    for (int i = 0; i < k; ++i) {
        printf("%d ", camminiMinimi[i].numeroGrafo);


    }
}


int main() {
    int d;
    int k;
    int numGrafo = 0;
    if (scanf("%u %u\n", &d, &k) != 2) {
        return -1;
    }
    struct prestazioneGrafo camminiMinimi[k];
    if (d == 0) {
        return -1;
    }
    Matrice = (int **) malloc(d * sizeof(int *));
    for (int i = 0; i < d; i++) {
        Matrice[i] = (int *) malloc(d * sizeof(int));
    }
    for (int i = 0; i < k; i++) {
        camminiMinimi[i].numeroGrafo = -1;
        camminiMinimi[i].costoGrafo = -1;
    }
    char str1[] = "AggiungiGrafo";
    char str2[] = "TopK";
    char *res = malloc(14 * sizeof(char));  //prima per 13
    while (!feof(stdin)) {
        if (scanf("%s\n", res) != 1) {
            return -1;
        } else if (!strcmp(res, str1)) {
            aggiungiGrafo(d);
            aggiornaCamminiMinimi(camminiMinimi, k, dijkstra(d), numGrafo);
        } else if (!strcmp(res, str2)) {
            topk(camminiMinimi, k);
        }
        numGrafo++;
    }
    return 0;
}




