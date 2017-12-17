typedef struct{
  int x;
  int y;
} coord;

typedef struct{
  coord d;
  coord a;
}coord_dep;

void aff_joueur(paquet p,joueur j);
void aff_milieu(paquet p,milieu m);
void aff_adv(paquet p,joueur j,int pos);
coord wait_inter(int taille);
coord conv_to_menu(coord c);
void reset_fen();
int aff_carte(paquet p,int c,int x,int y);
