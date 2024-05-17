//API PROJECT

#include <stdlib.h>
#include <stdio.h>
//#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define MAX 30000

int **Matrice;
int trovato=0;
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

char *myStrTok(char *str, const char *delim) {
    static char *buffer;
    if (str != NULL)
        buffer = str;
    if (buffer[0] == '\0') return NULL;

    char *ret = buffer, *b;
    const char *d;

    for (b = buffer; *b != '\0'; b++) {
        for (d = delim; *d != '\0'; d++) {
            if (*b == *d) {
                *b = '\0';
                buffer = b + 1;
                if (b == ret) {
                    ret++;
                    continue;
                }
                return ret;
            }
        }
    }
    //buffer = b;
    return ret;
}


void aggiungiGrafo(int d) {
    char riga[MAX];
    char *tok;
    for (int c = 0; c < d; c++) {
        if (fgets(riga, MAX, stdin) == NULL) {
            exit(1);
        }
        tok = myStrTok(riga, ",");
        Matrice[c][0] = myAtoi(tok);
        for (int e = 1; e < d; e++) {
            tok = myStrTok(NULL, ",");
            Matrice[c][e] = myAtoi(tok);
        }
    }
}

int parent(int i) {
    return (i - 1) / 2;
}

void swap(struct prestazioneGrafo *x, struct prestazioneGrafo *y) {
    struct prestazioneGrafo temp;
    temp.costoGrafo = (*x).costoGrafo;
    temp.numeroGrafo = (*x).numeroGrafo;
    (*x).costoGrafo = (*y).costoGrafo;
    (*x).numeroGrafo = (*y).numeroGrafo;
    (*y).costoGrafo = temp.costoGrafo;
    (*y).numeroGrafo = temp.numeroGrafo;
}

void heapify(struct prestazioneGrafo *camminiMinimi, int i, int size) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < size && camminiMinimi[l].costoGrafo > camminiMinimi[largest].costoGrafo)
        largest = l;
    if (r < size && camminiMinimi[r].costoGrafo > camminiMinimi[largest].costoGrafo)
        largest = r;
    if (largest != i) {
        swap(&camminiMinimi[i], &camminiMinimi[largest]);
        heapify(camminiMinimi, largest, size);
    }
}

void aggiornaCamminiMinimi(struct prestazioneGrafo *camminiMinimi, int dimensioneCamminiMinimi, int costoGrafo,
                           int numeroGrafo, int *size) {
    if (*size >= dimensioneCamminiMinimi) {
        if (camminiMinimi[0].costoGrafo > costoGrafo) {
            camminiMinimi[0].numeroGrafo = numeroGrafo;
            camminiMinimi[0].costoGrafo = costoGrafo;
            int i = *size - 1;
            while (camminiMinimi[parent(i)].costoGrafo < camminiMinimi[i].costoGrafo) {
                swap(&camminiMinimi[parent(i)], &camminiMinimi[i]);
                i = parent(i);
            }
        }
        if(*size == dimensioneCamminiMinimi && trovato ==0){
            trovato=1;
            for (int i = *size / 2 - 1; i >= 0; i--) {
                heapify(camminiMinimi, i, *size);
            }
        }
        else  heapify(camminiMinimi, 0, *size);
    } else {
        camminiMinimi[*size].costoGrafo = costoGrafo;
        camminiMinimi[*size].numeroGrafo = numeroGrafo;
        *size = *size + 1;
        int i = *size - 1;
        while (camminiMinimi[parent(i)].costoGrafo < camminiMinimi[i].costoGrafo) {
            swap(&camminiMinimi[parent(i)], &camminiMinimi[i]);
            i = parent(i);
        }
    }
    heapify(camminiMinimi, 0, *size);
}

void topk(struct prestazioneGrafo *camminiMinimi, int numGrafi, int k) {
    if (numGrafi == 0) {
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
    int size = 0;
    char res[MAX];
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
    while (fgets(res, MAX, stdin) != NULL) {
        /*if (scanf("%s\n", res) != 1) {  //(fgets(riga, MAX, stdin)
            return -1;
        }*/
        if (res[0] == 'A') {
            aggiungiGrafo(d);
            aggiornaCamminiMinimi(camminiMinimi, k, dijkstra(d), numGrafi, &size);
            numGrafi++;
        } else if (res[0] == 'T') {
            topk(camminiMinimi, numGrafi, k);
        }

    }
    return 0;
}




