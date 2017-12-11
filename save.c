#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jeu.h"

int save(joueur *humain, num_joueur tour, milieu jeu, int nb_joueur){
  FILE* sauv=NULL;
  char name[30];
  sprintf(name,"sauve/%s.txt",chemin,humain[0].nom);
  sauv=fopen(name, "r+");
  if(sauv==NULL){
    printf("Erreur ouverture fichier %s name");
    return 0;
  }
  fprintf(sauv, "%d\n", tour);
  for(i=0; i<13; i++){// sauvegarde de pioche
    fprintf(sauv, "%d ", jeu.pioche[i]);
  }
  fprintf(sauv,"\n");
  for(k=0; k<4; k++){//sauvegarde defusse milieu
    for(j=0; j<13;j++){
      fprintf(sauv,"%d ", jeu.m[k][j]);
    }
    fputs("\n", sauv);
  }
  for(l=0;l<nb_joueur; l++){//sauvegarde cares joueurs
    fprintf(sauv, "%s %d\n", humain[l].nom);
    for(m=0; m<=humain[l].tas[0];m++){
      fprintf(sauv, "%d ", m++);
    }
    for(k=0;k<5; k++){
      for(j=0; j<defausse[k][0]; j++){
	fprintf(sauv, "%d ", defausse[k][j]);
      }
      fprintf(sauv,"\n");
    }
    for(k=0;k<=humain[l].main[0]; k++){
      fprintf(sauv, "%d ", humain[l].main[k]);
    }
    fprintf(sauv,"\n");
  }
  return 1;
}
  
  
