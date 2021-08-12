#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX 30000
//#define INT_MAX 100000000
int peso= INT_MAX;


void AggiungiGrafo(unsigned int d);
//void TopK();
//inizio
int ArraySize, HeapSize, tot;
int left(int i) { return 2*i+1;}
int right(int i) { return 2*i+2;}
int parent(int i) {return (i-1)/2;}
void swap(int A[MAX], int i, int j){
    int tmp = A[i];
    A[i] = A[j];
    A[j] =tmp;}
void MaxHeapify(int A[MAX], int i);
void BuildHeap(int A[MAX]);
void HeapSort(int A[MAX]);
void MinHeapInsert(int A[MAX], int Key);
void HeapDecreaseKey(int A[MAX], int i, int Key);
void HeapExtractMin(int A[MAX]);

//fine


unsigned int myAtoi(char* str);
unsigned int **Matrice;

int main(void) {
    unsigned int d;
    unsigned int k;
    int i;


    if (!scanf("%u %u\n", &d, &k)){};
    printf("%u %u\n", d, k);
    Matrice = malloc(d*sizeof *Matrice);
    for(i=0;i<d;i++){
        Matrice[i] = malloc(d*sizeof **Matrice);
    }
    char str1[]= "AggiungiGrafo";
    char str2[]= "TopK";

    //char *res="";
    //char riga[MAX];

    //res = fgets(riga, MAX, stdin);

    char *res= malloc(13*sizeof *res);

    while(1){

        if(!scanf("%s\n",res)) {

        }
        if(feof(stdin))
            break;
        if (!strcmp(res, str1))
            AggiungiGrafo(d);
        else if (!strcmp(res, str2))
            printf("ciao");
            //Topk();

        else break;
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
        for (unsigned int s = 1; s < d; s++) {
            tok= strtok(NULL, ",");
            Matrice[c][s] = myAtoi(tok);
        }
    }
    free(res);

    //dijistra

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
     printf("ciao");
}*/

void BuildHeap(int A[MAX])
{
    int i;
    HeapSize = ArraySize;
    for (i=ArraySize/2; i>=0; i--)
        MaxHeapify(A, i);
}

void MaxHeapify(int A[MAX], int i)
{
    int l,r,largest;
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
void HeapSort(int A[MAX]){
    int i;
    BuildHeap(A);
    for (i=ArraySize-1; i>=1; i--) {
        swap(A, 0, i);
        HeapSize--;
        MaxHeapify(A, 0);
    }
}



void MinHeapify(int A[MAX], int i){
    int l,r,smallest;
    l = left(i);
    r = right(i);
    if (l < HeapSize && A[l] < A[i])
        smallest = l;
    else smallest = i;
    if (r < HeapSize && A[r] < A[smallest])
        smallest = r;
    if (smallest != i) {
        swap(A, i, smallest);
        MinHeapify(A, smallest);
    }
}



void HeapExtractMin(int A[MAX]){
    int i,min;
    HeapSize = ArraySize;
    if(HeapSize < 1)
        return NULL;
    min = A[1];
    A[1]= A[HeapSize];
    MinHeapify(int A[MAX], int i);
    return min;
}

void HeapDecreaseKey(int A[MAX], int i, int Key) {
    int p = parent(i);
    if (Key > A[i])
        return NULL;
    A[i] = Key;
    while (i > 1 && A[p] > A[i]) {
        swap(A, i, p);
        i = p;
    }
}

void MinHeapInsert(int A[MAX], int Key){
    HeapSize=ArraySize;
    HeapSize++;
    A[HeapSize]= INT_MAX;
    HeapDecreaseKey(int A[MAX], int HeapSize, int Key);

}

void dijkstra(int G[MAX][MAX],int w,int s){
    int Q=0;
    int sDist = 0:
    int sPrev = NULL;
    MinHeapInsert(Q, s);














}





























