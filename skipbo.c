//// programme lancement du jeu de SkipBo
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "jeu.h"
#include <MLV/MLV_all.h>
#include "interface.h"
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


int selzone(int z[][50],carte sel,int x,int y); // si case contient une carte et aucune carte en main alors selection de la carte
int detetat(); // lancée pour vérifier l'état du jeu après déplacement d'une carte
int mouse_to_zone(); // transforme coords souris en zone d'une pile de jeu



int main(int argc,char **argv){
  options o;
  int i;
  joueur j;
  sprintf(o.nom,"ZkipBoGA");
  milieu mil;
  char lcens[30][5];
  for(i=0;i<12;i++){
    sprintf(lcens[i],"%d",i+1);
  }
  o.nbj=4;
  mil.pioche=creer_paquet(162,12,lcens,12,"S",18);
  if(menufen(2,o)==0){
    return 0;
  }
  for(i=0;i<162;i++){
    printf("%d %s\n",mil.pioche.c[i].val,mil.pioche.c[i].ens);
  }
  fenetre(80*22,80*11);
  MLV_clear_window(MLV_rgba(38,133,52,255));
  printf("%d",EOF);
  aff_joueur(j);
  MLV_actualise_window();
  MLV_wait_seconds(10);
  MLV_free_window();
  return 1;
}
