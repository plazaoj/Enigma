#include "enigma.hpp"
#include <stdio.h>
#include <string.h>

ENIGMA::ENIGMA()
{

  tipo=KC; // Por defecto, la M4.
  strcpy(Entritt[0],ETW_M4);
  strcpy(Entritt[1],ETW_K);

  strcpy(RWires[0][0],WI_M4);
  strcpy(RWires[0][1],WII_M4);
  strcpy(RWires[0][2],WIII_M4);
  strcpy(RWires[0][3],WIV_M4);
  strcpy(RWires[0][4],WV_M4);
  strcpy(RWires[0][5],WVI_M4);
  strcpy(RWires[0][6],WVII_M4);
  strcpy(RWires[0][7],WVIII_M4);

  strcpy(TO[0][0],TO_I_M4);
  strcpy(TO[0][1],TO_II_M4);
  strcpy(TO[0][2],TO_III_M4);
  strcpy(TO[0][3],TO_IV_M4);
  strcpy(TO[0][4],TO_V_M4);
  strcpy(TO[0][5],TO_VI_M4);
  strcpy(TO[0][6],TO_VII_M4);
  strcpy(TO[0][7],TO_VIII_M4);

  strcpy(RWires[1][0],WI_KD);
  strcpy(RWires[1][1],WII_KD);
  strcpy(RWires[1][2],WIII_KD);

  strcpy(RWires[2][0],WI_KF);
  strcpy(RWires[2][1],WII_KF);
  strcpy(RWires[2][2],WIII_KF);

  strcpy(RWires[3][0],WI_KC);
  strcpy(RWires[3][1],WII_KC);
  strcpy(RWires[3][2],WIII_KC);

  strcpy(RWires[4][0],WI_KS);
  strcpy(RWires[4][1],WII_KS);
  strcpy(RWires[4][2],WIII_KS);

  strcpy(TO[1][0],TO_I_K);
  strcpy(TO[1][1],TO_II_K);
  strcpy(TO[1][2],TO_III_K);

  strcpy(RZusatz[0],BETA_M4);
  strcpy(RZusatz[1],GAMMA_M4);

  strcpy(Ukw[0][0],UKWB_M4);
  strcpy(Ukw[0][1],UKWC_M4);

  strcpy(Ukw[1][0],UKW_K);

  for(int i=0;i<8;i++)
    {
      RID[i][0]=i+'1';
      RID[i][1]=0;
    }
  strcpy(ZID[0],"B");
  strcpy(ZID[1],"G");

  strcpy(UID[0][0],"B");
  strcpy(UID[0][1],"C");

  strcpy(UID[1][0],"0");

  Modelo(tipo);
  UnPlug(0,0);

  return;

}
char ENIGMA::Code(char ci)
{
  int i;
  char pout,pin;
  // Avanzar
  pout='-'-'A';


  if((ci>='a')&&(ci<='z'))
    ci+='A'-'a';
  
  if(((ci>='A')&&(ci<='Z'))||(ci=='-'))
    {

      if(EWalze[1].avanza())
	{
	  if(EWalze[2].avanza())
	    EWalze[3].avanza();
	}
      else if (EWalze[2].doblestep())
	{
	  EWalze[2].avanza();
	  EWalze[3].avanza();
	}

      if(ci=='-') return('-');

      pin=Steck[ci-'A']-'A';
 
      for(i=0;i<NWalze-1;i++)
	{
	  pin=EWalze[i].code(pin,FWD);
	}
      
      pout=EWalze[NWalze-1].code(pin,FWD);
      
      for(i=NWalze-2;i>=0;i--)
	{
	  pout=EWalze[i].code(pout,BACK);
	}
      
      pout=Steck[(int)pout];
    }
  return(pout);
}

void ENIGMA::Modelo(int md)
{
  
  tipo=md;
  if(tipo)
    {
      // Enigma K
      UnPlug(0,0);
      NWalze=5;
      Nmax=3;
      EWalze[0].setWire(Entritt[1]);
      EWalze[0].setID("ETW");
      EWalze[4].setWire(Ukw[1][0]);
      EWalze[4].setID(UID[1][0]);
      setWalze("123");
      setRing("AAAA");
      setKey("AAAA");
    }
  else
    {
      // Enigma M4
      UnPlug(0,0);
      NWalze=6;
      Nmax=8;
      EWalze[0].setWire(Entritt[0]);
      EWalze[0].setID("ETW");
      EWalze[5].setWire(Ukw[0][0]);
      EWalze[5].setID(UID[0][0]);
      EWalze[5].setRing('A');
      EWalze[5].setKey('A');
      setWalze("B123");
      setRing("AAAA");
      setKey("AAAA");
    }
  return;
}
int ENIGMA::setRing(const char *ring)
{

  int i;
  
  for(i=0;i<4;i++)
    {
      if((ring[i]>='A')&&(ring[i]<='Z'))
	{
	  EWalze[4-i].setRing(ring[i]);
	  Ring[i]=ring[i];
	}
      else
	return(1);
    }
  Ring[4]=0;
  return(0);

}
int ENIGMA::setKey(const char *key)
{

  int i;
  strcpy(key0,key);  
  for(i=0;i<4;i++)
    {
      if((key[i]>='A')&&(key[i]<='Z'))
	{
	  EWalze[4-i].setKey(key[i]);
	  Key[i]=key[i];
	}
      else
	return(1);
    }
  Key[4]=0;

  return(0);

}
int ENIGMA::setWalze(const char *Wz)
{
  int i;

  if(tipo)
    {
      if((Wz[0]!=Wz[1])&&(Wz[1]!=Wz[2])&&(Wz[0]!=Wz[2]))
	{
	  for(i=0;i<=2;i++)
	    {
	      if((Wz[i]-'0'>0)&&(Wz[i]-'0'<=Nmax))
		{
		  EWalze[3-i].setWire(RWires[tipo][Wz[i]-'1']);
		  EWalze[3-i].setTO(TO[1][Wz[i]-'1']);
		  EWalze[3-i].setID(RID[Wz[i]-'1']);
		  Walze[i]=Wz[i];
		}
	      else 
		return(1);
	    }
	}
      else 
	return(1);
    }
  else
    {
      if((Wz[1]!=Wz[2])&&(Wz[1]!=Wz[3])&&(Wz[3]!=Wz[2]))
	{
	  for(i=1;i<=3;i++)
	    {
	      if((Wz[i]-'0'>0)&&(Wz[i]-'0'<=Nmax))
		{
		  EWalze[4-i].setWire(RWires[0][Wz[i]-'1']);
		  EWalze[4-i].setTO(TO[0][Wz[i]-'1']);
		  EWalze[4-i].setID(RID[Wz[i]-'1']);
		  Walze[i]=Wz[i];
		}
	      else 
		return(1);
	    }
	  switch(Wz[0])
	    {
	    case 'B':
	      {
		EWalze[4].setWire(RZusatz[0]);
		EWalze[4].setID(ZID[0]);
		break;
	      }
	    case 'G':
	      {
		EWalze[4].setWire(RZusatz[1]);
		EWalze[4].setID(ZID[1]);
		break;
	      }
	    default:
	      return(1);
	    }
	  Walze[0]=Wz[0];
	}
      else 
	return(1);
    }
  return(0);

}
int ENIGMA::setUkw(const char *ukw)
{
  

  if(tipo)
    return(0);

  if(ukw[0]=='C')
    {
      EWalze[5].setWire(Ukw[0][1]);
      EWalze[5].setID(UID[0][1]);
    }
  else
    {
      EWalze[5].setWire(Ukw[0][0]);
      EWalze[5].setID(UID[0][0]);
    }

  return(0);

}

int ENIGMA::Plug(const char *plug)
{
  int plen,i,flag=0;
  if(!plug) return(0);
  
  plen=strlen(plug);
  if((plen%2)!=0)
    plen--;

  i=0;
  do
    {
      flag=Plug2(plug[i],plug[i+1]);
      i+=2;
    }while((flag)&&(i<plen));
  return(flag);
}
int ENIGMA::UnPlug(char c1,char c2)
{
  int i;
  if((c1<'A')||(c2<'A'))
    {
      strcpy(Steck,UNPLUG);
      for(i=0;i<26;i++) IsSteck[i]=0;
      return(0);
    }
  if((c1<='Z')&&(c2<='Z'))
    {
      if(Steck[c1-'A']!=c2)
	return(1);
      Steck[c1-'A']=c1;
      Steck[c1-'A']=c2;
      IsSteck[c1-'A']=0;
      IsSteck[c2-'A']=0;
    }
  return(0);

}
int ENIGMA::Plug2(char c1,char c2)
{

  if(c1==c2) return(0);
  
  if((IsSteck[c1-'A']!=0)||(IsSteck[c2-'A']))
    return(0);

  Steck[c1-'A']=c2;
  Steck[c2-'A']=c1;
  IsSteck[c1-'A']=1;
  IsSteck[c2-'A']=1;

  return(1);
}
void ENIGMA::PrintConfig()
{
  int i;
  getRing();
  getKey();
  getWalze();
  PrintModelo();
  fprintf(stdout,"%s[%s]%s ",Walze,Ring,Key);
  for(i=0;i<26;i++)
    {
      if((IsSteck[i])&&(Steck[i]>'A'+i))
	fprintf(stdout,"%c%c ",'A'+i,Steck[i]);
    }
  fprintf(stdout,"\n");
  //  for(int i=0;i<NWalze;i++)
  //   EWalze[i].PrintW();
  return;

}
void ENIGMA::getRing()
{
  for(int i=0;i<4;i++)
    Ring[i]=EWalze[4-i].getRing();
  return;

}
void ENIGMA::getKey()
{
  for(int i=0;i<4;i++)
    Key[i]=EWalze[4-i].getKey();
  return;

}

void ENIGMA::getWalze()
{
  if(tipo)
    {
      for(int i=0;i<4;i++)
	Walze[i]=EWalze[4-i].ID[0];
      Walze[4]=0;
    }
  else
    {
      for(int i=0;i<5;i++)
	Walze[i]=EWalze[5-i].ID[0];
      Walze[5]=0;
    }

  return;
}
void ENIGMA::Reset()
{
  setKey(key0);
  return;
}
int ENIGMA::PrintModelo()
{
  switch(tipo)
    {
    case M4:
      {
	fprintf(stdout,"Enigma M4\n");
	break;
      }
    case KC:
      {
	fprintf(stdout,"Enigma K(Comercial)\n");
	break;
      }

    case KD:
      {
	fprintf(stdout,"Enigma K(D)\n");
	break;
      }

    case KF:
      {
	fprintf(stdout,"Enigma K(F)\n");
	break;
      }

    case KS:
      {
	fprintf(stdout,"Enigma K(Suiza)\n");
	break;
      }

    }
  return(tipo);

}
