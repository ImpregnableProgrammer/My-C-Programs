// This Challenge: https://codegolf.stackexchange.com/a/125554/52405
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// `R' replaces the `The ' at the beginning of the given string, and `S' sorts the given string array
// `S' is equivalent to the `Lexicographical_Sort' function in the file `Sorter.c'
// 284 bytes in total for functions `R` and `S`
char*R(s,i,j,e)char*s;{char*T=malloc(8);for(i=j=0;s[i]!='\0';T[i-j]=s[i],T[i-~j]='\0',T=!(e=strcasecmp(T,"The "))?T+4:T,j=!e?i+1:j,++i);return T;}
char**S(s,a,l,j)char**a;{char*G;for(l=0;l<s;++l){for(j=l+1;j<s;++j){if(strcasecmp(R(a[l]),R(a[j]))>0)G=a[j],a[j]=a[l],a[l]=G;}}return a;}

// Alternative solution utilizing the `qsort' function: https://www.gnu.org/software/libc/manual/html_node/Comparison-Functions.html#Comparison-Functions
// 216 bytes total for functions `R' and `M'
// Relevant: https://bewuethr.github.io/sorting-strings-in-c-with-qsort/
M(void*a,void*b){return strcasecmp(R(*(char**)a),R(*(char**)b));}

// Final solution utilizing the `qsort' and `strstr' functions to replace `R' and `S', respectively
// https://www.gnu.org/software/libc/manual/html_node/Search-Functions.html#Search-Functions
// 135 bytes total for function `M2'
M2(void*a,void*b){char*A,*B;A=*(char**)a;B=*(char**)b;A=strcasestr(A,"The ")?A+4:A;B=strcasestr(B,"The ")?B+4:B;return strcasecmp(A,B);}

int main(int argc,char**argv) {
  // Advance the `argv' array beginning index by one; In other words, "remove" the first element
  argv++;
  // Sorts IN PLACE
  qsort(argv,argc-1,8,M2);
  // Just print the resulting sorted array in a prettier way
  printf("[");
  for(int b = 0;b < argc-2;b++) {
    printf("%s, ",argv[b]);
  }
  printf("%s]\n",argv[argc-2]);
}
