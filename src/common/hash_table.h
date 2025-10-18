#include <stddef.h>
#pragma once
typedef struct HashNode{
  int key;
  char * value;
  struct HashNode* next;
}HashNode;

typedef struct HashTable{
  HashNode ** buckets;
  size_t size;
  size_t count;
}HashTable;


HashTable * create_hash_table(size_t size);
void insert(HashTable * hash_table,int key,const char * value);
unsigned int get_index(int key,size_t size);
void find(HashTable * hash_table,int key);
void free_table(HashTable * hash_table);


