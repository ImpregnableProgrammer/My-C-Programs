/*
  INTERVIEW QUESTION POSED TO ME BY DAVID, A DEVELOPER AT HCL.

  Premise: A phone company wants to begin a promotion geared towards chess enthusiasts wheerein they will begin issuing "knight's move" phone numbers.

  Given a standard 10-key telephone keypad, a "knight's move" is a L-shaped jump on the keypad.

  For example, the possible knight's moves from the 1 key on the keypad are 6 and 8, but not the others.

  A "knight's move" phone number is a sequence of digits where every digit in the sequence is a valid "knight's move" from its previous digit.

  For example, 161 is a valid "knight's move" phone number of length 3.

  Design an algorithm that returns the total number of unique "knight's move" phone numbers that can be generated for a phone number of length L.

  Test Cases:
  Given 1, output 10;
  Given 2, output 20.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

//////////////////////////////////////////////
// A highly inefficient recursive solution. //
//////////////////////////////////////////////

int KnightsMove(int L, int start) {
  if(L > 1) {
    switch(start) {
    case 1:
      return KnightsMove(L-1, 6) + KnightsMove(L-1, 8);
    case 2:
      return KnightsMove(L-1, 7) + KnightsMove(L-1, 9);
    case 3:
      return KnightsMove(L-1, 4) + KnightsMove(L-1, 8);
    case 4:
      return KnightsMove(L-1, 3) + KnightsMove(L-1, 9) + KnightsMove(L-1, 0);
    case 5:
      // Do nothing. A "knight's move" will never lead to or from 5.
      return 0;
    case 6:
      return KnightsMove(L-1, 1) + KnightsMove(L-1, 7) + KnightsMove(L-1, 0);
    case 7:
      return KnightsMove(L-1, 2) + KnightsMove(L-1, 6);
    case 8:
      return KnightsMove(L-1, 1) + KnightsMove(L-1, 3);
    case 9:
      return KnightsMove(L-1, 2) + KnightsMove(L-1, 4);
    case 0:
      return KnightsMove(L-1, 4) + KnightsMove(L-1, 6);
    }
  }
  return 1;
}

long RecursiveCount(int L) {
  long count = 0;
  for(int i = 0;i < 10;++i) {
    count += KnightsMove(L, i);
  }
  return count;
}

////////////////////////////////////////////////////////////////////////
// A highly inefficient solution using a breadth first search tactic. //
////////////////////////////////////////////////////////////////////////

void AddToArray(int* toarrlength, int** toarr, int fromarrlength, int* fromarr) {
  int* newtoarr = malloc((*toarrlength + fromarrlength) * sizeof(int));
  for(int i = 0;i < *toarrlength;++i)
   *(newtoarr + i) = *(*toarr + i);
  for(int i = *toarrlength;i < *toarrlength + fromarrlength;++i)
   *(newtoarr + i) = *(fromarr + i - *toarrlength);
  *toarrlength += fromarrlength;
  *toarr = newtoarr;
}

int BreadthFirstCount(int L) {
  int length = 10;
  int *digits = malloc(length * sizeof(int));
  for(int i = 0;i < 10;++i)
    *(digits + i) = i;
  
  int One[2] = {6, 8};
  int Two[2] = {7, 9};
  int Three[2] = {4, 8};
  int Four[3] = {3, 9, 0};
  int Six[3] = {1, 7, 0};
  int Seven[2] = {2, 6};
  int Eight[2] = {1, 3};
  int Nine[2] = {2, 4};
  int Zero[2] = {4, 6};
  
  while(L > 1) {
    int *NewDigits = malloc(0);
    int NewLength = 0;
    for(int i = 0;i < length;++i) {
      switch(*(digits + i)) {
      case 1:
	AddToArray(&NewLength, &NewDigits, 2, One);
	break;
      case 2:
	AddToArray(&NewLength, &NewDigits, 2, Two);
	break;
      case 3:
	AddToArray(&NewLength, &NewDigits, 2, Three);
	break;
      case 4:
	AddToArray(&NewLength, &NewDigits, 3, Four);
	break;
      case 5:
	// Do nothing. A "knight's move" will never lead to or from 5.
	break;
      case 6:
	AddToArray(&NewLength, &NewDigits, 3, Six);
	break;
      case 7:
	AddToArray(&NewLength, &NewDigits, 2, Seven);
	break;
      case 8:
	AddToArray(&NewLength, &NewDigits, 2, Eight);
	break;
      case 9:
	AddToArray(&NewLength, &NewDigits, 2, Nine);
	break;
      case 0:
	AddToArray(&NewLength, &NewDigits, 2, Zero);
      }
    }
    digits = NewDigits;
    length = NewLength;
    L -= 1;
  }
  free(digits);
  return length;
}

//////////////////////////////////////////////////////////////////////////////////////////
// An optimal iterative solution.                                                       //
// However, this is subject to overflow of the unsigned long long integer type, which   //
// seems to occur at around an input of 52, during the calculation of the `Sum`.        //
//////////////////////////////////////////////////////////////////////////////////////////

typedef unsigned long long LONG;

LONG CountFinal(int L) {
  LONG *arr = malloc(10 * sizeof(LONG));
  for(int i = 0;i < 10;arr[i++] = 1);
  while(L > 1) {
    LONG *arr2 = malloc(10 * sizeof(LONG));
    arr2[0] = arr[4] + arr[6];
    arr2[1] = arr[6] + arr[8];
    arr2[2] = arr[7] + arr[9];
    arr2[3] = arr[4] + arr[8];
    arr2[4] = arr[0] + arr[3] + arr[9];
    arr2[5] = 0; // A "knights's move" will never lead to or from 5.
    arr2[6] = arr[0] + arr[1] + arr[7];
    arr2[7] = arr[2] + arr[4];
    arr2[8] = arr[1] + arr[3];
    arr2[9] = arr[2] + arr[4];
    free(arr);
    arr = arr2;
    L--;
  }
  LONG Sum = 0;
  for(int i = 0;i < 10;Sum += arr[i++]);
  return Sum;
}

//////////////////////////////////////////////////////////////////
// An efficient string-based iterative solution.                //
// This was created in an attempt to overcome integer overflow. //
// However, because of errors in memory allocation, this may    //
// still produce erroneous results, though very rarely so.      //
//////////////////////////////////////////////////////////////////

// Return the length of the given string `str`.
int StringLength(char* str) {
  int length = 0;
  for(int i = 0;str[i++] != '\0';length++);
  return length;
}

// Return as a string the sum of the integers represented by the two strings `a` and `b`.
char* Addition(char* a, char* b) {
  int aLength = StringLength(a);
  int bLength = StringLength(b);
  int Larger = bLength > aLength ? bLength : aLength;
  char* Sum = malloc((Larger + 1) * sizeof(char));
  int Carry = 0;
  for(int i = 1;i <= Larger;++i) {
    int sum = (i <= aLength ? a[aLength - i] - 48 : 0) + (i <= bLength ? b[bLength - i] - 48 : 0) + Carry;
    Sum[i - 1] = 48 + (sum % 10);
    Carry = sum > 9 ? 1 : 0;
  }
  Sum[Larger] = Carry < 1 ? '\0' : '1';
  Larger -= Carry < 1 ? 1 : 0;
  for(int i = 0;i <= Larger / 2;++i) {
    char temp = Sum[i];
    Sum[i] = Sum[Larger - i];
    Sum[Larger - i] = temp;
  }
  return Sum;
}

// Allocate sufficient memory at `index' of `array2` for the sum of the digit strings at the indicies
// `first` and `second` (and `third` if `third` >= 0) of `array`.
char* Allocate(char** array2, int index, char** array, int first, int second, int third) {
  char* s = Addition(array[first], array[second]);
  if(third >= 0)
    s = Addition(s, array[third]);
  array2[index] = malloc(StringLength(s) * sizeof(char));
  return s;
}

// The main counting method.
char* CountFinal_String(int L) {
  char **arr = malloc(10 * sizeof(char*));
  for(int i = 0;i < 10;arr[i++] = "1");
  while(L > 1) {
    char **arr2 = malloc(10 * sizeof(char*));
    arr2[0] = Allocate(arr2, 0, arr, 4, 6, -1);
    arr2[1] = Allocate(arr2, 1, arr, 6, 8, -1);
    arr2[2] = Allocate(arr2, 2, arr, 7, 9, -1);
    arr2[3] = Allocate(arr2, 3, arr, 4, 8, -1);
    arr2[4] = Allocate(arr2, 4, arr, 0, 3, 9);
    arr2[5] = "0"; // A "knights's move" will never lead to or from 5.
    arr2[6] = Allocate(arr2, 6, arr, 0, 1, 7);
    arr2[7] = Allocate(arr2, 7, arr, 2, 4, -1);
    arr2[8] = Allocate(arr2, 8, arr, 1, 3, -1);
    arr2[9] = Allocate(arr2, 9, arr, 2, 4, -1);
    arr = arr2;
    L--;
  }
  char* Sum = "0";
  for(int i = 0;i < 10;Sum = Addition(Sum, arr[i++]));
  return Sum;
}

int main() {
  //printf("%ld\n", RecursiveCount(4));
  //printf("%d\n", BreadthFirstCount(3));
  printf("Non-string-based `CountFinal` method:\n");
  for(int i = 1;i <= 52; ++i)
    printf("%d => %llu\n", i, CountFinal(i));
  printf("\n\nString-based `CountFinal_String` method:\n");
  for(int i = 1; i <= 68; ++i)
    printf("%d => %s\n", i, CountFinal_String(i));

  // Testing for `AddToArray`
  /*
  int *a = malloc(3 * sizeof(int));
  *a = 5; *(a + 1) = 6; *(a + 2) = 7;
  int *b = malloc(3 * sizeof(int));
  *b = 12; *(b + 1) = 13; *(b + 2) = 14;
  int al = 3;
  int bl = 3;
  AddToArray(&al, &a, bl, b);
  printf("a[3] = %d\n", a[3]);
  */
  
  return 0;
}
