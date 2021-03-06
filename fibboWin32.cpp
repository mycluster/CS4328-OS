/*
Name: Michael Luster
Date: 3/15/2016
Instructor: Zong
Program: 1.1b
Description: Program will implement the fibonacci sequence
using Win32 multi-threading up to a given number (number will
be accepted as a single positive integer)
The parent thread will output the sequence generated by the child

*/

#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <cstdlib>

using namespace std;

//function is separated across threads w/ DWORD WINAPI
DWORD WINAPI fibo(LPVOID param){

  int x = 0,
      y = 1,
      fibn=0;
int num = *(int*)param;

for(int i = 1; i <= num; i++){
    cout << "F(" << i-1 << "): " << y << endl;
    fibn = x + y;
    x = y;
    y = fibn;
}
    return 0;
}


int main(int argc, char *argv[]){

cout <<"Fibonacci sequence\n---------------------\n";

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

    DWORD ThreadId;
    HANDLE ThreadHandle;
    //creates the threads
    ThreadHandle = CreateThread(NULL, 0, fibo, &num, 0, &ThreadId);
    //waits for thread to finish
    if(ThreadHandle != NULL){
        WaitForSingleObject(ThreadHandle, INFINITE);
        CloseHandle(ThreadHandle);
    }

 }

return 0;
}



