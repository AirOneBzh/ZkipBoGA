// définition de la structure du jeu de SkipBo

typedef enum {J1,J2,J3,J4} num_joueur;
#ifndef CARTES_H
#include "cartes.h"

typedef struct {
  char nom[30];
  num_joueur n;
  stock tas;
  pile defausse[5];   // def[i].nb=
  carte main[6];     // main[0].val=nb cartes en main
} joueur ;

typedef struct{
  paquet pioche;
  serie m[4];
} milieu;

typedef struct {
  char nom[30];    //nom du Jeu
  int nbj;          // nombre de joueurs max quand envoyé par le jeu et nb joueur réel renvoyé par module
  int ia[4];       // ia[0] nombre, ia[1,2,3]=1,2,3 niveau de chacune ia
} options;

int menufen(int nbmenu,options o);
int fenetre(int l,int h);
#endif
