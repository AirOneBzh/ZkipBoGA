/// module jeu
// permet de créer un menu un lecteur de manuel selectionner nb joueurs


#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "jeu.h"

// menuc nombre d'entrees, menuv titre menu
int menufen(int nbmenu,options o){
  int c,x,y;
  char titre[30];
  MLV_create_window("Menu","Menu",800,900);

  MLV_Image* header = MLV_load_image("assets/header.png");
  MLV_resize_image(header,100,100);
  MLV_Color fond = MLV_rgba(40,40,40,255);
  MLV_Font* font=MLV_load_font("assets/pricedown.ttf",60);
  MLV_Font* devil60=MLV_load_font("assets/Devil Breeze Bold.ttf",60);
  MLV_Font* devil80=MLV_load_font("assets/Devil Breeze Bold.ttf",90);
  sprintf(titre,"%s",o.nom[0]);
  sprintf(o.nom[0],"Lancer %s",titre);
  sprintf(o.nom[nbmenu],"Options");
  sprintf(o.nom[nbmenu+1],"Bots");
  nbmenu+=2;
  MLV_clear_window(fond);
  MLV_draw_image(header,30,15);
  MLV_draw_text_with_font(150,15,titre,font,MLV_COLOR_WHITE);
  MLV_draw_text_with_font(500,15,"ZNG",devil60,MLV_COLOR_RED);          // T. ZANGA :)
  MLV_draw_text_with_font(640,10,"c",devil80,MLV_COLOR_DARKGREEN);      // Cesarus
  MLV_draw_text_with_font(683,10,"a",devil80,MLV_COLOR_BLUE);           // AirOne
  for(c=0;c<nbmenu;c++){
    MLV_draw_filled_rectangle(40,140+100*c,720,80,MLV_COLOR_WHITE);
    MLV_draw_text_with_font(80,140+100*c,o.nom[c],font,fond);
  }

  MLV_actualise_window();
  while(x<40 || y<240 || x>760 || y>320){
    MLV_wait_mouse(&x,&y);
    printf("x%d y%d\n",x,y);
    if(x>40 && y>240 && x<760 && y<320){
      system("less README.md");
    }
  }
  MLV_free_window();
  return 1;

}

int fenetre (int l,int h){
  MLV_create_window("ZkipBoGA","ZkipBoGA",l,h);

  MLV_actualise_window();
  MLV_wait_seconds(10);
  MLV_free_window();
  return 1;
} // h hauteur , l largeur
