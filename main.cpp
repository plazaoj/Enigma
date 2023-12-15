#include "maquina.hpp"
#include <stdio.h>
#include <string.h>
#include <getopt.h>


void Ayuda();

int main(int argc, char **argv)
{
#ifdef ENIGMAVERSION
  fprintf(stdout,"Enigma M4 / K\nVers/commit: %s\n",ENIGMAVERSION);
  fprintf(stdout,"%s\n",__DATE__);
#endif

  maquina EnigmaK;
  int next_opt;
  const char* const sopt="hw:r:k:u:s:t:";
  const struct option lopt[]={
    {"help",0,NULL,'h'},
    {"walzen",1,NULL,'w'},
    {"rings",1,NULL,'r'},
    {"start",1,NULL,'k'},
    {"ukw",1,NULL,'u'},
    {"stecker",1,NULL,'s'},
    {"tipo",1,NULL,'t'}
  };    
  
  do
    {
      next_opt=getopt_long(argc,argv,sopt,lopt,NULL);
      switch(next_opt)
        {
	case 't':
	  {
	    EnigmaK.cambiamaq(optarg);
	    break;
	  }
	case 'w':
          {
            EnigmaK.WalzeCfg(optarg);
            break;
          }
	case 'r':
          {
            EnigmaK.setring(optarg);
            break;
          }
	case 'k':
          {  
            EnigmaK.setstart(optarg);
            break;
          }
	case 'u':
          {
            EnigmaK.setukw(optarg);
            break;
          }
	case 's':
          {
            EnigmaK.plug(optarg);
            break;
          }
	case -1:
          {
            break;
          }
	case 'h':
	default:
          {
	    Ayuda();
            return(0);
          }
        } 
    } while(next_opt!=-1);
  

  EnigmaK.loop();

  return(0);

}


void Ayuda()
{
  fprintf(stdout,"Opciones:\n");
  fprintf(stdout,"--help,   -h               Muestra esta ayuda\n");
  fprintf(stdout,"--walzen, -w  <B123>       Selecciona ruedas. Por defecto B123.\n");
  fprintf(stdout,"--rings,  -r  <ABCD>       Selecciona configuración del anillo. or defecto AAAA)\n");
  fprintf(stdout,"--start,  -k  <ABCD>       Selecciona posición de inicio. Por defecto AAAA)\n");
  fprintf(stdout,"--ukw,    -u  <B>          Selecciona reflector (B|C). Por defecto B\n");
  fprintf(stdout,"--stecker,-s  <ABCDEF...>  Conecta Stecker (ej: A con B, C con D, etc...) Por defecto no hay pares conectados\n");
  fprintf(stdout,"--tipo,   -t  <M4|KF>      Selecciona tipo de máquina: M4 (militar) o KF (Comercial). Por defecto M4\n");

}
