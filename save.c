#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jeu.h"
#include <MLV/MLV_all.h>


void save_mid(milieu jeu, FILE* f){
  int i,j;
  fprintf(f,"M:\np:\n");
  for(i=0;i<=jeu.pioche[0];i++){
    fprintf(f,"%d ",jeu.pioche[i]);
  }
  fprintf(f,"-1\nm:\n");
  for(i=0;i<4;i++){
    for(j=0;j<=jeu.m[i][0];i++){
      fprintf(f,"%d ",jeu.m[i][j]);
    }
    fprintf(f,"-1\n");
  }
}

void save_j(joueur j, FILE* f){
  int i,k;
  fprintf(f,"J:\nnom %s ia %d\ntas:\n",j.nom,j.ia);
  for(i=0;i<=j.tas[0];i++){
    fprintf(f,"%d ",j.tas[i]);
  }
  fprintf(f,"\ndef:\n");
  for(i=0;i<5;i++){
    for(k=0;k<=j.defausse[i][0];k++){
      fprintf(f,"%d ",j.defausse[i][k]);
    }
    fprintf(f,"-1\n");
  }
  fprintf(f,"main:\n");
  for(i=0;i<=j.main[0];i++){
    fprintf(f,"%d ",j.main[i]);
  }
  fprintf(f,"-1\n");
}

int save(char nom[19],joueur j[4],milieu m,options o){
  FILE *f;
  char chemin[30];
  int i;
  sprintf(chemin,"sauve/%s.save",nom);
  f=fopen(chemin,"w");
  if(f==NULL){
    fprintf(stderr,"Ouverture de %s impossible\n",nom);
    return 0;
  }
  fprintf(f,"Sauvegarde Partie Skipbo\n%s\n%d joueurs\n",nom,o.nbj);
  for(i=0;i<4;i++){
    if(o.ia[i]!=-1){
      fprintf(f,"%d %s %d\n",o.ia[i],o.nom[i],j[i].tas[0]);
    }
    else{
      fprintf(f,"-1\n");
    }
  }
  fprintf(f,"full %d pourc %d son %d \n",o.full,o.pourc,o.son);
  for(i=0;i<o.nbj;i++){
    save_j(j[i],f);
  }
  save_mid(m,f);
  fclose(f);
  return 1;
}

int load(){
  int tailleh = MLV_get_window_height();
  int taillew = MLV_get_window_width();
  char *l="",*nom="def",chemin[30];
  FILE *f=NULL;
  while(strcmp(nom,"")!=0 && f==NULL){
    MLV_wait_input_box(
      taillew*0.15,tailleh*0.45,
      taillew*0.7,tailleh*0.1,
      MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,
      "Nom de la partie à charger: (Vide pour annuler)  ",
      &nom
    );
    sprintf(chemin,"sauve/%s.save",nom);
    f=fopen(chemin,"r");
  }
  fgets(l,20,f);
  printf("%s",l);
  fclose(f);


  return 1;
}
