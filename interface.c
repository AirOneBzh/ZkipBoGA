// Module gérant l'interface graphique
// et les intéractions souris avec celle-ci
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "jeu.h"
#include "interface.h"
#include <MLV/MLV_all.h>

int aff_carte(carte c,int x,int y){
  MLV_draw_rectangle(x*80,y*80,80,80,MLV_COLOR_RED);
  return 1;
}

// affiche la carte du dessus d'une zone

int aff_pile(pile z,int xx,int p){
  int y=8;
  int x=xx;
  carte c;
  c=z.c[0];
  aff_carte(c,x,y);
  return 1;
}

int aff_serie(serie s,int x){
  int y=5;
  return y;
}

/*int aff_milieu(milieu m){
  int i;
  for(i=3;i<10;i+=2){
    aff_serie(m.m[i-3/2],i);
  }
  aff_carte(m.pioche.c[0],12,5);
  return 1;
}*/

int aff_stock(stock s,int p){
  //aff_carte(vide,12.7,8);
  aff_carte(s.c[0],16,8);
  return 1;
}

int aff_joueur(joueur j){
  int i;
  aff_stock(j.tas,1);
  for(i=5;i<14;i+=2){
    aff_pile(j.defausse[i],i,8);
  }
  for(i=6;i<15;i+=2){
    aff_carte(j.main[i],i,10);
  }
  return 1;
}
