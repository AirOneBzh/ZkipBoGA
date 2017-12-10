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

//deplace des cartes contenus dans un paquet
void aj_carte(int p[],int c){
  int i;
  for(i=1;i<=p[0];i++){
    p[i+1]=p[i];
  }
  p[0]++;
  p[1]=c;
}

int ret_carte(int p[]){
  int i,c;
  c=p[1];
  for(i=1;i<=p[0];i++){
    p[i]=p[i+1];
  }
  p[0]--;
  return c;
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
