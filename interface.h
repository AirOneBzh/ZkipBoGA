typedef struct{
  int x;
  int y;
} coord;



void aff_joueur(paquet p,joueur j);
void aff_milieu(paquet p,milieu m);
void aff_adv(paquet p,joueur j,int pos);
coord wait_inter(int taille);
coord conv_to_menu(coord c);
void reset_fen();
int aff_carte(paquet p,int c,int x,int y);
