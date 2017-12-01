//// programme lancement du jeu de SkipBo
#ifndef CARTES_H
#include "cartes.h"
#endif
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "jeu.h"
#include <MLV/MLV_all.h>
/// éléments
// pioche
// pile milieu (4)
// pile défausse (5 par personne)
// tas principal (1 par personne)
// main
// carte sel

///// actions
// pioche
/// joue
// selection d'une carte
// sel d'une case où la poser   + det si mouv possible
// detecter etats
// etat = pile pleine> vider et mettre dans pioche; tas vide> gagnant; main vide>pioche;
// vider pile > mélanger main vide piocher
// faire une fonction de détection clic souris (renvoi int de zone de clic)
// une qui actualise les zones de clic dispo   (dans une liste)


int selzone(zone[],*main,x,y); // si case contient une carte et aucune carte en main alors selection de la carte
int detetat(); // lancée pour vérifier l'état du jeu après déplacement d'une carte
int mouse_to_zone(); // transforme coords souris en zone d'une pile de jeu


int main(int argc,char **argv){
  options o;
  //paquet pioche,pile[4],def[5][4],tas[4];
  int i;
  joueur j;

  sprintf(o.nom[0],"ZkipBoGA");
  sprintf(o.nom[1],"Quitter");
  paquet p;
  char lcens[30][5];
  for(i=0;i<12;i++){
    sprintf(lcens[i],"%d",i+1);
  }
  p=creer_paquet(162,12,lcens,12,"S",18);
  menufen(3,o);
  for(i=0;i<162;i++){
    printf("%d %s\n",p.c[i].valeur,p.c[i].ens);
  }
  fenetre(500,500);
  MLV_clear_window(MLV_rgba(38,133,52,255));
  aff_joueur(j);
  MLV_actualise_window();
  MLV_close_window();
  return 1;
}
