// This Challenge: http://codegolf.stackexchange.com/questions/89062/write-a-vic-cipher-encoder 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

  ////////////////////////////////////
 // Version # 2 - Ungolfed Version //
////////////////////////////////////
char*Chain_Add(char*String,int End,int Start){
  if(Start>=End){return String;}
  char*C=malloc(strlen(String)+2);
  sprintf(C,"%s%c",String,'0'+(((String[Start]-'0')+(String[Start+1]-'0'))%10));
  return Chain_Add(C,End,Start+1);
}

char*Sequent(char*String){
  int J=strlen(String);
  char*P=malloc(J+2);
  for(int m=0;m<J;m++){
    P[m]=' ';
  }
  for(int v=0;v<J;v++){
    char G;
    int R;
    for(int u=0;u<J;u++){
      R=(u<1||String[u]<G)?u:R;
      G=(u<1||String[u]<G)?String[u]:G;
    }
    P[R]='0'+v;
    char*V=malloc(J);
    for(int t=0;t<J;t++){
      if(t!=R){
	V[t]=String[t];
      }
      else{
	V[t]='a';
      }
    }
    String=V;
  }
  return P;
}

char*Straddling_Checkerboard(char*C,char*Key,char*Message,char null){
  srand(time(NULL));
  int Msg_Len=strlen(Message);
  int Key_Len=strlen(Key);
  int R=rand()%Msg_Len;
  char*Q=malloc(Msg_Len+1);
  for(int u=R;u<Msg_Len;u++){
    Q[u-R]=Message[u];
  }
  Q[Msg_Len-R]='.';
  for(int H=0;H<R;H++){
    Q[H+Msg_Len-R+1]=Message[H];
  }
  char*Alphabet=malloc(26);
  for(int W=0;W<26;W++){
    Alphabet[W]='A'+W;
  }
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
  int r=0;
  for(int h=0;h<26;h++){
    if(strchr(e,Alphabet[h-r])!=NULL){
      for(int X=h-r;X<26;X++){
	Alphabet[X]=Alphabet[X+1];
      }
      r++;
    }
  }
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
  char*Values=malloc(28);
  strcat(Values,C);
  int B=strlen(e);
  for(int q=B;q<10;q++){
    for(int x=0;x<10;x++){
      char J[2]={C[q],C[x]};
      Values[B]='0'+atoi(J);
      B++;
    }
  }
  char*Encoded=malloc(Msg_Len*2+4);
  for(int J=0;J<=Msg_Len;J++){
    int K=0;
    for(int X=0;X<28;X++){
      if(Q[J]==Checkerboard[X]){
	char F[3];
	sprintf(F,"%d",Values[X]-'0');
	strcat(Encoded,F);
	//printf("F = %s while Q[J] = %c and Checkerboard[X] = %c and Encoded = %s\n",F,Q[J],Checkerboard[X],Encoded);
	K=1;
      }	
    }
    if(K<1){
      Encoded[strlen(Encoded)]=Q[J];
    }
  }
  int Encded_Len=strlen(Encoded);
  if(Encded_Len%5>0){
    char*P=malloc(5-Encded_Len%5);
    for(int E=0;E<5-Encded_Len%5;E++){
      P[E]=null;
    }
  strcat(Encoded,P);
  }
  return Encoded;
}

char*Transpose(char*Message,char*K1){
  int Msg_Len=strlen(Message),K1_Len=strlen(K1);
  char*T=malloc(Msg_Len);
  int F=0;
  for(int i=0;i<K1_Len;i++){
    for(int y=0;y<K1_Len;y++){
      if(K1[y]=='0'+i){
	for(int u=y;u<Msg_Len;u+=K1_Len){
	  T[F]=Message[u];
	  F++;
	}
      }
    }
  }
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
    for(int v=0;v<K2_Len;v++){
      T[F]=Message[P];
      P++;F++;
      if(K2[v+1]-'0'==u){
        for(int C=1;C<K2_Len-v;C++){
	  F+=K2_Len-v-C;
	  for(int E=0;E<=v+C;E++){
	    if(F<Msg_Len&P<Msg_Len){
	      T[F]=Message[P];
	    }
	    F++;P++;
	  }
	}
	break;
      }
    }
    if(F>Msg_Len){
      break;
    }
  }
  int U=0;
  for(int g=0;g<Msg_Len;g++){
    U=(T[g]-'0'<10&-1<T[g]-'0')?U+1:U;
  }
  for(int j=U;j<Msg_Len;j++){
    for(int x=0;x<Msg_Len;x++){
      if(T[x]==' '){
	T[x]=Message[j];
	break;
      }
    }
  }
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
  char*G=Chain_Add(M,5,0);
  for(int y=0;y<10;y++){
    G[y]='0'+(((S1[y]-'0')+(G[y]-'0'))%10);
  }
  char*N="0123456789";
  char*T=malloc(10);
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
  int p,q;
  for(int b=49;b>10;b++){
    if(U[b]!=U[b-1]){
      q=a_id+(U[b]-'0');
      p=a_id+(U[b-1]-'0');
      break;
    }
  }
  char*seqT=Sequent(T);
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
  char*C=malloc(10);
  for(int b=40;b<50;b++){
    C[b-40]=U[b];
  }
  C=Sequent(C);
  char*Transposed_2=Disrupted_Transpose(Transpose(Straddling_Checkerboard(C,Phrase,Message,null),K1),K2);
  int O=0;
  for(int B=0;B<strlen(Transposed_2)/5+1;B++){
    if(B==strlen(Transposed_2)/5-date[strlen(date)-1]+'1'){
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
  VIC_Encoder("HIDE.THEYKNOWABOUTOURWHEREABOUTS.WEHAVEAMOLEINOURSYSTEM.","TORIANES","YOURETERMINATEDHASTALAVISTABABY",6,"1052017","23657",'1');
}
