typedef enum {J1,J2,J3,J4} num_joueur;

typedef struct {
  char nom[30];
  num_joueur n;
} joueur ;

typedef struct {
  char nom[30][30];    //nom du Jeu
  int nbj;          // nombre de joueurs max quand envoyé par le jeu et nb joueur réel renvoyé par module
  int ia[4];       // ia[0] nombre, ia[1,2,3]=1,2,3 niveau de chacune ia
} options;

int menufen(int nbmenu,options o);
int fenetre(int l,int h);
