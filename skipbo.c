//// programme lancement du jeu de SkipBo
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "jeu.h"
#include <MLV/MLV_all.h>
#include "interface.h"
#include "time.h"
#include "extras.h"
#include "save.h"
#include <time.h>
/// éléments
// pioche
// pile milieu (4)
// pile défausse (5 par personne)
// tas principal (1 par personne)
// main
// carte sel

///// actions
// pioche
/// joue
// selection d'une carte
// sel d'une case où la poser   + det si mouv possible
// detecter etats
// etat = pile pleine> vider et mettre dans pioche; tas vide> gagnant; main vide>pioche;
// vider pile > mélanger main vide piocher
// faire une fonction de détection clic souris (renvoi int de zone de clic)
// une qui actualise les zones de clic dispo   (dans une liste)

//fonction vérif de règles
int pos_poss(paquet *p,int arr[],int c){
  printf("posposssss %d %d \n",p->r[c].val,p->r[arr[1]].val);
  if(p->r[arr[1]].val==p->r[c].val-1){ // carte successive
    return 1;
  }
  if(p->r[c].val==1 && arr[1]==-1){  // première carte
    return 1;
  }

  if(p->r[c].val==0){   // un joker
    if(arr[1]==-1){
      p->r[c].val=1;
    }
    else{
      p->r[c].val=p->r[arr[1]].val+1;
    }
    return 1;
  }
  else{
    return 0;
  }
}



void init_tas(joueur j[],milieu *m){
  int i;
  for(i=0;i<5;i++){
    init_cartes(j[0].defausse[i]);
    j[0].main[i+1]=-1;
  }
  j[0].main[0]=0;
  j[1].main[0]=0;
  init_cartes(j[0].tas);
  for(i=0;i<5;i++){
    init_cartes(j[1].defausse[i]);
    j[1].main[i+1]=-1;
  }
  for(i=0;i<4;i++){
    m->m[i][1]=-1;
    m->m[i][0]=0;
  }
  init_cartes(j[1].tas);
  for(i=1;i<163;i++){
    m->pioche[i]=i;
  }
  m->pioche[0]=162;
}

void init_zone(coord pos[][2]){
  int i;
  for(i=0;i<5;i++){
    pos[i][0].x=1;
    pos[i][0].y=i;
    pos[i][1].x=i*2+6;
    pos[i][1].y=10;

    pos[i+5][0].x=2;
    pos[i+5][0].y=i;
    pos[i+5][1].x=i*2+5;
    pos[i+5][1].y=8;
  }
  pos[10][0].x=3;
  pos[10][0].y=0;
  pos[10][1].x=16;
  pos[10][1].y=8;
  for(i=0;i<4;i++){
    pos[i+11][0].x=0;
    pos[i+11][0].y=i;
    pos[i+11][1].x=i*2+6;
    pos[i+11][1].y=5;
  }
}
//coord_dep dep   dep.d = c  dep.a = r
void bot(int ia,joueur b,milieu mil,int tasadv[],int nbj,coord *c,coord *r){

}

void echap(int *u){
  *u='a';
  MLV_Keyboard_button sym;
  MLV_Keyboard_modifier mod;
  int x=0, y=0;
  int tailleh = MLV_get_window_height();
  int taillew = MLV_get_window_width();
  MLV_draw_filled_rectangle(taillew*0.05,tailleh*0.3,taillew*0.1,tailleh*0.2,MLV_rgba(0,0,0,150));
  MLV_draw_text(140,350,"(Q)uit",MLV_COLOR_WHITE);
  MLV_draw_text(140,400,"(S)ave",MLV_COLOR_WHITE);
  MLV_draw_text(140,450,"(F)ullscreen",MLV_COLOR_WHITE);
  MLV_actualise_window();
  while(sym!=MLV_KEYBOARD_ESCAPE && *u!='q' && *u!='f' && *u!='s'){
    MLV_wait_keyboard_or_mouse(&sym, &mod, u, &x, &y);
  }
  reset_fen();
}

int main(int argc,char **argv){
  int i,carre,tour,jNfini=1,tourpasfin=1,carte,u=0;
  int distrib[]={0,0,2,25,20};
  int tasadv[4];
  srand(time(NULL));
  options o;
  coord c,oc,r,m,zones[48][2];
  m.x=-1;
  m.y=-1;
  paquet p;
  joueur j[4];
  milieu mil;
  MLV_Image* cadresel,*cadredesel,*cadreechec;

  char lcens[30][5];
  for(i=0;i<12;i++){
    sprintf(lcens[i],"%d",i+1);
  }

  o.nbj=2;  // normalement 4 mais on limite pour le début
  p=creer_paquet(162,12,lcens,12,18);
  if(menufen("ZkipBoGA",&o)==0){
    return 0;
  }
  char *nom;
  carre=(MLV_get_desktop_width()*o.pourc/100)/22;
  fenetre(carre*22,carre*11);
  int tailleh = MLV_get_window_height();
  int taillew = MLV_get_window_width();
  printf("full %d \n",o.full);
  if(o.full==1){
    MLV_enable_full_screen();
  }

  for(i=0;i<4;i++){
    if(o.ia[i]!=-1){
      strcpy(j[i].nom,o.nom[i]);
    }
    j[i].ia=o.ia[i];
  }

  cadresel=MLV_load_image("assets/CadreSel.png");
  cadredesel= MLV_load_image("assets/CadreDeSel.png");
  cadreechec= MLV_load_image("assets/CadreEchec.png");

  MLV_resize_image(cadreechec,carre*1.1,carre*1.1);
  MLV_resize_image(cadredesel,carre*1.1,carre*1.1);
  MLV_resize_image(cadresel,carre*1.1,carre*1.1);

  reset_fen();
  init_tas(j,&mil);
  init_zone(zones);
  son_mel(5);
  mel_pioche(mil.pioche);
  for(i=0;i<o.nbj;i++){
    piocher(mil.pioche,j[i].tas,distrib[o.nbj]);
  }
  for(i=0;i<o.nbj;i++){
    j[i].defausse[0][0]=0;
  }

  // au début du jeu on rempli le tas d'objectif (celui devant être vidé)

  tour=0;
  while(jNfini){
    if(tour==o.nbj){
      tour=0;
    }

    aff_milieu(p,mil);
    if(o.son==1){
      son_mel(3);
    }
    piocher(mil.pioche,j[tour].main,5);
    //tri_carte(p,j[tour].main);
    aff_joueur(p,j[0]);
    aff_adv(p,j[1],2);
    tourpasfin=1;
    if(o.son==1){
      son_you();
    }
    while(tourpasfin){

      if(j[tour].ia!=0){
        for(i=0;i<o.nbj;i++){
          tasadv[i]=j[i].tas[1];
        }
        for(i=o.nbj;i<4;i++){
          tasadv[i]=-1;
        }
        bot(j[tour].ia,j[tour],mil,tasadv,o.nbj,&c,&r);
      }
      if(j[tour].main[0]==0){
        if(o.son==1){
          son_pose();
        }

        piocher(mil.pioche,j[tour].main,5);
        aff_joueur(p,j[0]);
      }
      c=wait_inter(carre);
      printf("x %d y %d\n",c.x,c.y);
      if(c.x==0 && c.y==0){  //clic raccourcis
        printf("clic racc");
        echap(&u);
        aff_joueur(p,j[0]);
        aff_adv(p,j[1],2);
        aff_milieu(p,mil);
      }
      if(c.x==-1){
        if(c.y==0 && u==0){   //echap
          printf("echap");
          echap(&u);
          aff_joueur(p,j[0]);
          aff_adv(p,j[1],2);
          aff_milieu(p,mil);
        }
        printf("u%d %c\n",u,u);
        if(c.y==1 || u=='s'){
          MLV_wait_input_box(
            taillew*0.3,tailleh*0.45,
            taillew*0.4,tailleh*0.1,
            MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,
            "Nom de la partie : ",
            &nom
          );
          save(nom,j,mil,o);
        }
        if(c.y==2 || u=='q'){  //q
          if(nom)
          MLV_free_window();
          return 1;
        }
        if(c.y==3 || u=='f'){   //f
          if(MLV_is_full_screen()){
            MLV_disable_full_screen();
          }
          else{
            MLV_enable_full_screen();
          }
          reset_fen();
          aff_joueur(p,j[0]);
          aff_adv(p,j[1],2);
          aff_milieu(p,mil);
        }
        if(c.y==4){
          o.son=1-o.son;
        }
      }

      if(c.x!=0 && c.y!=0 && c.x!=-1){
        r.x=-1;
        r.y=-1;

        for(i=0;i<16;i++){
          if(c.x==zones[i][1].x && c.y==zones[i][1].y ){
            r=zones[i][0];

          }
        }
      }
      printf("rx %d ry %d\nmx %d my %d\n",r.x,r.y,m.x,m.y);

      if(m.x==-1){
        if(r.x>0){
          m.x=r.x;
          m.y=r.y;
          oc.x=c.x;
          oc.y=c.y;
          MLV_draw_image(cadresel,(c.x-0.05)*carre,(c.y-0.05)*carre);
          MLV_actualise_window();
          carte=-1;
        }
      }
      else{
        if(m.x==0){
          m.x=-1;
        }


        //départ
        if(r.x!=-1){

          if(m.x==tour*3+1 && r.x !=tour*3+1){
            carte=j[tour].main[m.y+1];
          }
          if(m.x==tour*3+2 && r.x!=tour*3+2){
            carte=j[tour].defausse[m.y][1];
          }

          if(m.x==(tour+1)*3 && r.x==0){
            carte=j[0].tas[1];
          }
          //////////////
          if((r.x==0 && pos_poss(&p,mil.m[r.y],carte)) || r.x!=0){
            if(m.x==tour*3+1 && r.x !=tour*3+1){
              ret_carte_n(j[tour].main,m.y+1);
              if(tour==0){
                aff_joueur(p,j[0]);
              }
              else{
                aff_adv(p,j[tour],tour+1);
              }
            }
            if(m.x==tour*3+2 && r.x!=tour*3+2 && r.x!=tour*3+1){
              ret_carte(j[tour].defausse[m.y]);
              if(tour==0){
                aff_joueur(p,j[0]);
              }
              else{
                aff_adv(p,j[tour],tour+1);
              }
            }

            if(m.x==(tour+1)*3 && r.x==0){
              ret_carte(j[0].tas);
              if(tour==0){
                aff_joueur(p,j[0]);
              }
              else{
                aff_adv(p,j[tour],tour+1);
              }
            }

            //  Arrivé
            //
            printf("carte%d\n",carte);
            if(carte!=-1 || (r.x==1 && m.x==1)){
              if(r.x==0){


                aj_carte(mil.m[r.y],carte);
                printf("ajmil %d\n",p.r[mil.m[r.y][1]].val);
                if(mil.m[r.y][0]==12){
                  retirer_paquet(&p,mil.pioche,mil.m[r.y]);
                }
                aff_milieu(p,mil);
                if(o.son==1){
                  son_pose();
                }
                m.x=-1;
                carte=-1;
              }
              printf("aarx %d aary %d\naamx %d aamy %d\n",r.x,r.y,m.x,m.y);
              if(r.x==1 && m.x==1){

                echanger_cartes(j[0].main,r.y,m.y);
                r.x=-1;
                m.x=-1;
                printf("changer cartes main");
                aff_joueur(p,j[0]);
                if(o.son==1){
                  son_pose();
                  son_pose();
                }
              }

              if(r.x==2 && m.x!=3){

                aj_carte(j[0].defausse[r.y],carte);
                aff_joueur(p,j[0]);
                m.x=-1;
                carte=-1;
                if(o.son==1){
                  son_pose();
                }
                //tour++;
                tourpasfin=0;
              }

              if(r.x==5){

                aj_carte(j[1].defausse[r.y],carte);
                aff_joueur(p,j[1]);
                if(o.son==1){
                  son_pose();
                }
                m.x=-1;
                carte=-1;
                //tour++;
                tourpasfin=0;
              }
            }
          }
          else{
            MLV_draw_image(cadreechec,(oc.x-0.05)*carre,(oc.y-0.05)*carre);
            MLV_actualise_window();
            if(o.son==1){
              son_den();
            }
          }
          carte=-1;
          r.x=-1;
          m.x=-1;

          printf("carteaprès   %d\n",carte);

        }
        else{
          m.x=-1;
        }
        MLV_draw_image(cadredesel,(oc.x-0.05)*carre,(oc.y-0.05)*carre);
        MLV_actualise_window();
      }
      if(j[tour].tas[0]==0){
        winner(j[tour].nom);
      }
    }
  }

  MLV_actualise_window();
  MLV_free_image(cadreechec);
  MLV_free_image(cadredesel);
  MLV_free_image(cadresel);
  MLV_free_window();
  MLV_free_audio();
  return 1;
}
