
// Module gérant l'interface graphique
// et les intéractions souris avec celle-ci
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "jeu.h"
#include "interface.h"
#include <MLV/MLV_all.h>

int aff_carte(paquet p,int c,int x,int y){
  MLV_Image* img;
  int taille = MLV_get_window_height()/11;
  char path_img[10];
  if(c<-1 || c>12){
    c=-1;
  }
  printf("c%d x%d y%d\n",c,x,y);
  if(c!=-1){
    printf("               val %d \n",p.r[c].val);
    if(c==0){
      sprintf(path_img,"assets/verso.png");
    }
    else{
      sprintf(path_img,"assets/%d.png",p.r[c].val);
    }
    img=MLV_load_image(path_img);
    if(img==NULL){
      printf("NULLLLL img\n");
    }
    MLV_resize_image(img,taille,taille);
    MLV_draw_image(img,x*taille,y*taille);
  }
  return 1;
}

// affiche la carte du dessus d'une zone

void aff_joueur(paquet p,joueur j){
  aff_carte(p,j.tas[1],16,8);

  aff_carte(p,j.defausse[0][1],5,8);
  aff_carte(p,j.defausse[1][1],7,8);
  aff_carte(p,j.defausse[2][1],9,8);
  aff_carte(p,j.defausse[3][1],11,8);
  aff_carte(p,j.defausse[4][1],13,8);

  aff_carte(p,j.main[1],6,10);
  aff_carte(p,j.main[2],8,10);
  aff_carte(p,j.main[3],10,10);
  aff_carte(p,j.main[4],12,10);
  aff_carte(p,j.main[5],14,10);
  MLV_actualise_window();
}

void aff_adv(paquet p,joueur j,int pos){
  int i;
  aff_carte(p,j.tas[1],4,2);
  for(i=6;i<15;i+=2){
    aff_carte(p,j.main[(i-4)/2],i,0);             //main
    aff_carte(p,j.defausse[0][1],i+1,2);   //defausse
  }
  MLV_actualise_window();
}

void aff_milieu(paquet p,milieu m){
  aff_carte(p,0,15,5);

  aff_carte(p,m.m[0][1],6,5);
  aff_carte(p,m.m[1][1],8,5);
  aff_carte(p,m.m[2][1],10,5);
  aff_carte(p,m.m[3][1],12,5);
  MLV_actualise_window();
}

void reset_fen(){
  MLV_clear_window(MLV_COLOR_WHITE);
  MLV_Image* tapis;
  tapis=MLV_load_image("assets/fond.png");
  int taille=MLV_get_window_height()/11;
  MLV_resize_image(tapis,taille*22,taille*11);
  MLV_draw_image(tapis,0,0);
  MLV_free_image(tapis);
  MLV_actualise_window();
}

// retourne dans x et y les variables correspondant à la case séléctionnée
int wait_inter(int *x,int *y){
  MLV_Keyboard_button keyb;
  MLV_Keyboard_modifier keym;
  int r,u,taille;
  taille=MLV_get_window_height()/11;
  r=MLV_wait_keyboard_or_mouse(&keyb,&keym,&u,x,y);
  printf("KEY%d, Mouse%d r%d\n",MLV_KEY,MLV_MOUSE_BUTTON,r);
  if(r==MLV_KEY){
    *x=0;
    *y=0;
    if(keyb==MLV_KEYBOARD_ESCAPE){
      *x=(-1);
    }
    return 2;
  }
  else if(r==MLV_MOUSE_BUTTON){
    (*x)=*x/taille;
    (*y)=*y/taille;
    return 1;
  }

  return 0;
}
