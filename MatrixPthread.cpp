/*
Name: Michael Luster
Date: 3/15/2016
Instructor: Zong
Program: 1.2a
Description: Program will implement the fibonacci sequence
using Win32 multi-threading up to a given number (number will
be accepted as a single positive integer)
The parent thread will output the sequence generated by the child

*/

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <pthread.h>

//contained declarations are predefined in directions
/////////////////////////
#define M 3
#define K 2
#define N 3

int A [M][K] = { {1,4}, {2,5}, {3,6} };
int B [K][N] = { {8,7,6}, {5,4,3} };
int C [M][N];

void *multMatrix(void *); //void prototype
void printC(int[M][N]);
pthread_mutex_t lock;

struct v{
int i;
int j;
};
////////////////////////////

using namespace std;
int main()
{
    int numthreads = -1;
    int NUM_WORKERS = M*N;

    cout <<"\nPrinting Matrix A: \n";
    for(int i=0;i<M;i++)
    {
        for(int j=0;j<K;j++)
        {
            cout <<A[i][j] <<"\t";
        }
        cout <<"\n";
    }

    cout <<"\nPrinting Matrix B: \n";
    for(int i=0;i<K;i++)
    {
        for(int j=0;j<N;j++)
        {
            cout <<B[i][j] <<"\t";
        }
        cout <<endl;
    }

    cout <<"\nNow initializing workers...\n";
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_mutex_init(&lock, NULL);
    pthread_t workers[NUM_WORKERS];

    //declarations and implementation
    cout <<"creating threads & multiplying matrices...\n";
    //creating multiple(M x N) workers
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++ ) {
            struct v *data = (struct v *) malloc (sizeof (struct v)) ;
            data->i = i;
            data->j = j;
            numthreads++;
            pthread_create(&workers[numthreads],&attr,multMatrix,(void *)data);
        }
      //joining NUM_THREADS amount of workers
    for(int i=0; i<NUM_WORKERS; i++)
        pthread_join(workers[i],NULL);

        printC(C);
        return 0;
}
//C[i,j] = A[i,n] * B[n,j]
void *multMatrix(void *data)
{
struct v *deref;
deref = (struct v*)data;
int inner = deref->i;
int outer = deref->j;

int i,
 index = 0;

for(i=0;i<K;i++)
    index += A[inner][i] * B[i][outer];

    C[inner][outer]=index;


    return 0;
}

void printC(int matrixC[M][N]){

    cout <<"\nPrinting Matrix C: \n";

    for(int i=0;i<M;i++)
    {
        for(int j=0;j<N;j++)
        {
            cout <<matrixC[i][j] <<"\t";
        }
        cout <<"\n";
    }
}
