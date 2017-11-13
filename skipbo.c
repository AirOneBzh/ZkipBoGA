//// programme lancement du jeu de SkipBo

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "jeu.h"
#include "cartes.h"
/// éléments
// pioche
// pile milieu (4)
// pile défausse (5 par personne)
// tas principal (1 par personne)
// main

///// actions
// pioche
/// joue
// selection d'une carte
// sel d'une case où la poser   + det si mouv possible
// detecter etats
// etat = pile pleine> vider et mettre dans pioche; tas vide> gagnant; main vide>pioche;
// vider pile > mélanger
// faire une fonction de détection clic souris (renvoi int de zone de clic)
// une qui actualise les zones de clic dispo   (dans une liste)

int piocher(); // donne cartes (max 5 par personne réelle (si 3 joueurs ne donne pas de cartes à J4))
int selcase(); // si case contient une carte et aucune carte en main alors selection de la carte
int detetat(); // lancée pour vérifier l'état du jeu après déplacement d'une carte
int mouse_to_zone(); // transforme coords souris en zone d'une pile de jeu
int affiche_zone(); // affiche la carte du dessus d'une zone

int main(int argc,char **argv){
  options o;
  //paquet pioche,pile[4],def[5][4],tas[4];
  int i;
  sprintf(o.nom[0],"ZkipBoGA");
  paquet p;
  char lcens[30][5];
  for
  p=creer_paquet(162,12,lcens,12,"Skipbo",18);
  menufen(2,o);
  for(i=0;i<162;i++){
    printf("%d %s\n",p.c[i].valeur,p.c[i].ens);
  }

  return 1;
}
