#ifndef RDAS
#define RDAS
// Enigma A/K


#define WIRE_D 1
#define WIRE_F 2
#define WIRE_COMERCIAL 3
#define WIRE_SWISS 4
#define WIRE_M4 0

#define NWALZE_K 3

#define ETW_K "JWULCMNOHPQZYXIRADKEGVBTSF" 
//QWERTZUIOASDFGHJKPYXCVBNML"

#define TO_I_K "Y"
#define WI_KS "PEZUOHXSCVFMTBGLRINQJWAYDK" 
#define WI_KC "LPGSZMHAEOQKVXRFYBUTNICJDW"
#define WI_KD "CIAHFQOYBXNUWJLVGEMSZKPDTR"
#define WI_KF "HFOTWPDURMCGXJLQEIVZSKBNAY"

#define TO_II_K "E"
#define WII_KS "ZOUESYDKFWPCIQXHMVBLGNJRAT"
#define WII_KC "SLVGBTFXJQOHEWIRZYAMKPCNDU"
#define WII_KD "KEDXVBSQHNCZTRUFLOAYWIPMJG"
#define WII_KF "MUHTASIPJYNCVKLOXFDZEGQBWR"


#define TO_III_K "N"
#define WIII_KS "EHRVXGAOBQUSIMZFLYNWKTPDJC"
#define WIII_KC "CJGDPSHKTURAWZXFMYNQOBVLIE"
#define WIII_KD "NUJPHWFMGDOBAVZQTXECLKYSIR"
#define WIII_KF "DKWOJVUNGLFTZCSYIBEARHXQPM"


#define UKW_K "IMETCGFRAYSQBZXWLHKDVUPOJN"


//Enigma M4
#define NWALZE_M4 8

#define UNPLUG "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define ETW_M4 "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

#define TO_I_M4 "Q"
#define WI_M4  "EKMFLGDQVZNTOWYHXUSPAIBRCJ"
#define TO_II_M4 "E"
#define WII_M4 "AJDKSIRUXBLHWTMCQGZNPYFVOE"
#define TO_III_M4 "V"
#define WIII_M4 "BDFHJLCPRTXVZNYEIWGAKMUSQO"
#define TO_IV_M4 "J"
#define WIV_M4  "ESOVPZJAYQUIRHXLNFTGKDCMWB"
#define TO_V_M4 "Z"
#define WV_M4   "VZBRGITYUPSDNHLXAWMJQOFECK"
#define TO_VI_M4 "ZM"
#define WVI_M4  "JPGVOUMFYQBENHZRDKASXLICTW"
#define TO_VII_M4 "ZM"
#define WVII_M4 "NZJHGRCXMYSWBOUFAIVLPEKQDT" 
#define TO_VIII_M4 "ZM"
#define WVIII_M4 "FKQHTLXOCBJSPDZRAMEWNIUYGV"  

#define BETA_M4 "LEYJVCNIXWPBQMDRTAKZGFUHOS"
#define GAMMA_M4 "FSOKANUERHMBTIYCWLQPZXVGJD"

#define UKWB_M4    "ENKQAUYWJICOPBLMDXZVFTHRGS"
#define UKWC_M4    "RDOBJNTKVEHMLFCWZAXGYIPSUQ"

#define FWD 1
#define BACK 0

#define NOID "NO ID"
class RUEDA 
{
public:
  char ID[15];
private:
  char pos;
  char Ring;
  char TO[27];
  int NTO;
  char Wiring[27];
  char BWiring[27];
public:
  RUEDA();
  int avanza();
  int doblestep();
  int IsTO(char t);
  char getRing();
  char getKey();
  void setRing(char c);
  void setKey(char c);
  void setWire(char *wr);
  void setTO(char *to);
  void setID(char *tx);
  int code(int i,int dir);
  void PrintW();

};


#endif
