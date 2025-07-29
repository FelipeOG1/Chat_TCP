#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "client.h"
int main(int argc,char *argv[]){
  
  if(argc<2){
    fprintf(stderr,"Se deben de colocar dos argumentos\n");
    exit(1);   
  }
  say_hello("name");

  printf("%d",argc); 

  return 0;
  
}
