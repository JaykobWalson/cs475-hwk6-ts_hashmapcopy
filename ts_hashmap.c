#include <limits.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ts_hashmap.h"

/**
 * Creates a new thread-safe hashmap. 
 *
 * @param capacity initial capacity of the hashmap.
 * @return a pointer to a new thread-safe hashmap.
 */
ts_hashmap_t *initmap(int capacity) {
  ts_hashmap_t *params = (ts_hashmap_t*) malloc (capacity *sizeof(ts_hashmap_t*));
  params->capacity = capacity;
  params->size = 0;
  params->table = (ts_entry_t**) malloc (capacity *sizeof(ts_entry_t*));
  for(int i = 0; i < capacity; i++){
     params->table[i] = NULL;//putting everything to NULL by default. 
  }
  return params;
}

/**
 * Obtains the value associated with the given key.
 * @param map a pointer to the map
 * @param key a key to search
 * @return the value associated with the given key, or INT_MAX if key not found
 */
int get(ts_hashmap_t *map, int key) {
  int index = (unsigned int) key % map->capacity;
  ts_entry_t *entry = map->table[index];
  for(int i = 0; i < map->capacity; i++){
    if(entry->key == key){
    return entry->value;//Looks for all of them and changing the values before changing the node.;
    }
    else{
      entry = entry->next;//One after.
    }
  }
  if(entry != NULL && entry->key == key){
    return entry->value;//Change the values.
  }
  

  return INT_MAX;

}

/**
 * Associates a value associated with a given key.
 * @param map a pointer to the map
 * @param key a key
 * @param value a value
 * @return old associated value, or INT_MAX if the key was new
 */
int put(ts_hashmap_t *map, int key, int value) {
  int index = (unsigned int) key % map->capacity;
  ts_entry_t *entry = map->table[index];
  // for(int i = 0; i < map->capacity; i++){
    while(entry != NULL && entry->key != key){
      entry = entry->next;
    }
  // }
  if(entry == NULL){
    entry = (ts_entry_t*) malloc (sizeof(ts_entry_t));
    entry->key = key;
    entry->value = value;//no old value;
    entry->next = map->table[index];
    map->table[index] = entry;
    map->size = map->size + 1;//up the size. This is expanding.
    return INT_MAX;
  }
  else{
    int oldValue = entry->value;//to return if the key wasn't new (as in saying "Oh, that key is already at this value").
    entry->value = value;//old value
    return oldValue;
  }
}

/**
 * Removes an entry in the map
 * @param map a pointer to the map
 * @param key a key to search
 * @return the value associated with the given key, or INT_MAX if key not found
 */
int del(ts_hashmap_t *map, int key) {
  int index = (unsigned int) key % map->capacity;
  ts_entry_t *entry = map->table[index];

  for(int i = 0; i < map->capacity; i++){
    if(entry != NULL && entry->key != key){
      entry = NULL;//deletes the entry.
    }
  }
  if(entry == NULL){
    return INT_MAX;//if the key isn't found.
  }
  else{
    int oldValue = entry->value;//to return if the key wasn't new (as in saying "Oh, that key is already at this value").
    map->table[index] = NULL;
    return oldValue;
  }
}
  


/**
 * @return the load factor of the given map
 */
double lf(ts_hashmap_t *map) {
  return (double) map->size / map->capacity;
}

/**
 * Prints the contents of the map
 */
void printmap(ts_hashmap_t *map) {
  for (int i = 0; i < map->capacity; i++) {
    printf("[%d] -> ", i);
    ts_entry_t *entry = map->table[i];
    while (entry != NULL) {
      printf("(%d,%d)", entry->key, entry->value);
      if (entry->next != NULL)
        printf(" -> ");
      entry = entry->next;
    }
    printf("\n");
  }
}