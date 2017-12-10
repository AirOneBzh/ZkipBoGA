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
void case_carte(int x,int y,int *a,int *b){
  int i;
  for(i=6;i<15;i+=2){
    if(y==10 && x==i){
      *a=0;
      *b=(i-4)/2;
    }
    if(y==8 && x==i-1){ //defausse
      *a=1;
      *b=(i-5)/2;
    }
    if(y==5 && x==i){
      *a=3;
      *b=(i-4)/2;
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

int main(int argc,char **argv){
  srand(time(NULL));
  options o;
  int i,taille,a,b;
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
  init_tas(j,&m);
  reset_fen();
  mel_pioche(m.pioche);
  printf("pioooo%d \n",m.pioche[1]);
  piocher(m.pioche,j[0].main,5);
  piocher(m.pioche,j[1].main,5);
  aff_joueur(p,j[0]);
  aff_adv(p,j[1],2);
  aff_milieu(p,m);
  int x,y,pasfin=1,c=-1,selx,sely;
  while(pasfin!=0){
    wait_inter(&x,&y);
    if(x==-1 && y==0){
      printf("ECHAP %d\n",pasfin);
      pasfin=0;
      break;
    }
    case_carte(x,y,&a,&b);
    if(selx!=-1){
      selx=a;
      sely=b;
      MLV_draw_rectangle(x*taille-1,y*taille-1,taille+2,taille+2,MLV_COLOR_WHITE);
    }
    else{
      if(selx==0){
        c=ret_carte_m(j[0].main,sely);
      }
      if(a==3){
        aj_carte(m.m[sely],c);
      }
    }
    aff_joueur(p,j[0]);
    aff_milieu(p,m);
  }

  printf("inter %d %d \n",x,y);

  MLV_actualise_window();
  MLV_free_window();
  return 1;
}
