// définition de la structure du jeu de SkipBo

#ifndef CARTES_H
#include "cartes.h"

typedef struct {
  char nom[30];
  int ia;
  int tas[30];   //30
  int defausse[5][30];   // def[i].nb=
  int main[6];     // main[0].val=nb cartes en main
} joueur ;

typedef struct{
  int pioche[163];
  int m[4][13];
} milieu;


typedef struct {
  int nbj;          // nombre de joueurs max quand envoyé par le jeu et nb joueur réel renvoyé par module
  int ia[4];       // ia[0] nombre, ia[1,2,3]=1,2,3 niveau de chacune ia 0 -> pas une ia   si deux joueurs +1 bot -> [1]=0 [2]=1,2,3 pour l'instant uniquement 1
  char nom[4][20];
} options;

int menufen(char *nom,options o);
int fenetre(int l,int h);
#endif



////// ///////////////////////////  RÉFÉRENCES /////////////////////////////////////:
