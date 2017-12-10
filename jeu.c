/// module jeu
// permet de créer un menu un lecteur de manuel selectionner nb joueurs


#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "jeu.h"
#include "interface.h"

// menuc nombre d'entrees, menuv titre menu
int menufen(int nbmenu,options o){
  int c,x,y;
  char menu[8][30];
  int taille;
  taille=(MLV_get_desktop_height()*0.65)/10;
  MLV_create_window("Menu","Menu",((1.4*nbmenu)+2)*taille,10*taille);
  MLV_Image* header = MLV_load_image("assets/header.png");
  MLV_resize_image(header,100,100);
  MLV_Color fond = MLV_rgba(40,40,40,255);
  MLV_Font* font=MLV_load_font("assets/pricedown.ttf",0.65*taille);
  sprintf(menu[0],"Lancer %s",o.nom);
  sprintf(menu[1],"Règles");
  sprintf(menu[2],"Options");
  sprintf(menu[3],"Bots");
  sprintf(menu[4],"Quitter");
  nbmenu=5;
  MLV_change_window_size((1.4*nbmenu+2)*taille,10*taille);
  MLV_actualise_window();
  o.nbj=2;
  MLV_clear_window(fond);
  MLV_draw_image(header,0.2*taille,0.1*taille);
  MLV_draw_text_with_font(1.6*taille,0.2*taille,o.nom,font,MLV_COLOR_WHITE);
  for(c=0;c<nbmenu;c++){
    MLV_draw_filled_rectangle(0.6*taille,(2+1.5*c)*taille,7.8*taille,taille,MLV_COLOR_WHITE);
    MLV_draw_text_with_font(taille*1.1,(2+1.5*c)*taille,menu[c],font,fond);
  }

  MLV_actualise_window();
  while(1){
    wait_inter(&x,&y);
    printf("x%d y%d\n",x,y);
    if(y<2 || y>5){
      MLV_free_window();
      return 0;
    }
    if(y==2){
      MLV_free_window();
      return 1;
    }
    if(y==3){
      printf("README");
    }
  }
  MLV_free_window();
  return 0;

}

int fenetre (int l,int h){
  MLV_create_window("ZkipBoGA","ZkipBoGA",l,h);

  MLV_actualise_window();

  return 1;
} // h hauteur , l largeur
