#ifndef MAQ
#define MAQ
//#include <iostream>
#include <enigma.hpp>
#include <stdio.h>
#include <string.h>
#include <string>
#include <map>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#define NOCMD -1

enum enigmaERR
  {
    RUEDAS_INCORRECTAS= -100,
    RUEDAS_REPETIDAS,
    PLUG_YA_PLUG,
    UNPLUG_NO_PLUG,
    START_LETRAS_INCORRECTAS,
    RING_LETRAS_INCORRECTAS,
    UNPLUG_LETRAS_INCORRECTAS ,
    UKW_INCORRECTO,
    SINPARAMETRO
  };

enum EnigmaCMD
  {
    QUIT=99,
    SETWALZE,
    SETRINGS,
    SETSTART,
    PLUGSTEK,
    UNPLUGST,
    CODEFILE,
    CODETEXT, 
    RESETSTA,
    CAMBIAMAQ,
    SETUKW, 
    QCODE,    
    ERRFICHERO,
    TIPOINCORRECTO,
    LISTACMD
  };
class maquina
{
private:
  ENIGMA enigma;
  char Ring[5];
  char Start[5],Walze[5];
  int tipo;
  std::map<std::string,int> command_map;
  
public:
  maquina();
  ~maquina();
  void WalzeCfg(char *wlz);
  void config(int tp, char *wlz, char *r, char *k, char *st);
  int command(int cmd,std::string param);
  int loop();
  int plug(std::string param);
  int unplug(std::string param);
  int setwalze(std::string param);
  int setring(std::string param);
  int setstart(std::string param);
  int codefile(std::string param);
  int codetext(std::string param);
  int setukw(std::string param);
  int traducecom(char *comando,std::string &param);
  int quickcode(std::string param);
  int cambiamaq(std::string param);
  int maqerr(int err);
private:
  void Ayuda();
};

#endif
