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
      p.c[i*nbcaens+j].val=j+1;    // valeur > int au besoin modifié par le prog
      strcpy(p.c[i*nbcaens+j].ens,ens);
    }
  }

  for(k=nbcaens*nbens;k<nbca;k++){
    p.c[k].val=0;                 // 0 = joker
    strcpy(p.c[k].ens,cspe);
  }
  return p;
}

int depl_carte(int d[],int a[]){
  int i;
  a[n_a]=d[0];
  for(i=0;i<n_d-1;i++){

  }
}



int piocher(paquet pioche,joueur j,int n){
  // son_dist
  while(j.main[0].val<n){
    // depl_carte pioche.carte[] main[]
  }
  return 1;

} // donne cartes (max n )
