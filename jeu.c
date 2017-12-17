/// module jeu
// permet de créer un menu un lecteur de manuel selectionner nb joueurs


#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "jeu.h"
#include "save.h"
#include "interface.h"

void bouton(char *nom,int x){
  int carre = MLV_get_window_height()/10;

  MLV_Color fond = MLV_rgba(40,40,40,255);            // variables à changer pour les couleurs du menu
  MLV_Color text = MLV_COLOR_WHITE;
  MLV_Font* font=MLV_load_font("assets/pricedown.ttf",0.65*carre);
  MLV_draw_filled_rectangle(0.5*carre,(1+1.5*x)*carre,8.5*carre,carre,text);
  MLV_draw_text_with_font(carre,(1+1.5*x)*carre,nom,font,fond);
}

void sous_bouton(char *nom,int x,int y,int n,int sel){   // x pour quel bouton vertical y combien sur les boutons horiz et combien boutons horiz total
  int carre = MLV_get_window_height()/10;
  int bx,by; //coords des coins NO des boutons
  bx = 5*carre+(4*(y-1)*carre)/n;
  by=(1.1+1.5*x)*carre;
  MLV_Color fond;          // variables à changer pour les couleurs du menu
  MLV_Color text = MLV_COLOR_WHITE;
  printf("sel %d\n",sel);
  if(sel==-1){
    fond = MLV_COLOR_DARK_RED;
  }
  else {
    if(sel>0){
      fond = MLV_COLOR_DARK_GREEN;
    }
    else{
      fond = MLV_rgba(40,40,40,255);
    }
  }

  MLV_Font* font=MLV_load_font("assets/pricedown.ttf",0.3*carre);    //max 9 caractère
  MLV_draw_text_box_with_font(bx,by,(4*0.8*carre)/n,0.8*carre,nom,font,0.7,text,text,fond,MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER,MLV_VERTICAL_CENTER);
}

void insert_nom(char *nom){
  int th=MLV_get_window_height();
  int tw=MLV_get_window_width();
  MLV_wait_input_box(
    tw*0.3,th*0.45,
    tw*0.4,th*0.1,
    MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,
    "Votre nom : ",
    &nom
  );
}

void aff_menu(char *nom,int carre,options o){

  MLV_Image* header = MLV_load_image("assets/header.png");
  MLV_resize_image(header,9.5*carre,carre);

  MLV_Color fond = MLV_rgba(40,40,40,255);        // variables à changer pour les couleurs du menu
  //MLV_Font* font=MLV_load_font("assets/pricedown.ttf",0.65*carre);

  MLV_clear_window(fond);
  MLV_draw_image(header,0.2*carre,0.1*carre);
  //Lancer jeu charger partie
  bouton(nom,1);
  sous_bouton("Charger",1,1,2,0);
  sous_bouton("Stats",1,2,2,0);
  // Règles
  bouton("Règles",2);
  sous_bouton("PDF",2,1,2,0);
  sous_bouton("HTML",2,2,2,0);
  // Joueurs et bots
  bouton("Joueurs",3);

  sous_bouton("Nom",3,1,3,0);
  sous_bouton("Jo / IA",3,2,3,1);
  sous_bouton("Niv IA",3,3,3,0);

  //Affichage
  bouton("Options",4);
  sous_bouton("95",4,1,3,0);
  sous_bouton("Son",4,2,3,o.son);
  sous_bouton("Pl.Ec.",4,3,3,o.full);
  //quitter
  bouton("Quitter",5);
  sous_bouton("Autres jeux",5,1,1,0);
}

// menuc nombre d'entrees, menuv titre menu
int menufen(char *nom,options *o){
  coord c;
  char tmp[3],jba[3];
  int tailleh = MLV_get_desktop_height()*0.65;
  int carre = tailleh /10,i,jbn=4;
  printf("taille h %d \n",tailleh);
  MLV_create_window("Menu","Menu",((1.5*5)+2)*carre,tailleh);
  o->pourc=95;
  o->full=-1;
  o->son=1;
  for(i=0;i<4;i++){
      sprintf(o->nom[i],"J%d",i);
  }
  o->ia[0]=0;
  o->ia[1]=1;
  o->ia[2]=-1;
  o->ia[3]=-1;
  aff_menu(nom,carre,*o);

  coord r;
  MLV_actualise_window();
  while(1){
    c=wait_inter(1);
    printf("x%d y%d\n",c.x,c.y);
    if(c.x>-1){
      r=conv_to_menu(c);
      printf("x%d y%d\n",r.x,r.y);
      if(r.x==1){
        if(r.y==1){
          load();
        }
        if(r.y==2){
          system("xdg-open classement.txt");
        }
        if(r.y==0){
          MLV_free_window();
          return 1;
        }

      }
      if(r.x==2){
        if(r.y==0){
          system("xdg-open README.md");
        }
        if(r.y==1){
          system("xdg-open README.pdf");

        }
        if(r.y==2){
          system("xdg-open https://aironebzh.github.io/ZkipBoGA/");
        }
      }
      //joueurs
      if(r.x==3){
        if(r.y==0){
          jbn++;
          if(jbn==5){
            jbn=0;
          }
          printf("jbn %d \n",jbn);
          bouton("Joueurs",3);
          if(jbn==4){
            sous_bouton("Nom",3,1,3,0);
            sous_bouton("Jo / IA",3,2,3,1);
            sous_bouton("Niv IA",3,3,3,0);
          }
          else{
            sprintf(jba,"%d",jbn-1);
            sous_bouton(o->nom[jbn],3,1,3,0);
            sous_bouton(jba,3,2,3,1);
            sous_bouton("Bot",3,3,3,o->ia[jbn-1]);
          }

          MLV_actualise_window();
        }
        if(r.y==1 && jbn!=4){
          insert_nom(o->nom[jbn]);
          sous_bouton(o->nom[jbn],3,1,3,0);
          MLV_actualise_window();
        }
        if(r.y==2 && jbn!=4){
          sprintf(tmp,"%d",o->ia[jbn]);
          sous_bouton(tmp,3,2,3,o->ia[jbn]);
        }
      }

      if(r.x==4 ){
        if(r.y==1){
          o->pourc-=10;
          if(o->pourc<60){
            o->pourc=95;
          }
          sprintf(tmp,"%d",o->pourc);
          printf("%s\n",tmp);
          sous_bouton(tmp,4,1,3,0);
          MLV_actualise_window();
        }
        if(r.y==2){
          o->son=-o->son;
          sous_bouton("Son",4,2,3,o->son);
          MLV_actualise_window();
        }
        if(r.y==3){
          o->full=-o->full;
          sous_bouton("Pl.Ec.",4,3,3,o->full);
          MLV_actualise_window();
        }

      }
      if(r.x==5){
        MLV_free_window();
        if(r.y==1){
          system("xdg-open https://aironebzh.github.io/");
        }
        return 0;
      }
    }
    else{
      if(c.y==2){
        MLV_free_window();
        return 0;
      }
      if(c.y==3){
        o->full=1-o->full;
        sous_bouton("F",4,3,3,o->full);
        MLV_actualise_window();
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
