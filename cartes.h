
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
void mel_pioche(int p[]);
void aj_carte(int p[],int c);
int ret_carte(int p[]);
int ret_carte_n(int p[],int n);
int ret_carte_m(int p[],int n);
void tri_carte(paquet p,int c[]);
void aj_carte_m(int p[],int c,int n);
void echanger_cartes(int p[],int r,int m);
