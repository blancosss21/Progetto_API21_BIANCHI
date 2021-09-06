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
/*char* strtok1(char *str, const char* delim) {
    static char* buffer;
    if(str != NULL)
        buffer = str;
    if(buffer[0] == '\0') return NULL;
    char *ret = buffer, *b;
    const char *d;
    for(b = buffer; *b !='\0'; b++) {
        for (d = delim; *d != '\0'; d++) {
            if (*b == *d) {
                *b = '\0';
                //buffer = b + 1;
                // skip the beginning delimiters
                if (b == ret) {
                    ret++;
                    continue;
                }
                return ret;
            }
        }
    }
    return ret;
}*/
char* strtok1(char *str, const char* delim) {
    static char* buffer;
    if(str != NULL) buffer = str;
    if(buffer[0] == '\0') return NULL;

    char *ret = buffer, *b;
    const char *d;

    for(b = buffer; *b !='\0'; b++) {
        for(d = delim; *d != '\0'; d++) {
            if(*b == *d) {
                *b = '\0';
                buffer = b+1;

// skip the beginning delimiters
                if(b == ret) {
                    ret++;
                    continue;
                }
                return ret;
            }
        }
    }
    buffer = b;
    return ret;
}




void aggiungiGrafo(int d) {
    char riga[MAX];
    char *tok;
    for (int c = 0; c < d; c++) {
        if (fgets(riga, MAX, stdin) == NULL) {
            exit(1);
        }
        tok = strtok1(riga, ",");
        Matrice[c][0] = myAtoi(tok);
        for (int e = 1; e < d; e++) {
            tok = strtok1(NULL, ",");
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

void topk(struct prestazioneGrafo *camminiMinimi, int numGrafi, int k) {
    if (numGrafi == 0){
        printf("\n");
        return;
    }
    int ripeti;
    if (numGrafi < k)
        ripeti = numGrafi;
    else
        ripeti = k;
    for (int i = 0; i < ripeti - 1; ++i) {
        //puts(camminiMinimi[i].numeroGrafo);
        //write(0,camminiMinimi[i].numeroGrafo,strlen(camminiMinimi[i].numeroGrafo));
        printf("%d ", camminiMinimi[i].numeroGrafo);
    }
    printf("%d\n", camminiMinimi[ripeti - 1].numeroGrafo);
}


int main() {
    int d;
    int k;
    int numGrafi = 0;
    char res [MAX];
    //int c;
    //scanf("%u %u\n", &d, &k)     (fgets(riga, MAX, stdin)
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
    //char str1[] = "AggiungiGrafo";
    //char str2[] = "TopK";
    //char *res = malloc(14 * sizeof(char));  //prima per 13
    while (fgets(res, MAX, stdin) !=NULL) {
        /*if (scanf("%s\n", res) != 1) {  //(fgets(riga, MAX, stdin)
            return -1;
        }*/
        if (res[0] == 'A') {
            aggiungiGrafo(d);
            aggiornaCamminiMinimi(camminiMinimi, k, dijkstra(d), numGrafi);
            numGrafi++;
        } else if (res[0] == 'T') {
            topk(camminiMinimi, numGrafi, k);
        }

    }
    return 0;
}




