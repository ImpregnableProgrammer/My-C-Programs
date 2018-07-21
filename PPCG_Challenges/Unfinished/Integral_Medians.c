//
// This Challenge: https://codegolf.stackexchange.com/questions/53100/integral-triangles-and-integral-medians

void Integral_Medians(int N) {
  int v=0;
  //int z=0;
  for(int a=1;a<=N;++a) {
    for(int b=1;b<=N;++b) {
      for(int c=1;c<=N;++c) {
	//if(4*a*a*c*c-pow(a*a+c*c-b*b,2)>0) {
	//printf("%d, %d, %d, %f\n",a,b,c,4*a*a*(c+1)*(c+1)-pow(a*a+(c+1)*(c+1)-b*b,2));
	//z+=1;
	//if(a==160&&b>=150) {
	//printf("%d, %d, %d, %f, %f, %f, %f\n",a,b,c,4*a*a*c*c-pow(a*a+c*c-b*b,2),sqrt(2*a*a+2*b*b-c*c)/2,sqrt(2*a*a+2*c*c-b*b)/2,sqrt(2*b*b+2*c*c-a*a)/2);
	//}
	if((a+b>c&&a+c>b&&c+b>a) && (!fmod(sqrt(2*a*a+2*b*b-c*c)/2,1) || !fmod(sqrt(2*a*a+2*c*c-b*b)/2,1) || !fmod(sqrt(2*b*b+2*c*c-a*a)/2,1)) && (a<=b&&b<=c)) {
	  //printf("%d, %d, %d, %f\n",a,b,c,sqrt(2*a*a+2*b*b-c*c)/2);
	  //int q=!fmod(sqrt(2*a*a+2*b*b-c*c)/2,1)+!fmod(sqrt(2*a*a+2*c*c-b*b)/2,1)+!fmod(sqrt(2*b*b+2*c*c-a*a)/2,1);
	  //printf("%d, %d, %d, %f, %f, %f, %d\n",a,b,c,sqrt(2*a*a+2*b*b-c*c)/2,sqrt(2*a*a+2*c*c-b*b)/2,sqrt(2*b*b+2*c*c-a*a)/2,q);
	  //v+=(a==b||a==c||b==c)?1.0/q:0.5/q;
	  //printf("%f\n",v);
	  ++v;
	}
      }
    }
  }
  printf("%d\n",v);
}

int main(int argc, char **argv) {
  //for(int u=6;u<201;++u) {
  Integral_Medians(2000);
  //printf("%d\n",u);
  //}
  //printf("%d\n",!0+!0+!0);
}
