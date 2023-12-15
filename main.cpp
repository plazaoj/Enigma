#include "maquina.hpp"
#include <stdio.h>
#include <string.h>
#include <getopt.h>
int main(int argc, char **argv)
{
#ifdef ENIGMAVERSION
  fprintf(stdout,"Enigma K/M4 - %s\n",ENIGMAVERSION);
  fprintf(stdout,"%s\n",__DATE__);
#endif
  int i,j,m;
  maquina EnigmaK;
  int next_opt;
  const char* const sopt="hw:r:k:u:s:t:";
  const struct option lopt[]={
    {"help",0,NULL,'h'},
    {"walzen",1,NULL,'w'},
    {"ringstellung",1,NULL,'r'},
    {"spruchsschlussel",1,NULL,'k'},
    {"ukw",1,NULL,'u'},
    {"steckbrett",1,NULL,'s'},
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
	    //            Ayuda();
            return(0);
          }
        } 
    } while(next_opt!=-1);
  

  EnigmaK.loop();

  return(0);

}
