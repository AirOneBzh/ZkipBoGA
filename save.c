#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int save_mid(milieu jeu, FILE* fichier){
  
}




int save_j(joueur player, FILE* fichier){}
