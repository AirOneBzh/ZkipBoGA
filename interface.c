
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
  if(c<-1 || c>162){
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
  else{
    MLV_draw_filled_rectangle(x*taille,y*taille,taille,taille,MLV_rgba(34,76,16,255));
    MLV_draw_rectangle(x*taille,y*taille,taille,taille,MLV_rgba(13,53,16,255));
  }
  return 1;
}

// affiche la carte du dessus d'une zone

void aff_joueur(paquet p,joueur j){
  int i;
  aff_carte(p,160,16,8);
  for(i=6;i<15;i+=2){
    aff_carte(p,j.main[(i-4)/2],i,10);
    aff_carte(p,j.defausse[(i-4)/2][1],i-1,8);
  }
  MLV_actualise_window();
}

void aff_adv(paquet p,joueur j,int pos){
  int i;
  aff_carte(p,j.tas[1],4,2);
  for(i=6;i<15;i+=2){
    aff_carte(p,j.main[(i-4)/2],i,0);             //main
    aff_carte(p,j.defausse[(i-4)/2][1],i+1,2);   //defausse
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
coord wait_inter(int taille){
  MLV_Keyboard_button keyb;
  MLV_Keyboard_modifier keym;
  int r,u;
  coord c;
  r=MLV_wait_keyboard_or_mouse(&keyb,&keym,&u,&c.x,&c.y);
  if(r==MLV_KEY){
    c.x=-1;
    c.y=-1;
    if(keyb==MLV_KEYBOARD_ESCAPE){
      c.y=0;
    }
    if(keyb==MLV_KEYBOARD_s){
      c.y=1;
    }
    if(keyb==MLV_KEYBOARD_q){
      c.y=2;
    }
    if(keyb==MLV_KEYBOARD_f){
      c.y=3;
    }
    return c;
  }
  else if(r==MLV_MOUSE_BUTTON){
    c.x=c.x/taille;
    c.y=c.y/taille;
    return c;
  }

  return c;
}

coord conv_to_menu(coord c){
  coord r;
  int tailleh = MLV_get_desktop_height()*0.65;
  int carre = tailleh /10;
  if(c.x>46 && c.x<8.5*carre){
    if(c.y>232 && c.y<232+carre){
      //if(c.x>)
      r.x=1;
      r.y=0;
      return r;
    }
      r.x=1;
      r.y=0;
      return r;
    }
    if(c.y>232 && c.y<232+carre){
      r.x=1;
      r.y=0;
      return r;
    }
    if(c.y>232 && c.y<232+carre){
      r.x=1;
      r.y=0;
      return r;
    }
    if(c.y>232 && c.y<232+carre){
      r.x=1;
      r.y=0;
      return r;
    }
  }
  return r;
}
