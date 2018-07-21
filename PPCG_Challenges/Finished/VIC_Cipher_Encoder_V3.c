// This Challenge: http://codegolf.stackexchange.com/questions/89062/write-a-vic-cipher-encoder 
#include<stdio.h>
#define m(x)malloc(x)
#define Y(x)strlen(x)
typedef int i;typedef char*c;

  //////////////////////////////////////////////////////////////////////////////////////////////////
 // Version # 3 - Semi-Golfed Version (Outputs warnings upon compilation, but works nonetheless) //
//////////////////////////////////////////////////////////////////////////////////////////////////
c _(c A,i B,i D){
  if(D>=B){return A;}
  c C=m(Y(A)+2);
  sprintf(C,"%s%c",A,48+(A[D]+A[D+1]-96)%10);
  return _(C,B,D+1);
}

c l(c A){
  i J=Y(A);
  c P=m(J+2);
  for(i m=0;m<J;m++){
    P[m]=32;
  }
  for(i v=0;v<J;v++){
    char G;
    i R;
    for(i u=0;u<J;u++){
      R=u<1|A[u]<G?u:R;
      G=u<1|A[u]<G?A[u]:G;
    }
    P[R]=48+v;
    c V=m(J);
    for(i t=0;t<J;t++){
      V[t]=t!=R?A[t]:97;
    }
    A=V;
  }
  return P;
}

c S(c C,c N,c I,char U){
  srand(time(NULL));
  i M=Y(I);
  i O=Y(N);
  i R=rand()%M;
  c Q=m(M+1);
  for(i u=R;u<M;u++){
    Q[u-R]=I[u];
  }
  Q[M-R]=46;
  for(i H=0;H<R;H++){
    Q[H+M-R+1]=I[H];
  }
  c g=m(28);
  c V=m(28);
  strcat(V,C);
  sprintf(g,"%s%s",N,"BCDFGHJKLMPQUVWXYZ.#");
  i B=Y(N);
  for(i q=B;q<10;q++){
    for(i x=0;x<10;x++){
      char J[2]={C[q],C[x]};
      V[B]=48+atoi(J);
      B++;
    }
  }
  c w=m(M*2+4);
  for(i J=0;J<=M;J++){
    i K=0;
    for(i X=0;X<28;X++){
      if(Q[J]==g[X]){
	char F[3];
	sprintf(F,"%d",V[X]-48);
	strcat(w,F);
	K=1;
      }	
    }
    if(K<1){
      w[Y(w)]=Q[J];
    }
  }
  i f=Y(w);
  if(f%5>0){
    c P=m(5-f%5);
    for(i E=0;E<5-f%5;E++){
      P[E]=U;
    }
  strcat(w,P);
  }
  return w;
}

c a(c I,c U){
  i M=Y(I),K=Y(U);
  c T=m(M);
  i F=0;
  for(i b=0;b<K;b++){
    for(i y=0;y<K;y++){
      if(U[y]==48+b){
	for(i u=y;u<M;u+=K){
	  T[F]=I[u];
	  F++;
	}
      }
    }
  }
  return T;
}

c da(c I,c K){
  i e=Y(I),k=Y(K);
  c T=m(e);
  for(i y=0;y<e;y++){
    T[y]=32;
  }
  i F,P;
  F=P=0;
  for(i u=0;u<k;u++){
    for(i v=0;v<k;v++){
      T[F]=I[P];
      P++;F++;
      if(K[v+1]-48==u){
        for(i C=1;C<k-v;C++){
	  F+=k-v-C;
	  for(i E=0;E<=v+C;E++){
	    if(F<e&P<e){
	      T[F]=I[P];
	    }
	    F++;P++;
	  }
	}
	break;
      }
    }
    if(F>e){
      break;
    }
  }
  i U=0;
  for(i g=0;g<e;g++){
    U=T[g]-48<10&-1<T[g]-48?U+1:U;
  }
  for(i j=U;j<e;j++){
    for(i x=0;x<e;x++){
      if(T[x]==32){
	T[x]=I[j];
	break;
      }
    }
  }
  return a(T,K);
}

En(c n,c m,c k,i d,c v,c s,char u){
  c S1,S2;
  S1=m(10);
  S2=m(10);
  for(i i=0;i<20;i++){
    if(i<10){
      S1[i]=k[i];
    }
    else{
      S2[i-10]=k[i];
    }
  }
  S1=l(S1);
  S2=l(S2);
  c M=m(5);
  for(i i=4;i>-1;i--){
    M[i]=48+(s[i]-v[i])%10;
  }
  c G=_(M,5,0);
  for(i y=0;y<10;y++){
    G[y]=48+(S1[y]+G[y]-96)%10;
  }
  c N="0123456789";
  c T=m(10);
  for(i q=0;q<10;q++){
    for(i t=0;t<10;t++){
      if(N[t]==G[q]){
	T[q]=S2[t];
      }
    }
  }
  c Z=_(T,50,0);
  c U=m(50);
  for(i h=0;h<50;h++){
    U[h]=Z[h+10];
  }
  i p,q;
  for(i b=49;b>10;b++){
    if(U[b]!=U[b-1]){
      q=d+U[b]-48;
      p=d+U[b-1]-48;
      break;
    }
  }
  c V=m(50);
  i Ct=0;
  for(i j=0;j<10;j++){
    for(i o=0;o<10;o++){
      if(l(T)[o]==48+j){
	for(i x=o;x<o+41;x+=10){
	  V[Ct]=U[x];
	  Ct+=1;
	}
      }
    }
  }
  c K1=m(p);
  c K2=m(q);
  for(i D=0;D<p+q;D++){
    if(D<p){
      K1[D]=V[D];
    }
    else{
      K2[D-p]=V[D];
    }
  }
  K1=l(K1);
  K2=l(K2);
  c C=m(10);
  for(i b=40;b<50;b++){
    C[b-40]=U[b];
  }
  C=l(C);
  c t=da(a(S(C,m,n,u),K1),K2);
  i O=0;
  for(i B=0;B<Y(t)/5+1;B++){
    if(B==Y(t)/5-v[Y(v)-1]+49){
      printf("%s ",s);
    }
    else{
      for(i J=O;J<O+5;J++){
	printf("%c",t[J]);
      }
      printf(" ");
      O+=5;
    }
  }
}

i main(){
  En("WEAREDISCOVERED.TAKEWHATYOUCAN.BURNEVERYTHINGELSE.MOVETOSAFEHOUSEFOXTROT#3#.","SENATORI","THEFIRSTPRINCIPLEISTHATYOUMUSTNOTFOOLYOURSELFANDYOUARETHEEASIESTPERSONTOFOOL",9,"3172016","47921",'4');
}
