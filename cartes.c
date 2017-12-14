/// module cartes
// fonctions liées aux cartes création mélange gestion

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jeu.h"
paquet creer_paquet(int nbca,int nbens,char lcens[30][5],int nbcaens,char cspe[],int nbspe){
  paquet p;
  int i,j,k;
  char ens[20];
  p.nb=nbca;

  for(i=0;i<nbens;i++){
    sprintf(ens,"%s",lcens[i]);
    for(j=0;j<nbcaens;j++){
      p.r[i*nbcaens+j].val=j+1;    // valeur > int au besoin modifié par le prog
      strcpy(p.r[i*nbcaens+j].ens,ens);
    }
  }

  for(k=nbcaens*nbens;k<nbca;k++){
    p.r[k].val=0;                 // 0 = joker
    strcpy(p.r[k].ens,cspe);
  }
  return p;
}


void init_cartes(int c[]){
  c[0]=1;
  c[1]=(-1);
}

// fonction decaler cartes
// void dec_carte(int p[],int n);
// fonction mettre trous à la fin
//deplace des cartes contenus dans un paquet
void aj_carte(int p[],int c){
  int i;
  for(i=p[0];i>=1;i--){

    p[i+1]=p[i];
  }
  p[0]++;
  p[1]=c;
}

void echanger_cartes(int p[],int r,int m){
  int t;
  t=p[r+1];
  p[r+1]=p[m+1];
  p[m+1]=t;
}

void aj_carte_m(int p[],int c,int n){
  int i;
  if(p[n]!=-1){
    for(i=p[0];i>=1;i--){
      p[i+1]=p[i];
    }
  }
  p[0]++;
  p[n]=c;
}
// prends une carte position m et la remplace par le vide
int ret_carte_m(int p[],int n){
  int c=p[n];
  p[n]=-1;
  p[0]--;
  return c;
}
// prends une carte en position n et décale la suite (pour ne laisser aucun vide)
int ret_carte_n(int p[],int n){
  int i,c;
  c=ret_carte_m(p,n);
  for(i=n;i<=p[0];i++){
    p[i]=p[i+1];
  }
  return c;
}
// pioche une carte sur le dessus de la pile
int ret_carte(int p[]){
  return ret_carte_n(p,1);
}

void tri_carte(paquet p,int c[]){
  int i,tmp;
  for(i=1;i<c[0];i++){
    if(p.r[c[i]].val>p.r[c[i+1]].val){
      tmp=c[i];
      c[i]=c[i+1];
      c[i+1]=tmp;
    }
  }
}

void mel_pioche(int p[]){
  int i,r,n,c;
  n=rand()%(3*p[0])+(3*p[0]);
  for(i=0;i<n;i++){
    r=rand()%161+1;
    c=ret_carte_n(p,r);
    aj_carte(p,c);
  }
}

int piocher(int pioche[],int main[],int n){
  // son_dist
  int c;
  while(main[0]<n){
    // depl_carte pioche.carte[] main[]
    c=ret_carte(pioche);
    aj_carte(main,c);
  }
  return 1;

} // donne cartes (max n )
