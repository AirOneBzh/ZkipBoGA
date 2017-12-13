/// module jeu
// permet de créer un menu un lecteur de manuel selectionner nb joueurs


#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "jeu.h"
#include "interface.h"

void bouton(char *nom,int x){
  int carre = MLV_get_window_height()/10;

  MLV_Color fond = MLV_rgba(40,40,40,255);            // variables à changer pour les couleurs du menu
  MLV_Color text = MLV_COLOR_WHITE;
  MLV_Font* font=MLV_load_font("assets/pricedown.ttf",0.65*carre);
  printf("bout x%lf y%lf\n",0.5*carre,(1+1.5*x)*carre);
  MLV_draw_filled_rectangle(0.5*carre,(1+1.5*x)*carre,8.5*carre,carre,text);
  MLV_draw_text_with_font(carre,(1+1.5*x)*carre,nom,font,fond);
}

void sous_bouton(char *nom,int x,int y,int n,int sel){   // x pour quel bouton vertical y combien sur les boutons horiz et combien boutons horiz total
  int carre = MLV_get_window_height()/10;
  int bx,by; //coords des coins NO des boutons
  bx = 5*carre+(4*(y-1)*carre)/n;
  by=(1.1+1.5*x)*carre;
  printf("sousbout x%d a %lf y%d a %lf\n",bx,(4*0.8*carre)/n,by,0.8*carre);
  MLV_Color fond = MLV_rgba(40,40,40,255);          // variables à changer pour les couleurs du menu
  MLV_Color text = MLV_COLOR_WHITE;
  MLV_Font* font=MLV_load_font("assets/pricedown.ttf",0.3*carre);    //max 9 caractère
  MLV_draw_text_box_with_font(bx,by,(4*0.8*carre)/n,0.8*carre,nom,font,0.7,text,text,fond,MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER,MLV_VERTICAL_CENTER);
}

// menuc nombre d'entrees, menuv titre menu
int menufen(char *nom,options o){
  int i;
  coord c;
  char tmp[10];
  int tailleh = MLV_get_desktop_height()*0.65;
  int carre = tailleh /10;

  MLV_create_window("Menu","Menu",((1.5*5)+2)*carre,tailleh);

  MLV_Image* header = MLV_load_image("assets/header.png");
  MLV_resize_image(header,10*carre,carre);

  MLV_Color fond = MLV_rgba(40,40,40,255);        // variables à changer pour les couleurs du menu
  //MLV_Font* font=MLV_load_font("assets/pricedown.ttf",0.65*carre);

  MLV_clear_window(fond);
  MLV_draw_image(header,0.2*carre,0.1*carre);
  //Lancer jeu charger partie
  bouton("ZkipBoGA",1);
  sous_bouton("Charger",1,1,2,0);
  sous_bouton("Stats",1,2,2,0);
  // Règles
  bouton("Règles",2);
  sous_bouton("PDF",2,1,2,0);
  sous_bouton("HTML",2,2,2,0);
  // Joueurs et bots
  bouton("Joueurs",3);
  for(i=1;i<=o.nbj;i++){
    sprintf(tmp,"%d",i);
    sous_bouton(tmp,3,i,o.nbj,0);
  }

  //Affichage
  bouton("Affichage",4);
  sous_bouton("30",4,1,3,0);
  sous_bouton("50",4,2,3,0);
  sous_bouton("70",4,3,3,1);
  //quitter
  bouton("Quitter",5);
  sous_bouton("Autres jeux",5,1,1,0);

  MLV_Color col;
  for(i=0;i<15;i++){
    if(i%2){
      col=MLV_COLOR_BLACK;
    }
    else{
      col=MLV_COLOR_RED;
    }
    MLV_draw_filled_rectangle(i*carre,i*carre,carre,carre,col);
  }

  MLV_actualise_window();
  while(1){
    c=wait_inter(1);
    printf("x%d y%d\n",c.x,c.y);
    if(c.x==-1){
      if(c.x==-1 && c.y==2){
        MLV_free_window();
        return 0;
      }
      if(c.y==10){
        MLV_free_window();
        return 0;
      }
      if(c.y==2){
        MLV_free_window();
        return 1;
      }
      if(c.y==3){
        printf("README");
      }
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
