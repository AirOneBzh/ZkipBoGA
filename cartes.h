typedef struct {
  int val;
  char ens[20];         // enseigne (couleur) ou permet de différencier cartes
} carte;

typedef struct{
  carte c[30];
  int nb;         // nombre de carte dans tas de cartes
} stock;      // stock tas de carte à écouler par le joueur (vide = victoire)

typedef struct{
  carte c[12];
  int t;
} serie;  // la serie au milieu de 1 a 12


typedef struct {
  carte c[400];
  int nb;           // taille réelle paquet
} paquet;  //pioche


paquet creer_paquet(int nbca,int nbens,char lcens[30][5],int nbcaens,char cspe[],int nbspe);
