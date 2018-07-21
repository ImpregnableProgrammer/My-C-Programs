/* 
   My implementation of a dynamically-resizeable Hash Table with a custom Hash function in the C programming language.
   Reference(s): https://en.wikipedia.org/wiki/Hash_table
                 https://algs4.cs.princeton.edu/34hash/
 */ 

#include <stdlib.h>
#include <stdio.h>

// Buckets for Hash Table
struct chain {
  char* key;
  long value;
  int size;
  struct chain *next;
} master = {NULL, 0, 0, NULL};

typedef struct chain *Chain;

const int SIZE = sizeof(struct chain);
long MAX_SIZE = 1;
double TOTAL_ENTRIES = 0;
const double LOAD_FACTOR = 2.0 / 3.0;

Chain *array;

// Generate a hash for the given key
unsigned long getHash(char *key) {
  unsigned long Hash = 0;
  while(*key != '\0') {
    Hash = 101 * Hash + *key;
    key++;
  }
  return Hash;
}

// Return whether or not the two given strings are equal
int StringEqual(char *s1, char *s2) {
  int equal = 0;
  while(*s1 == *s2 && *s1 != '\0' && *s2 != '\0') {
    s1++;
    s2++;
  }
  if(*s1 == '\0' && *s2 == '\0')
    return 1;
  else
    return 0;
}

// Add a new key-value pair entry into the hash table
void addEntry(char* key, long value) {
  if(TOTAL_ENTRIES / MAX_SIZE > LOAD_FACTOR) {
    Chain *newArray = malloc(MAX_SIZE * 2 * SIZE);
    for(int i=0;i<MAX_SIZE*2;i++)
      newArray[i] = NULL;
    for(int j=0;j<MAX_SIZE;j++) {
      if(array[j] != NULL)
	newArray[getHash(array[j]->key) % (MAX_SIZE * 2)] = array[j];
    }
    array = newArray;
    MAX_SIZE *= 2;
  }
  unsigned long hash = getHash(key) % MAX_SIZE;
  if(array[hash] != NULL) {
    Chain bucket = array[hash];
    int newSize = bucket->size + 1;
    while(bucket->next != NULL) {
      if(StringEqual(bucket->key, key))
	break;
      bucket->size++;
      bucket = bucket->next;
    }
    bucket->key = key;
    bucket->value = value;
    bucket->size = newSize;
    bucket->next = malloc(SIZE);
    *bucket->next = master;
  } else {
    array[hash] = malloc(SIZE);
    Chain bucket = array[hash];
    bucket->key = key;
    bucket->value = value;
    bucket->size = 1;
    bucket->next = malloc(SIZE);
    *bucket->next = master;
  }
  TOTAL_ENTRIES++;
}

// Retrieve the value associated with the given key
int getEntry(char* key) {
  unsigned long hash = getHash(key) % MAX_SIZE;
  Chain bucket = NULL;
  if(array[hash] != NULL)
    bucket = array[hash];
  while(bucket != NULL && bucket->next != NULL && StringEqual(bucket->key, key) == 0)
    bucket = bucket->next;
  if(bucket != NULL && bucket->key != NULL)
    return bucket->value;
  else {
    printf("Error: Value not in Hash Table\n");
    exit(255);
  }
}

// Convert a given non-negative integer into a string
// Used for hash table testing
char* intToString(long Num) {
  long tNum = Num;
  int numDigits = 1;
  while(tNum > 9) {
    tNum /= 10;
    numDigits += 1;
  }
  char *numString = malloc(numDigits * sizeof(char));
  for(int i=numDigits-1;i>=0;i--) {
    numString[i] = 48 + Num % 10;
    Num /= 10;
  }
  return numString;
}
  
int main() {
  // Initialize the Hash Table `array`
  array = malloc(MAX_SIZE * SIZE);
  for(int i=0;i<MAX_SIZE;i++)
    array[i] = NULL;

  // Hash Table Testing
  for(long i=0;i<10000000;i++)
    addEntry(intToString(i), i);
  printf("key 943176 = %d\n", getEntry("943176"));
  
  free(array);
  return 0;
}
