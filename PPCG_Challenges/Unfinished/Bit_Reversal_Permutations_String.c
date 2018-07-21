// This Challenge: http://codegolf.stackexchange.com/questions/88781/permute-a-string-using-bit-reversal

void J(int b){
  char p={0};
  char *ptr=&p;
  //char *ptr=p;
  //printf("%s\n",p);
  do{++*ptr;b/=2;printf("%c\n",*ptr);++ptr;}while(b>=1);
  printf("%s\n",ptr);
}

int main(){
  J(34);
}
