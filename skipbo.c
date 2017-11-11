//// programme lancement du jeu de SkipBo

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "jeu.h"

int main(int argc,char **argv){
  options o;
  sprintf(o.nom[0],"ZkipBoGA");
  menufen(2,o);
  return 1;
}
