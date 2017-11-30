/// module cartes
// fonctions liées aux cartes création mélange gestion

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cartes.h"

paquet creer_paquet(int nbca,int nbens,char lcens[30][5],int nbcaens,char cspe[],int nbspe){
  paquet p;
  int i,j,k;
  char ens[20];
  p.n=nbca;

  for(i=0;i<nbens;i++){
    sprintf(ens,"%s",lcens[i]);
    for(j=0;j<nbcaens;j++){
      p.c[i*nbcaens+j].valeur=j+1;    // valeur > int au besoin modifié par le prog
      strcpy(p.c[i*nbcaens+j].ens,ens);
    }
  }

  for(k=nbcaens*nbens;k<nbca;k++){
    p.c[k].valeur=0;                 // 0 = joker
    strcpy(p.c[k].ens,cspe);
  }
  return p;
}

int piocher(paquet pioche,paquet main,int n){
  while(main.n<n){
    //supp_carte(pioche)
    printf("e");
  }
  return 1;
  
} // donne cartes (max n )
