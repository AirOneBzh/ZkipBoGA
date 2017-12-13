//// programme lancement du jeu de SkipBo
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "jeu.h"
#include <MLV/MLV_all.h>
#include "interface.h"
#include "time.h"
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
void case_carte(int pos[][3 ],int x,int y,int *a,int *b){
  int i;
  for(i=0;i<15;i++){
    printf("x%d y%d posx %d posy %d\n",x,y,pos[i][1],pos[i][2]);
    if(pos[i][1]==x && pos[i][2]==y){
      *a=pos[i][0];
      *b=(pos[i][1]-4)/2;
      break;
    }
  }
  printf("a%d b%d\n",*a,*b);
}


void init_tas(joueur j[],milieu *m){
  int i;
  for(i=0;i<5;i++){
    init_cartes(j[0].defausse[i]);
    j[0].main[i+1]=-1;
  }
  j[0].main[0]=0;
  j[1].main[0]=0;
  init_cartes(j[0].tas);
  for(i=0;i<5;i++){
    init_cartes(j[1].defausse[i]);
    j[1].main[i+1]=-1;
  }
  for(i=0;i<4;i++){
    init_cartes(m->m[i]);
  }
  init_cartes(j[1].tas);
  for(i=1;i<163;i++){
    m->pioche[i]=i;
  }
  m->pioche[0]=162;
}

void init_zone(int pos[][3]){
  int i;
  for(i=6;i<15;i+=2){
    pos[(i-6)/2][0]=0;
    pos[(i-6)/2][1]=i;
    pos[(i-6)/2][2]=10;
    pos[(i-6)/2+5][0]=1;
    pos[(i-6)/2+5][1]=i-1;
    pos[(i-6)/2+5][2]=8;
  }
  pos[11][0]=2;
  pos[11][1]=16;
  pos[11][2]=8;
  for(i=6;i<13;i+=2){
    pos[12+(i-6)/2][0]=3;
    pos[12+(i-6)/2][1]=i;
    pos[12+(i-6)/2][2]=5;
  }
}

int main(int argc,char **argv){
  int i,taille;
  paquet p;
  srand(time(NULL));
  options o;



  char lcens[30][5];
  for(i=0;i<12;i++){
    sprintf(lcens[i],"%d",i+1);
  }

  o.nbj=2;  // normalement 4 mais on limite pour le début
  p=creer_paquet(162,12,lcens,12,"S",18);
  if(menufen("ZkipBoGA",o)==0){
    return 0;
  }

  taille=(MLV_get_desktop_width()*0.95)/22;
  fenetre(taille*22,taille*11);

  MLV_actualise_window();
  MLV_free_window();
  return 1;
}
