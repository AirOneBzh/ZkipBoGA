// Module gérant l'interface graphique
// et les intéractions souris avec celle-ci
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "jeu.h"
#include "interface.h"
#include <MLV/MLV_all.h>

int aff_carte(paquet p,int c,int x,int y){
  c=0;
  MLV_Image* img;
  int taille = MLV_get_window_height()/11;
  char path_img[10];
  if(p.r[c].val==0){
    sprintf(path_img,"assets/0.png");
  }
  else{
    sprintf(path_img,"assets/0.png");
  }
  img=MLV_load_image(path_img);
  MLV_resize_image(img,taille,taille);
  MLV_draw_image(img,x*taille,y*taille);
  int ecart = taille*0.1;
  printf("ecart %d\n",ecart);
  MLV_draw_rectangle(x*taille-8,y*taille-8,taille+8,taille+8,MLV_COLOR_RED);
  return 1;
}

// affiche la carte du dessus d'une zone

int aff_joueur(paquet p,joueur j){
  aff_carte(p,j.tas[0],16,8);

  aff_carte(p,j.defausse[0][0],5,8);
  aff_carte(p,j.defausse[0][0],7,8);
  aff_carte(p,j.defausse[0][0],9,8);
  aff_carte(p,j.defausse[0][0],11,8);
  aff_carte(p,j.defausse[0][0],13,8);

  aff_carte(p,j.main[0],6,10);
  aff_carte(p,j.main[0],8,10);
  aff_carte(p,j.main[0],10,10);
  aff_carte(p,j.main[0],12,10);
  aff_carte(p,j.main[0],14,10);
  MLV_actualise_window();
  return 1;
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
    printf("x%d y%d\n",*x,*y);
    if(keyb==MLV_KEYBOARD_ESCAPE){
      *x=(-1);
    }
    return 2;
  }
  else if(r==MLV_MOUSE_BUTTON){
    (*x)=*x/taille;
    (*y)=*y/taille;
    printf("x%d y%d\n",*x,*y);
    return 1;
  }

  return 0;
}
