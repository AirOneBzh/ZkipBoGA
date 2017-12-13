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
  int i,carre,tour,jNfini=1,r;
  int zones[48][3],distrib[]={0,0,30,25,20};
  srand(time(NULL));
  options o;
  coord c;
  paquet p;
  joueur j[4];
  milieu mil;


  char lcens[30][5];
  for(i=0;i<12;i++){
    sprintf(lcens[i],"%d",i+1);
  }

  o.nbj=2;  // normalement 4 mais on limite pour le début
  p=creer_paquet(162,12,lcens,12,"S",18);
  if(menufen("ZkipBoGA",o)==0){
    return 0;
  }

  carre=(MLV_get_desktop_width()*0.95)/22;
  fenetre(carre*22,carre*11);
  reset_fen();
  init_tas(j,&mil);
  init_zone(zones);

  mel_pioche(mil.pioche);
  for(i=0;i<o.nbj;i++){
    piocher(mil.pioche,j[i].tas,distrib[o.nbj]);
  }
  // au début du jeu on rempli le tas d'objectif (celui devant être vidé)

  tour=0;

  while(jNfini){

    if(tour==o.nbj){
      tour=0;
    }

    piocher(mil.pioche,j[tour].main,5);

    aff_joueur(p,j[0]);
    aff_adv(p,j[1],2);
    aff_milieu(p,mil);

    while(1){
      c=wait_inter(carre);
      if(c.x==-1 && c.y==2){
        MLV_free_window();
        return 1;
      }
      if(c.x!=0 && c.y!=0){
        for(i=0;i<48;i++){
          if(c.x==zones[i][1] && c.y==zones[i][2]){
            r=zones[i][0];
          }
        }
      }
      if(r==0){

      }
    }
  }

  MLV_actualise_window();
  MLV_free_window();
  return 1;
}
