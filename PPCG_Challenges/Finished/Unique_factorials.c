//
// This challenge: https://codegolf.stackexchange.com/a/124805/52405
#include <stdio.h>

// Initial attempt
/* f(a){return a<2?a:a*f(a-1);}
   Q(a,b,u,v){while(a&&b){u=v=1;while(f(u)<=a){u++;};while(f(v)<=b){v++;};a-=f(u-1);b-=f(v-1);if(u==v){return 0;}};return 1;} */

// BEGIN SUBMISSION
G(q,i){return gamma(q+1)>i?gamma(q):G(q+1,i);}
Q(a,b,u,v){while(a&&b){a-=u=G(1,a);b-=v=G(1,b);if(a==b)exit();}exit(0);}
// END SUBMISSION

void main() {
  printf("%d\n",Q(225,178));
}
