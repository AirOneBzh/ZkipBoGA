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
    for(j=0;j<=jeu.m[i][0];j++){
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
  sprintf(chemin,"save/%s.zngs",nom);
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

void ligne(char *l,FILE *f){
  fgets(l,50,f);
}

void scanl(char *l,int t[]){
  int i,n,c;
  sscanf(l,"%d ",&n);
  for(i=0;i<=n+1;i++){
    sscanf(l,"%d ",&c);
    l[i*2]=' ';
    t[i]=c;
  }
}

int load_j(joueur *j,FILE* f){
  char l[50];
  int i;
  ligne(l,f);   //J:
  ligne(l,f);   // nom J%d ia %d
  sscanf(l,"nom %s ia %d",j->nom,&j->ia);
  ligne(l,f);
  ligne(l,f);
  scanl(l,j->tas);
  ligne(l,f);
  ligne(l,f);
  for(i=0;i<5;i++){
    scanl(l,j->defausse[i]);
  }
  ligne(l,f);
  ligne(l,f);
  scanl(l,j->main);
  return 1;
}

int load_mid(milieu *m,FILE *f){
  char l[50];
  int i;
  ligne(l,f);
  ligne(l,f);
  ligne(l,f);
  scanl(l,m->pioche);
  ligne(l,f);
  for(i=0;i<4;i++){
    ligne(l,f);
    scanl(l,m->m[i]);
  }
  return 1;
}

int load(conf *confjeu){

  int tailleh = MLV_get_window_height();
  int taillew = MLV_get_window_width();
  char l[20]="",*nom="def",chemin[30];
  FILE *f=NULL;
  int i;
  while(strcmp(nom,"")!=0 && f==NULL){
    MLV_wait_input_box(
      taillew*0.15,tailleh*0.45,
      taillew*0.7,tailleh*0.1,
      MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,
      "Nom de la partie à charger: (Vide pour annuler)  ",
      &nom
    );
    if(nom[0]=='\0'){
      return 0;
    }
    sprintf(chemin,"save/%s.zngs",nom);
    f=fopen(chemin,"r");
  }
  ligne(l,f);
  ligne(confjeu->o.partie,f);
  ligne(l,f);
  sscanf(l,"%d joueurs",&confjeu->o.nbj);
  for(i=0;i<confjeu->o.nbj;i++){
    sscanf(l,"%d %s %*d ",&confjeu->j[i].ia,confjeu->j[i].nom);
  }
  for(i=confjeu->o.nbj;i<4;i++){
    confjeu->j[i].ia=-1;
  }
  ligne(l,f);
  sscanf(l,"full %d pourc %d son %d",&confjeu->o.full,&confjeu->o.pourc,&confjeu->o.son);
  for(i=0;i<confjeu->o.nbj;i++){
    load_j(&confjeu->j[i],f);
  }
  load_mid(&confjeu->m,f);

  fclose(f);
  return 1;
}
