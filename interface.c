
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
  if(c!=-1){
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
  char s[3];
  int carre=(MLV_get_desktop_width()*0.95)/22;
  MLV_Font* font=MLV_load_font("assets/pricedown.ttf",0.3*carre);
  aff_carte(p,j.tas[1],16,8);
  sprintf(s,"%d",j.tas[0]);
  MLV_draw_filled_rectangle(17.2*carre,7.1*carre,0.53*carre,0.53*carre,MLV_rgba(34,76,16,255));
  MLV_draw_text_with_font(17.42*carre,7.3*carre,s,font,MLV_rgba(13,53,16,255));
  for(i=0;i<5;i++){
    aff_carte(p,j.main[i+1],i*2+6,10);
    printf("def %d\n",j.defausse[i][1]);
    aff_carte(p,j.defausse[i][1],i*2+5,8);
  }
  printf("nbcamain %d %d\n",j.main[0],j.main[1]);
  MLV_actualise_window();
}

void aff_adv(paquet p,joueur j,int pos){
  int i,x;
  char s[3];
  int carre=(MLV_get_desktop_width()*0.95)/22;
  MLV_Font* font=MLV_load_font("assets/pricedown.ttf",0.3*carre);
  sprintf(s,"%d",j.tas[0]);
  MLV_draw_filled_rectangle(5.37*carre,1.39*carre,0.53*carre,0.53*carre,MLV_rgba(34,76,16,255));
  MLV_draw_text_with_font(5.43*carre,1.39*carre,s,font,MLV_rgba(13,53,16,255));

  aff_carte(p,j.tas[1],4,2);
  for(i=0;i<5;i++){
    if(j.main[i]!=-1){
      x=0;
    }
    aff_carte(p,x,i*2+6,0);             //main
    aff_carte(p,j.defausse[i][1],i*2+7,2);   //defausse
  }
  MLV_actualise_window();
}

void aff_milieu(paquet p,milieu m){
  int i;
  int carre = MLV_get_window_height()/11;
  aff_carte(p,0,15,5);
  for(i=0;i<4;i++){
    aff_carte(p,m.m[i][1],i*2+6,5);
  }
  MLV_draw_text_box(0.1*carre,carre*0.3,carre*1.3,carre*0.6,"Raccourcis (Esc)",1,MLV_COLOR_BLACK,MLV_COLOR_BLACK,MLV_COLOR_WHITE,MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER,MLV_VERTICAL_CENTER);
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
    if(keyb==MLV_KEYBOARD_f){
      c.y=3;
    }
    if(keyb==MLV_KEYBOARD_m){
      c.y=4;
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
  int tailleh = MLV_get_window_height();
  int taillew = MLV_get_window_width();
  printf("taille w %d \n",taillew);
  int carre = tailleh /10;
  if(c.x>taillew/19.2 && c.x<taillew/19.2+8.5*carre){
    if(c.y>tailleh/4.034 && c.y<tailleh/4.034+carre){
      r.x=1;
      r.y=0;
      if(c.x>taillew/1.8989 && c.x<taillew/1.44){
        r.y=1;
      }
      if(c.x>taillew/1.35 && c.x<taillew/1.1){
        r.y=2;
      }
    }
    if(c.y>tailleh/2.51 && c.y<tailleh/2.51+carre){
      r.x=2;
      r.y=0;
      if(c.x>taillew/1.8989 && c.x<taillew/1.44){
        r.y=1;
      }
      if(c.x>taillew/1.35 && c.x<taillew/1.1){
        r.y=2;
      }
    }
    if(c.y>tailleh/1.83 && c.y<tailleh/1.83+carre){
      r.x=3;
      r.y=0;
      if(c.x>taillew/1.8989 && c.x<taillew/1.44){
        r.y=1;
      }
      if(c.x>taillew/1.35 && c.x<taillew/1.1){
        r.y=2;
      }
    }
    if(c.y>tailleh/1.4377 && c.y<tailleh/1.4377+carre){
      r.x=4;
      r.y=0;
      if(c.x>taillew/1.8989 && c.x<taillew/1.5656){
        r.y=1;
      }
      if(c.x>taillew/1.5171 && c.x<taillew/1.28){
        r.y=2;
      }
      if(c.x>taillew/1.23 && c.x<taillew/1.08){
        r.y=3;
      }
    }
    if(c.y>tailleh/1.1858 && c.y<tailleh/1.1848+carre){
      r.x=5;
      r.y=0;
      if(c.x>taillew/1.8989 && c.x<taillew/1.1587){
        r.y=1;
      }
    }
  }
  return r;
}
