/// module cartes
// fonctions liées aux cartes création mélange gestion

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int valeur;
  char ens[20];         // enseigne (couleur) ou permet de différencier cartes
} carte;

typedef struct {
  carte c[200];
  int n;           // taille réelle paquet
} paquet;

paquet creer_paquet_skipbo(){
  paquet p;
  int i,j,k;
  char ens[20];
  p.n=152;
  for(i=0;i<12;i++){
    sprintf(ens,"%d",i+1);
    for(j=0;j<12;j++){              
      p.c[i*12+j].valeur=j+1;
      strcpy(p.c[i*12+j].ens,ens);
    }
  }
  
  for(k=i*12+j;k<i*12+j+18;k++){
    p.c[k].valeur=0;                 // 0 = joker
    strcpy(p.c[k].ens,"j");
  }
  return p;
}

int main(){
  paquet p = creer_paquet_skipbo();
  int i,j; 
}
