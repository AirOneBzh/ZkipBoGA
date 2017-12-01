// Module gérant l'interface graphique
// et les intéractions souris avec celle-ci
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "jeu.h"
#include "cartes.h"
#include <MLV/MLV_all.h>
int aff_carte(carte c,int x,int y){
  MLV_draw_rectangle(x*50,y*50,50,50);
  return 1;
}

// affiche la carte du dessus d'une zone

int aff_pile(pile z,int xx,int p){
  int y=8;
  int x=xx;
  carte c;
  depile(&z,&c);
  aff_carte(c,x,y);
  return 1;
}

int aff_serie(serie s,int x){
  int y=5;
  return 1;
}

int aff_milieu(milieu m){
  int i;
  for(i=3;i<10;i+=2){
    aff_serie(m.s[i-3/2],i);
  }
  aff_carte(c)

  return 1;
}

int aff_joueur(joueur j){
  int i;
  aff_serie(j.tas,13,8);
  for(i=2;i<11;i+=2){
    aff_pile(j.defausse[i],i,8);
  }
  for(i=3;i<12;i+=2){
    aff_carte(j.main[i],i,10);
  }
  return 1;
}
