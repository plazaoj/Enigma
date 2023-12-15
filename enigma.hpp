#ifndef ENGMA
#define ENGMA
#include "ruedas.hpp"

#define UNPLUG "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

enum TipoMaq
  {
    M4=0,
    KD,
    KF,
    KC,
    KS,
  };


class ENIGMA
{
private:
  char key0[5];
  int NWalze; // numero de ruedas 6 para M4, 5 para K
  int Nmax;
  char Steck[27];
  int IsSteck[26];
  int tipo; // Tipo de maquina KD, KF, KC, M4
  char RID[8][3];
  char ZID[2][3];
  char UID[2][2][3];
  char Entritt[2][27];
  char RWires[5][8][27];
  char RZusatz[2][27];
  char Ukw[2][2][27];
  char TO[2][8][27];

 
public:

  char Ring[5];
  char Key[5];
  char Walze[6];
  char UKW[2];
  RUEDA EWalze[6];
  
   ENIGMA();
  char Code(char cin);
  void Modelo(int md);
  int setRing(char *Ring);
  int setKey(char *Key);
  int setWalze(char *Wz);
  int setUkw(char *ukw);
  int Plug(char *plug);
  int UnPlug(char c1, char c2);
  void PrintConfig();
  void getRing();
  void getKey();
  void getWalze();
  int Plug2(char c1,char c2);
  int PrintModelo();
  void Reset();
};

#endif
