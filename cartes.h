typedef struct {
  int valeur;
  char ens[20];         // enseigne (couleur) ou permet de différencier cartes
} carte;

typedef struct {
  carte c[400];
  int n;           // taille réelle paquet
} paquet;


paquet creer_paquet(int nbca,int nbens,char lcens[30][5],int nbcaens,char cspe[],int nbspe);
