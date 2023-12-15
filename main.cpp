#include <maquina.hpp>
#include <stdio.h>




void Ayuda();

int main(int argc, char **argv)
{
#ifdef ENIGMAVERSION
  fprintf(stdout,"Enigma M4 / K\nVers/commit: %s\n",ENIGMAVERSION);
  fprintf(stdout,"%s\n",__DATE__);
#endif

  maquina EnigmaK;
  EnigmaK.loop();

  return(0);

}

