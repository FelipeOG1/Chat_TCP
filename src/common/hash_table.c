#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include "hash_table.h"


unsigned int get_index(int key,size_t size){
  return (unsigned int) key % size;
}

HashTable * create_hash_table(size_t size){
  HashTable *hash_table = malloc(sizeof(HashTable));
  hash_table->buckets = calloc(size,sizeof(HashNode *));
  hash_table->count = 0;
  hash_table->size = size; 

}

void insert(HashTable * hash_table,int key,const char * value){
  printf("No implementation");
}
