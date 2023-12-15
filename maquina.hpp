#ifndef MAQ
#define MAQ
//#include <iostream>
#include <enigma.hpp>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#define NOCMD -1

enum enigmaERR
  {
    WALZE_RUEDAS_INCORRECTAS= -100,
    WALZE_RUEDAS_REPETIDAS,
    PLUG_YA_PLUG,
    UNPLUG_NO_PLUG,
    START_LETRAS_INCORRECTAS,
    RING_LETRAS_INCORRECTAS,
    UNPLUG_LETRAS_INCORRECTAS ,
    UKW_INCORRECTO
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
    SUBERUEDA,
    BAJARUEDA,
    QCODE,    
    ERRFICHERO,
    TIPOINCORRECTO,
    SINPARAMETRO
  };
class maquina
{
private:
  ENIGMA enigma;
  char Ring[5];
  char Start[5],Walze[5];
  //  char[4] wz,ring,start,zs;
  //  char[27] steck;
  int tipo;

public:
  maquina();
  ~maquina();
  void WalzeCfg(char *wlz);
  void  config(int tp, char *wlz, char *r, char *k, char *st);
  int command(int cmd,char *param);
  int loop();
  int plug(char *param);
  int unplug(char *param);
  int setwalze(char *param);
  int setring(char *param);
  int setstart(char *param);
  //  int setzusats(char *param);
  int codefile(char *param);
  int codetext(char *param);
  int setukw(char *param);
  int maqerr(int err);
  int mueverueda(int cmd,char *param);
  int traducecom(char *comando,char *param);
  int quickcode(char *param);
  int cambiamaq(char *param);
};

int extrae(char *a,char *b);
int letra(char c,int num);
#endif
