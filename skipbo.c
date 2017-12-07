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


int detetat(); // lancée pour vérifier l'état du jeu après déplacement d'une carte
int mouse_to_zone(); // transforme coords souris en zone d'une pile de jeu



int main(int argc,char **argv){
  options o;
  int i,taille;
  joueur j[4];
  sprintf(o.nom,"ZkipBoGA");
  paquet p;
  milieu m;
  char lcens[30][5];
  for(i=0;i<12;i++){
    sprintf(lcens[i],"%d",i+1);
  }
  o.nbj=4;
  p=creer_paquet(162,12,lcens,12,"S",18);
  if(menufen(2,o)==0){
    return 0;
  }
  taille=(MLV_get_desktop_width()*0.95)/22;
  fenetre(taille*22,taille*11);
  reset_fen();
  aff_joueur(p,j[0]);
  aff_adv(p,j[1],2);
  aff_milieu(p,m);
  int x,y;
  while(1){
    wait_inter(&x,&y);
    if(x==-1 && y==0){
      printf("ECHAP\n");
      return 0;
    }
    printf("inter %d %d \n",x,y);
  }
  MLV_actualise_window();
  MLV_wait_seconds(10);
  MLV_free_window();
  return 1;
}
