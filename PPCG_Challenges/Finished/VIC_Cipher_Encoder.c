// This Challenge: http://codegolf.stackexchange.com/questions/89062/write-a-vic-cipher-encoder
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

  /////////////////////////////////
 // Version # 1 - Check Version //
/////////////////////////////////
char*Chain_Add(char*A,int B,int D/*=0*/){
  if(D>=B){return A;}
  char*C=malloc(strlen(A)+2);
  sprintf(C,"%s%c",A,'0'+(((A[D]-'0')+(A[D+1]-'0'))%10));
  return Chain_Add(C,B,D+1);
}

char*Sequent(char*A){
  int J=strlen(A);
  char*P=malloc(J+2);
  for(int m=0;m<J;m++){
    P[m]=' ';
  }
  for(int v=0;v<J;v++){
    char G;
    int R;
    for(int u=0;u<J;u++){
      R=(u<1||A[u]<G)?u:R;
      G=(u<1||A[u]<G)?A[u]:G;
    }
    P[R]='0'+v;
    char*V=malloc(J);
    for(int t=0;t<J;t++){
      if(t!=R){
	V[t]=A[t];
      }
      else{
	V[t]='a';
      }
    }
    A=V;
  }
  return P;
}

char*Staddling_Checkerboard(char*C,char*Key,char*Message,char null){
  //printf("Beginning Straddling Checkerboard\n");
  srand(time(NULL));
  int Msg_Len=strlen(Message);
  int Key_Len=strlen(Key);
  int R=rand()%Msg_Len;
  char*Q=malloc(Msg_Len+1);
  for(int u=R;u<Msg_Len;u++){
    Q[u-R]=Message[u];
  }
  Q[Msg_Len-R]='.';
  //printf("Q  = %s\n",Q);
  for(int H=0;H<R;H++){
    Q[H+Msg_Len-R+1]=Message[H];
  }
  //printf("Q2 = %s\n",Q);
  char*Alphabet=malloc(26);
  for(int W=0;W<26;W++){
    Alphabet[W]='A'+W;
  }
  //printf("Alphabet_1 = %s\n",Alphabet);
  int q=0;
  char*e=malloc(Key_Len);
  for(int z=0;z<Key_Len;z++){
    if(strchr(e,Key[z])!=NULL){
      q++;
    }
    else{
      e[z-q]=Key[z];
    }
  }
  //printf("New Key = %s\n",e);
  int r=0;
  for(int h=0;h<26;h++){
    //printf("Alphabet[h-r]=%c at h=%d\n",Alphabet[h-r],h);
    if(strchr(e,Alphabet[h-r])!=NULL){
      //printf("Alphabet[h-r]=%c\n",Alphabet[h-r]);
      for(int X=h-r;X<26;X++){
	Alphabet[X]=Alphabet[X+1];
      }
      r++;
    }
  }
  //printf("Alphabet = %s\n",Alphabet);
  char*Checkerboard=malloc(28);
  for(int i=0;i<26;i++){
    if(i<strlen(e)){
      Checkerboard[i]=e[i];
    }
    else{
      Checkerboard[i]=Alphabet[i-strlen(e)];
    }
  }
  Checkerboard[26]='.';
  Checkerboard[27]='#';
  //printf("Checkerboard = %s\n",Checkerboard);
  char*Values=malloc(28);
  strcat(Values,C);
  //printf("Values = %s\n",Values);
  int B=strlen(e);
  for(int q=B;q<10;q++){
    for(int x=0;x<10;x++){
      char J[2]={C[q],C[x]};
      Values[B]='0'+atoi(J);
      B++;
    }
  }
  //printf("Values = %s\n",Values);
  char*Encoded=malloc(Msg_Len*2+4);
  for(int J=0;J<Msg_Len;J++){
    int K=0;
    for(int X=0;X<28;X++){
      if(Q[J]==Checkerboard[X]){
	char F[3];
	sprintf(F,"%d",Values[X]-'0');
	//printf("F = %s\n",F);
	strcat(Encoded,F);
	K=1;
      }	
    }
    if(K<1){
      Encoded[strlen(Encoded)]=Q[J];
    }
  }
  int Encded_Len=strlen(Encoded);
  //printf("Encoded = %s\n",Encoded);
  if(Encded_Len%5>0){
    char*P=malloc(5-Encded_Len%5);
    for(int E=0;E<5-Encded_Len%5;E++){
      P[E]=null;
    }
  strcat(Encoded,P);
  }
  //printf("Encoded = %s\n",Encoded);
  return Encoded;
}

char*Transpose(char*Message,char*K1){
  int Msg_Len=strlen(Message),K1_Len=strlen(K1);
  char*T=malloc(Msg_Len);
  //printf("Length of Message = %lu\n",strlen(Message));
  int F=0;
  for(int i=0;i<K1_Len;i++){
    for(int y=0;y<K1_Len;y++){
      if(K1[y]=='0'+i){
	for(int u=y;u<Msg_Len;u+=K1_Len){
	  T[F]=Message[u];
	  //printf("Message[u] = %c at u = %d at y = %d and i = %d\n",Message[u],u,y,i);
	  //printf("T = %s\n",T);
	  F++;
	}
      }
    }
  }
  //printf("T = %s\n",T);
  return T;
}

char*Disrupted_Transpose(char*Message,char*K2){
  int Msg_Len=strlen(Message),K2_Len=strlen(K2);
  char*T=malloc(Msg_Len);
  for(int y=0;y<Msg_Len;y++){
    T[y]=' ';
  }
  int F=0;
  int P=0;
  for(int u=0;u<K2_Len;u++){
    //printf("u = %d and P = %d and F = %d\n",u,P,F);
    for(int v=0;v<K2_Len;v++){
      T[F]=Message[P];
      //printf("P = %d and F = %d\n",P,F);
      P++;F++;
      if(K2[v+1]-'0'==u){
	//printf("K2[v+1] = %c at v+1=%d\n",K2[v+1],v+1);
	//printf("T = %s\n",T);
        for(int C=1;C<K2_Len-v;C++){
	  F+=K2_Len-v-C;
	  for(int E=0;E<=v+C;E++){
	    if(F<Msg_Len&P<Msg_Len){
	      T[F]=Message[P];
	    }
	    //printf("Message[P]=%c\n",Message[F]);
	    F++;P++;
	    //printf("P = %d\n",P);
	  }
	}
	break;
      }
    }
    if(F>Msg_Len){
      break;
    }
  }
  //printf("Message = %s\n",Message);
  //printf("Final P = %d and Final F = %d\n",P,F);
  int U=0;
  for(int g=0;g<Msg_Len;g++){
    U=(T[g]-'0'<10&-1<T[g]-'0')?U+1:U;
  }
  //printf("U = %d\n",U);
  for(int j=U;j<Msg_Len;j++){
    //printf("Message[j] = %c\n",Message[j]);
    for(int x=0;x<Msg_Len;x++){
      if(T[x]==' '){
	T[x]=Message[j];
	//printf("Message[j] = %c\n",Message[j]);
	break;
      }
    }
  }
  //printf("Okay = T = %s\n",T);
  //printf("Disrupted_Transpose = %s\n",Transpose(T,K2));
  return Transpose(T,K2);
}

void VIC_Encoder(char*Message,char*Phrase,char*Key,int a_id,char*date,char*m_id,char null){
  char*S1=malloc(10);
  char*S2=malloc(10);
  for(int i=0;i<20;i++){
    if(i<10){
      S1[i]=Key[i];
    }
    else{
      S2[i-10]=Key[i];
    }
  }
  S1=Sequent(S1);
  S2=Sequent(S2);
  char*M=malloc(5);
  for(int i=4;i>-1;i--){
    M[i]='0'+(((m_id[i]-'0')-(date[i]-'0'))%10);
  }
  //printf("M = %s\n",M);
  char*G=Chain_Add(M,5,0);
  //printf("G = %s\n",G);
  for(int y=0;y<10;y++){
    G[y]='0'+(((S1[y]-'0')+(G[y]-'0'))%10);
  }
  //printf("G2 = %s\n",G);
  char*N="0123456789";
  char*T=malloc(10);
  //printf("N  = %s\n",N);
  //printf("S2 = %s\n",S2);
  for(int q=0;q<10;q++){
    for(int t=0;t<10;t++){
      if(N[t]==G[q]){
	T[q]=S2[t];
      }
    }
  }
  char*Z=Chain_Add(T,50,0);
  char*U=malloc(50);
  for(int h=0;h<50;h++){
    U[h]=Z[h+10];
  }
  //printf("U = %s\n",U);
  int p,q;
  //printf("T = %s\n",T);
  for(int b=49;b>10;b++){
    if(U[b]!=U[b-1]){
      q=a_id+(U[b]-'0');
      p=a_id+(U[b-1]-'0');
      break;
    }
  }
  //printf("p = %d and q = %d\n",p,q);
  char*seqT=Sequent(T);
  //printf("seqT = %s\n",seqT);
  char*V=malloc(50);
  int Count=0;
  for(int j=0;j<10;j++){
    for(int o=0;o<10;o++){
      if(seqT[o]=='0'+j){
	for(int x=o;x<o+41;x+=10){
	  V[Count]=U[x];
	  Count+=1;
	}
      }
    }
  }
  //printf("V = %s\n",V);
  char*K1=malloc(p);
  char*K2=malloc(q);
  for(int D=0;D<p+q;D++){
    if(D<p){
      K1[D]=V[D];
    }
    else{
      K2[D-p]=V[D];
    }
  }
  K1=Sequent(K1);
  K2=Sequent(K2);
  //printf("K1 = %s and K2 = %s\n",K1,K2);
  char*C=malloc(10);
  for(int b=40;b<50;b++){
    C[b-40]=U[b];
  }
  C=Sequent(C);
  //printf("C = %s\n",C);
  //char*Encoded_1=Staddling_Checkerboard(C,Phrase,Message,null);
  //printf("Encoded # 1 = %s\n",Encoded_1);
  //char*Transposed_1=Transpose(Encoded_1,K1);
  //printf("Transposed_1 = %s\n",Transposed_1);
  //char*Transposed_2=Disrupted_Transpose(Transposed_1,K2);
  //printf("Transposed_2 = %s\n",Transposed_2);
  char*Transposed_2=Disrupted_Transpose(Transpose(Staddling_Checkerboard(C,Phrase,Message,null),K1),K2);
  int O=0;
  for(int B;B<strlen(Transposed_2)/5+1;B++){
    //printf("B = %d\n",B);
    //printf("date[-1] = %c\n",date[strlen(date)-1]);
    if(B==strlen(Transposed_2)/5-(date[strlen(date)-1]-'0')+1){
      printf("%s ",m_id);
    }
    else{
      for(int J=O;J<O+5;J++){
	printf("%c",Transposed_2[J]);
      }
      printf(" ");
      O+=5;
    }
  }
}
  

int main(){
  //printf("%s\n",Sequent("EDCBA"));
  VIC_Encoder("WEAREDISCOVERED.TAKEWHATYOUCAN.BURNEVERYTHINGELSE.MOVETOSAFEHOUSEFOXTROT#3#.","SENATORI","THEFIRSTPRINCIPLEISTHATYOUMUSTNOTFOOLYOURSELFANDYOUARETHEEASIESTPERSONTOFOOL",9,"3172016","47921",'4');
  //VIC_Encoder("HELLO.WORLD.","SENATORI","THEFIRSTPRINCIPLEISTHATYOUMUSTNOTFOOLYOURSELFANDYOUARETHEEASIESTPERSONTOFOOL",9,"3172012","47921",'4');  
  printf("\n");
  //printf("Transpose Result = %s\n",Transpose("4070201293124496481963541140628314164798694434424242715812173436481812124954512740592262843502423288014818229","6:;015794823"));
  //printf("Disrupted Transpose Result = %s\n",Disrupted_Transpose("060826428246674580151411542246272922961311401082918141441443423911845123433442202829348875804172492247949435684567","87<2:9456031;"));
  //Disrupted_Transpose("060826428246674580151411542246272922961311401082918141441443423911845123433442202829348875804172492247949435684567","87<2:9456031;");
}
