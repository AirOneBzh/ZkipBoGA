
typedef struct {
  int val;
  char ens[20];         // enseigne (couleur) ou permet de différencier cartes
} carte;

typedef carte reference[162];

typedef struct {
  reference r;
  int nb;           // taille réelle paquet
} paquet;  //pioche


paquet creer_paquet(int nbca,int nbens,char lcens[30][5],int nbcaens,char cspe[],int nbspe);
void init_cartes(int c[]);
int piocher(int pioche[],int main[],int n);
