//// programme lancement du jeu de SkipBo
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "jeu.h"
#include <MLV/MLV_all.h>
#include "interface.h"
#include "time.h"
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
int pos_poss(paquet p,int arr[],int c){
  printf("posposssss %d %d \n",p.r[c].val,p.r[arr[1]].val);
  if(p.r[arr[1]].val==p.r[c].val-1){
    return 1;
  }
  if(p.r[c].val==1 && p.r[arr[1]].val==-1){
    return 1;
  }
  if(p.r[c].val==0){
    return 1; //possible
  }
  else{
    return 0;//impossible
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

void bot(int ia,joueur b,milieu mil,paquet p, int tasadv[],int nbj,coord *c,coord *r){
  srand(time(NULL));
  if(pos_poss(paquet p,int arr[],int c)==1){
    
  /*tas etape 1
    reagrde si peut jouer carte dans une pile au HASARD du milieu
    si OUI il joue puis -> etape1
    si NON regarde peut_jouer(defausse[i])
                  si OUI joue carte pile au HASARD -> etape 1
		  si NON regarde peut_jouer main
		         si OUI joue carte -> etape 1
			 si NON defausse au hasard de sa main dans une pile de defausse au hasard
  */	  
}

int main(int argc,char **argv){
  int i,carre,tour,jNfini=1,tourpasfin=1,carte;
  int distrib[]={0,0,30,25,20};
  int tasadv[4];
  srand(time(NULL));
  options o;
  coord c,r,m,zones[48][2];
  m.x=-1;
  m.y=-1;
  paquet p;
  joueur j[4];
  milieu mil;


  char lcens[30][5];
  for(i=0;i<12;i++){
    sprintf(lcens[i],"%d",i+1);
  }

  o.nbj=2;  // normalement 4 mais on limite pour le début
  p=creer_paquet(162,12,lcens,12,"S",18);
  if(menufen("ZkipBoGA",o)==0){
    return 0;
  }

  carre=(MLV_get_desktop_width()*0.95)/22;
  fenetre(carre*22,carre*11);
  reset_fen();
  init_tas(j,&mil);
  init_zone(zones);

  mel_pioche(mil.pioche);
  for(i=0;i<o.nbj;i++){
    piocher(mil.pioche,j[i].tas,distrib[o.nbj]);
  }
  // au début du jeu on rempli le tas d'objectif (celui devant être vidé)

  tour=0;
  while(jNfini){

    if(tour==o.nbj){
      tour=0;
    }

    piocher(mil.pioche,j[tour].main,5);
    tri_carte(p,j[tour].main);
    aff_joueur(p,j[0]);
    aff_adv(p,j[1],2);
    aff_milieu(p,mil);
    tourpasfin=1;
    while(tourpasfin){
      printf("tour %d\n",tour);
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
        piocher(mil.pioche,j[tour].main,5);
      }
      c=wait_inter(carre);
      printf("x %d y %d\n",c.x,c.y);
      if(c.x==-1){
        if(c.y==2){
          MLV_free_window();
          return 1;
        }
        if(c.y==3){
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
      printf("rx %d ry %d\n",r.x,r.y);

      if(m.x==-1){
        if(r.x>0){
          m.x=r.x;
          m.y=r.y;
        }
      }
      else{
        if(m.x==0){
          m.x=-1;
        }


        //départ
        if(r.x!=-1){
          if(m.x==tour*3+1 && r.x !=tour*3+1){
            carte=ret_carte_m(j[tour].main,m.y+1);
            printf("retmain%d\n",p.r[carte].val);
            if(tour==0){
              aff_joueur(p,j[0]);
            }
            else{
              aff_adv(p,j[tour],tour+1);
            }
          }
          if(m.x==tour*3+2 && r.x!=tour*3+2){
            carte=ret_carte(j[tour].defausse[m.y]);
            printf("retdefausse%d\n",p.r[carte].val);
            if(tour==0){
              aff_joueur(p,j[0]);
            }
            else{
              aff_adv(p,j[tour],tour+1);
            }
          }

          if(m.x==(tour+1)*3 && r.x==0){
            carte=ret_carte(j[0].tas);
            printf("rettas%d\n",p.r[carte].val);
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
          if(carte!=-1){
            if(r.x==0){
              printf("posposs %d\n",pos_poss(p,mil.m[r.y],carte));
              aj_carte(mil.m[r.y],carte);
              printf("ajmil\n");
              aff_milieu(p,mil);
              m.x=-1;
              carte=-1;
            }

            if(r.x==1 && m.x==1){
              echanger_cartes(j[0].main,r.y,m.y);
              r.x=-1;
              m.x=-1;
              printf("changer cartes main");
              aff_joueur(p,j[0]);
            }

            if(r.x==2 && m.x!=3){
              aj_carte(j[0].defausse[r.y],carte);
              aff_joueur(p,j[0]);
              m.x=-1;
              carte=-1;
              //tour++;
              tourpasfin=0;
            }

            if(r.x==5){
              aj_carte(j[1].defausse[r.y],carte);
              aff_joueur(p,j[1]);
              m.x=-1;
              carte=-1;
              //tour++;
              tourpasfin=0;
            }
            r.x=-1;
            m.x=-1;
          }
        }
      }

    }
  }

  MLV_actualise_window();
  MLV_free_window();
  return 1;
}
