/*
Name: Michael Luster
Date: 3/15/2016
Instructor: Zong
Program: 1.1b
Description: Program will implement the fibonacci sequence
using pthreads up to a given number (number will
be accepted as a single positive integer)
The parent thread will output the sequence generated by the child

*/

#include<cstdio>
#include<pthread.h>
#include<cstdlib>
#include<string>
#include <iostream>

#define SIZE 25//global

int fib_arr[SIZE]; //shared by threads
void *fibonacci(void *n); // dymanically aloocate memory
using namespace std;

int main(int argc,char *argv[] ){


//Errpr checking & initalization /////////////////////////////////
  if(argc !=2){   //Error message for non single arguments

  cout << "Error: Fib Sequence only works for single arguments\n";
  return -1;
 }

int num=atoi(argv[1]);  //convert string value to integer

  if(num<0){
  cout << "Error:Fibb Sequence works only for positive numbers.\n";
  return -1;
 }
 else{
  pthread_attr_t attr; //attributes for the threads
  pthread_attr_init(&attr); //get the default attributes
  pthread_t tid; //thread Identifier
  pthread_create(&tid,&attr,fibonacci,&num); //create a thread
  pthread_join(tid,NULL); //waits for thread to exit before initiation

//Fibonacci sequence begins:////////////////////////////////////////////////

  cout <<"Fibonacci sequence\n---------------------\n";

   for(int i=0; i<num; i++)
   cout << "F(" <<i <<"): "<< fib_arr[i] << endl;

 }
 return 0;
}

void *fibonacci(void *n){ //passed as a void function for pthread_create argument

   int x = 0,
      y = 1,
      fibn=0;

int num = *(int *) (n); //must dereference num for integer use

 for(int i=1; i<=num; i++){
  fib_arr[i-1]=fibn;
  fibn = x + y;
  x = y;
  y = fibn;
 }

 return 0;
}
