
/* My personal C playground where I can get acquainted with the various capabilities and intricacies of the C programming language.
 * Currently this file consists of my own custom implementation of the linked list construct.
 * Any tips and tricks on improving and optimizing the linked list implementation are very much welcome.
 */

#include <stdio.h>
#include <stdlib.h>

/* Practice struct
 */
typedef struct hello {
  int a;
  int b;
} someStruct;

/* Used in the `main` method to test passing by reference in C.
 */
void passByReference(int *a) {
  *a = 7;
}

/* The main linked list struct.
 */
struct linkedList {
  int value;
  struct linkedList *next;
  struct linkedList *prev;
};

typedef struct linkedList List;

/* Return a new linked list.
 */
List* createList() {
  List* newList = malloc(sizeof(List));
  newList -> next = NULL;
  newList -> prev = NULL;
  return newList;
}
  
/* Insert `Value` at the end of `list`.
 */
void appendValue(List *list, int Value) {
  List* newList = createList();
  while(list -> next) {
    list = list -> next;
  }
  newList -> prev = list;
  list -> next = newList;
  list -> value = Value;
}

/* Return the length of `list`.
 */
int getLength(List *list) {
  int length = 0;
  while(list -> next) {
    length++;
    list = list -> next;
  }
  return length;
}

/* Helper method for the implementation of other list methods
 * Returns the memory address in `list` at `index`.
 * Negative indices wrap around the end of `list` for all subsequent index-based list methods.
 */
List* getIndexAddress(List* list, int index) {
  if(index < 0) {
    while(list -> next) {
      list = list -> next;
    }
  }
  for(int i = 0; i < (index < 0 ? -index : index); i++) {
    List* check = index < 0 ? list -> prev : list -> next;
    if(check) {
      list = check;
    } else {
      printf("Error: List index out of range.\n");
      exit(255);
    }
  }
  return list;
}

/* Return the value in `list` at `index`.
 */
int getValueAt(List *list, int index) {
  return getIndexAddress(list, index) -> value;
}

/* Insert `Value` at the beginning of `list`.
 */
void prependValue(List *list, int Value) {
  int length = getLength(list);
  List* newList = createList();
  while(list -> next) {
    list = list -> next;
  }
  newList -> prev = list;
  list -> next = newList;
  for(int i = 0; i < length; i++) {
    list -> value = list -> prev -> value;
    list = list -> prev;
  }
  list -> value = Value;
}

/* Insert the values of `list2` at the end of `list1`.
 */
void appendValues(List *list1, List *list2) {
  int length2 = getLength(list2);
  while(list1 -> next) {
    list1 = list1 -> next;
  }
  for(int i = 0; i < length2; i++) {
    List* newList = createList();
    list1 -> value = getValueAt(list2, i);
    newList -> prev = list1;
    list1 = list1 -> next = newList;
  }
}

/* Insert the values of `list2` at the beginning of `list1`.
 */
void prependValues(List *list1, List *list2) {

  int length2 = getLength(list2);
  for(int i = 1; i <= length2; i++) {
    prependValue(list1, getValueAt(list2, length2 - i));
  }

  /* Interestingly, the following does NOT work.
   * Although `oList` is assigned the value `*list2` (the value stored at memory address `list2`),
   * `oList` is still modified after `appendValues` executes.
   * Comment the code block in to see for yourself.
   */
  /* 
  List oList = *list2;
  printf("Should print 3: %d\n", getLength(list2));
  appendValues(list2, list1);
  printf("Should still print 3: %d\n", getLength(List2); // Yet "11" is printed instead.
  *list1 = *list2;
  *list2 = oList;
  */
}

/* Change the value in `list` at `index` to `Value`.
 */
void changeValueAt(List *list, int index, int Value) {
  getIndexAddress(list, index) -> value = Value;
}

/* Insert value `Value` at `index` in `list`.
 */
void insertValueAt(List *list, int index, int Value) {
  prependValue(getIndexAddress(list, index), Value);
}

/* Sort `list` in order from least to greatest.
 */
void sort(List *list) {
  List* head = list;
  while(head -> next) {
    while(list -> next) {
      if(list -> value < head -> value && list != head) {
	int listValue = list -> value;
	list -> value = head -> value;
	head -> value = listValue;
      }
      list = list -> next;
    }
    head = head -> next;
    list = head;
  }
} 

/* Through binary searching, Find the index of the first occurance of `Value` in `list`.
 * The `list` must be sorted in order from least to greatest.
 */
int search(List* list, int Value) {
  List* oList = list;
  int length = getLength(list) - 1;
  int index = 0;
  while(length) {
    if(list -> value > Value) {
      index -= length;
    } else {
      index += length;
    }
    list = getIndexAddress(oList, index);
    length /= 2;
  }
  if(list -> value == Value) {
    while(list -> prev && list -> prev -> value == Value) {
      list = list -> prev;
      index--;
    }
    return index;
  } else {
    printf("Error: Value not in list\n");
    exit(255);
  }
}

/* Return a sub-list of `list` beginning at `index1` (inclusive) and ending at `index2` (exclusive).
 * If only `index2` is greater than the length of `list`, the sub-list from `index1` to the end is returned.
 * If both `index1` and `index2` are greater than the length of `list`, or both indices are negative, or `index1` > `index2`, an empty list is returned.
 * If only `index1` is negative, the sub-list from the beginning to `index2` (exclusive) is returned.
 */
List* subList(List* list, int index1, int index2) {
  int length = getLength(list);
  List* subList = createList();
  for(int i = index1 < 0 ? 0 : index1; i < index2 && i < length - 1; i++) {
    appendValue(subList, getValueAt(list, i));
  }
  return subList;
}


int main(int argc, char **argv) {

  /* Struct practice
   */
  someStruct a = {.b = 2, .a = 3};
  struct hello *p = &a;
  int *int_array = malloc(2 * sizeof(int)); // MUST include malloc
  *int_array = 5;
  *(int_array + 1) = 6;
  printf("%d\n", *int_array); // Prints `5`
  printf("%d %d\n", p->a, p->b); // Prints `3 2`

  /* Work with passing by reference.
   */
  int G = 9;
  printf("G: %d\n", G); // Prints `9`
  passByReference(&G); // Pass `G` by reference rather than by value (the latter would instead be `passByReference(G)`)
  printf("G2: %d\n", G); // Prints `7` since `G` was passed by reference rather than by value

  ////////////////////////////
  // Work with Linked Lists //
  ////////////////////////////
  
  List *list = createList();
  printf("list Address: %p\n", list); // Should print "Address: 0x..."
  printf("Length: %d\n", getLength(list)); // Should print "Length: 0"
  appendValue(list, 3);
  printf("Value: %d, Length: %d\n", getValueAt(list, 0), getLength(list)); // Should print "Value: 3, Length: 1"
  appendValue(list, 7);
  printf("Value: %d, Length: %d\n", getValueAt(list, -1), getLength(list)); // Should print "Value: 7, Length: 2"
  prependValue(list, 89);
  printf("Value: %d, Length: %d\n", getValueAt(list, 0), getLength(list)); // Should print "Value: 89, Length: 3"
  prependValue(list, 156);
  appendValue(list, 678);
  printf("Value: %d, Length: %d\n", getValueAt(list, 0), getLength(list)); // Should print "Value: 156, Length: 5"
  printf("Value: %d, Length: %d\n", getValueAt(list, 4), getLength(list)); // Should print "Value: 678, Length: 5"
  
  printf("\nBy this point, list should be {156, 89, 3, 7, 678}\n");
  printf("-----\nlist:\n-----\n");
  for(int k = 0; k < getLength(list); k++) {
    printf("Value: %d\n", getValueAt(list, k));
  }
  
  List *list2 = createList();
  appendValue(list2, 7);
  appendValue(list2, 8);
  prependValue(list2, 89);
  printf("\nValue: %d, Length: %d\n", getValueAt(list2, 0), getLength(list2)); // Should print "Value: 89, Length: 3"
  appendValues(list, list2);
  printf("Value: %d, Length: %d\n", getValueAt(list, 7), getLength(list)); // Should print "Value: 8, Length: 8"
  prependValues(list, list2);
  printf("Value: %d, Length: %d\n", getValueAt(list, 0), getLength(list)); // Should print "Value: 89, Length: 11"
  changeValueAt(list, 0, 545);
  printf("Value: %d, Length: %d\n", getValueAt(list, 0), getLength(list)); // Should print "Value: 545, Length: 11"
  
  printf("\nBy this point, list should be {545, 7, 8, 156, 89, 3, 7, 678, 89, 7, 8}\n");
  printf("-----\nlist:\n-----\n");
  for(int i = 0; i < getLength(list); i++) {
    printf("Value: %d\n", getValueAt(list, i));
  }
  printf("\nBy this point, list2 should be {89, 7, 8}\n");
  printf("------\nlist2:\n------\n");
  for(int j = 0; j < getLength(list2); j++) {
    printf("Value: %d\n", getValueAt(list2, j));
  }
  printf("\n");
  
  insertValueAt(list, 7, 829);
  printf("Value: %d, Length: %d\n", getValueAt(list, 7), getLength(list));
  
  sort(list);
  printf("\n------------\nlist sorted:\n------------\n");
  for(int i = 0; i < getLength(list); i++) {
    printf("Value: %d\n", getValueAt(list, i));
  }
  printf("\n");

  printf("Index of 89 in list: %d\n", search(list, 89));
  
  List* list3 = subList(list, 4, 9);
  printf("\n------\nlist3:\n------\n");
  for(int i = 0; i < getLength(list3); i++) {
    printf("Value: %d\n", getValueAt(list3, i));
  }

  free(list);
  free(list2);
  free(list3);

  /////////
  // END //
  /////////
  
  return 0;
}
