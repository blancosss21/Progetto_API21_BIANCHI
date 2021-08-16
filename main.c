#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>



#define MAX 3000000
//#define INT_MAX 100000000
//int peso= INT_MAX;

//typedef enum {NONVISITATO =0, VISITATO= 1} BOOL;
typedef struct {
    unsigned int w;  //nodo
    unsigned int dist; //distanza da quel nodo
    //devo aggiornare la distanza minima totale dal  nodo sorgente corrente
    //indice del nodo 
    //BOOL;
}ElMinHeap;


typedef struct{
    unsigned int ArraySize, HeapSize;  //lunghezza dell'Array e dello Heap
    unsigned int *Pos; //serve per sapere dove stanno i nodi nella priorityqueue, siccome essendo un min heap,non sono in ordine di indice ma di distanza migliore
    ElMinHeap *array;
}MinHeap;



void AggiungiGrafo(unsigned int d);
void dijkstra(unsigned int d); //dovrei metterci anche nodo[d][d]?
//void TopK();
unsigned int somma (unsigned int v[],unsigned int n);


unsigned int left(unsigned int i) { return 2*i+1;}
unsigned int right(unsigned int i) { return 2*i+2;}
unsigned int parent(unsigned int i) {return (i-1)/2;}
void swap(unsigned int A[MAX], unsigned int i,unsigned  int j){
    unsigned int tmp = A[i];
    A[i] = A[j];
    A[j] =tmp;}

//void MaxHeapify(unsigned int A[MAX], unsigned int i);
//void BuildHeap(unsigned int A[MAX]);
//void HeapSort(unsigned int A[MAX]);
//void MinHeapInsert(unsigned int A[MAX], unsigned int Key);
void HeapDecreaseKey(unsigned int A[MAX], unsigned int i,unsigned  int Key);
unsigned int HeapExtractMin(unsigned int A[MAX]);



unsigned int myAtoi(char* str);
unsigned int **Matrice;
MinHeap *PriorityQueue;



int main(void) {
    unsigned int d;
    unsigned int k;
    int i;


    if (scanf("%u %u\n", &d, &k)){};
    printf("%u %u\n", d, k);
    Matrice = malloc(d*sizeof *Matrice);
    for(i=0;i<d;i++){
        Matrice[i] = malloc(d*sizeof **Matrice);
    }
    PriorityQueue= malloc(sizeof *PriorityQueue);
    PriorityQueue->Pos=malloc(d*sizeof PriorityQueue->Pos);
    PriorityQueue->array=malloc(d*sizeof PriorityQueue->array);
    PriorityQueue->ArraySize=d;
    PriorityQueue->HeapSize=0;

    char str1[]= "AggiungiGrafo";
    char str2[]= "TopK";

    //char *res="";
    //char riga[MAX];

    //res = fgets(riga, MAX, stdin);

    char *res= malloc(13*sizeof *res);

    while(1){

        if(!scanf("%s\n",res)) {};
        if(feof(stdin))
            break;
        if (!strcmp(res, str1))
            AggiungiGrafo(d);
        else if (!strcmp(res, str2))
            //Topk();
            printf("ciao");
        else
            break;
    }




    return 0;

}

void AggiungiGrafo(unsigned int d) {

    char *res;
    char riga[MAX];
    char *tok;
    res = (char *) malloc(sizeof(char));

    /* legge e stampa ogni riga */
    for (unsigned int c = 0; c<d; c++) {
        res = fgets(riga, MAX, stdin);
        printf("%s", riga);
        tok=strtok(res, ",");
        Matrice[c][0] = myAtoi(tok);
        for (unsigned int e = 1; e < d; e++) {
            tok= strtok(NULL, ",");
            Matrice[c][e] = myAtoi(tok);
        }
    }
    free(res);

    dijkstra(d); //dovrei metterci anche nodo[d][d]?

}


// A simple atoi() function

unsigned int myAtoi(char *str) {
    // Initialize result
    unsigned int res = 0;
    // Iterate through all characters
    // of input string and update result
    // take ASCII character of corresponding digit and
    // subtract the code from '0' to get numerical
    // value and multiply res by 10 to shuffle
    // digits left to update running total
    for (unsigned int i = 0; str[i] != '\0'&& str[i] != '\n'; ++i)
        res = res * 10 + str[i] - '0';
    // return result.
    return res;
}


/*void TopK(){
 * devo avere una classifica
    if(Due grafi hanno lo stesso peso){
         stampo classifica fino a k e se due hanno stesso peso quello che arriva prima e poi l'altro
    }
    else if (due grafi hanno peso diverso)
             stampo classifica fino a k

    else printf("\n");

}*/




/*void BuildHeap(unsigned int A[MAX]){
    unsigned int i;
    HeapSize = ArraySize;
    for (i=ArraySize/2; i>=0; i--)
        MaxHeapify(A, i);
}*/

/*void MaxHeapify(unsigned int A[MAX],unsigned  int i)
{
    unsigned int l,r,largest;
    l = left(i);
    r = right(i);
    if (l < HeapSize && A[l] > A[i])
        largest = l;
    else largest = i;
    if (r < HeapSize && A[r] > A[largest])
        largest = r;
    if (largest != i) {
        swap(A, i, largest);
        MaxHeapify(A, largest);
    }
}
void HeapSort(unsigned int A[MAX]){
    int i;
    BuildHeap(A);
    for (i=ArraySize-1; i>=1; i--) {
        swap(A, 0, i);
        HeapSize--;
        MaxHeapify(A, 0);
    }
}*/






void MinHeapify(unsigned int A[MAX], unsigned int i){
    unsigned int l,r,smallest;
    l = left(i);
    r = right(i);
    if (l < PriorityQueue->HeapSize && A[l] < A[i])
        smallest = l;
    else smallest = i;
    if (r < PriorityQueue->HeapSize && A[r] < A[smallest])
        smallest = r;
    if (smallest != i) {
        swap(A, i, smallest);
        MinHeapify(A, smallest);
    }
}



unsigned int HeapExtractMin(unsigned int A[MAX]){
    unsigned int min;
    PriorityQueue->HeapSize = PriorityQueue->ArraySize;
    if(PriorityQueue->HeapSize < 1)
        return 1;
    min = A[1];
    A[1]= A[PriorityQueue->HeapSize];
    MinHeapify(A, 1);
    return min;
}

void HeapDecreaseKey(unsigned int A[MAX],unsigned  int i, unsigned int Key) {
    unsigned int p = parent(i);
    if (Key > A[i])
        return;
    A[i] = Key;
    while (i > 1 && A[p] > A[i]) {
        swap(A, i, p);
        i = p;
    }
}

/*void MinHeapInsert(unsigned int A[MAX],unsigned  int Key){
    PriorityQueue->HeapSize=PriorityQueue->ArraySize;
    PriorityQueue->HeapSize++;
    A[PriorityQueue->HeapSize]= INT_MAX;
    HeapDecreaseKey(A, PriorityQueue->HeapSize, Key);

}*/

void dijkstra(unsigned int d){   //dovrei metterci anche nodo[d][d]?
    unsigned int u;

    (PriorityQueue->array[0]).w=0;
    (PriorityQueue->array[0]).dist=0;
    PriorityQueue->HeapSize++;


    for(u=1; u !=0; u++){
        (PriorityQueue->array[u]).w=u;
        (PriorityQueue->array[u]).dist=UINT_MAX;
        PriorityQueue->HeapSize++;
    }


    while ((&(PriorityQueue->array[u]).w)!=0){
        u= HeapExtractMin((&(PriorityQueue->array[u]).w));
        for(unsigned int v=1; v!=(PriorityQueue->HeapSize++);v++){    //prima avevo v!=u
            if((PriorityQueue->array[u]).dist> (PriorityQueue->array[u]).dist+ Matrice[u][v]){   //PriorityQueue->array[u]).w non è corretto!!!
                (PriorityQueue->array[v]).dist = (PriorityQueue->array[u]).dist + Matrice[u][v]; //poichè la funzione w(u,v) è la distanza fra u e v (che ho nella matrice)
                //unsigned int vPrev = u; mi interessa solo la lunghezza non mi interessa salvare i valori
                HeapDecreaseKey((&(PriorityQueue->array[u]).w), v, Matrice[u][v]);
            }
        }
    }
    //dovrei fare somma dei cammini minimi
    somma(&(PriorityQueue->array[u]).w, PriorityQueue->HeapSize++);
}



unsigned int somma (unsigned int v[], unsigned int n) {
    unsigned int i;
    unsigned int s=0;
    for (i=0;i<n;i++) {
        s=s+v[i];
    }
    return s;
}






