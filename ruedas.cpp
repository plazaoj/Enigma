#include "ruedas.hpp"
#include <stdio.h>
#include <string.h>

// Constructor de clase. Hace falta configurar después las ruedas
RUEDA::RUEDA()
{
  setID(NOID);
  setWire(UNPLUG);
  setRing('A');
  setKey('A');
  NTO=0;
  return;
}

// Avanza una posición. Retorna 1 si pasa por una letra de TurnOver
int RUEDA::avanza()
{
  int av=0,i;

  i=0;
  if(NTO!=0)
    {
      do
	{
	  if(TO[i]==pos)
	    av=1;
	  i++;
	}while((av==0)&&(i<NTO));
    }
  pos++;
  if(pos>'Z')
    {
      pos='A';
    }
  return(av);
}
// Comprueba si debe hacer el doble paso
int RUEDA::IsTO(char t)
{
  int i,flag=0;
  i=0;
  if(NTO>0)
    {
      do{
	if(TO[i]==t)
	  flag=1;
	i++;
      }while((flag==0)&&(i<NTO));
    }
  return(flag);


}

int RUEDA::doblestep()
{
  int av=0,i;

  i=0;
  if(NTO>0)
    {
      do{
	if(TO[i]==pos)
	  av=1;
	i++;
      }while((av==0)&&(i<NTO));
    }

  return(av);


}
// Retorna la posición del anillo actual
char RUEDA::getRing()
{
  return(Ring);
}
// Retorna la posición de la letra actual
char RUEDA::getKey()
{
  return(pos);
}

// configura el ringstellung 
void RUEDA::setRing(char c)
{

  Ring=c;
  return;

}

// configura la posición de la rueda
void RUEDA::setKey(char c)
{
  pos=c;
  return;
}

// COnfigura las conexiones de la rueda
void RUEDA::setWire(char *wr)
{
  int i;
  strcpy(Wiring,wr);
  for(i=0;i<26;i++)
    BWiring[Wiring[i]-'A']='A'+i;

  return;

}

void RUEDA::setTO(char *to)
{
  if(to!=NULL)
    {
      strcpy(TO,to);
      NTO=strlen(TO);
    }
  else
    NTO=0;

  return;

}

void RUEDA::setID(char *tx)
{
  strcpy(ID,tx);
  return;
}

int RUEDA::code(int i,int dir)
{
  int o;
  int ps;
  if (dir==FWD)
    {
      ps=i+(pos-Ring);
      //      fprintf(stderr,"**%i",ps);
      if(ps>25) ps-=26;
      if(ps<0) ps+=26;
      //      fprintf(stderr,"**%i\n",ps);
      o=(Wiring[ps]-'A')-(pos-Ring);
      if(o>25) o-=26;
      else if(o<0) o+=26;
    }
  else
    {
      ps=i+(pos-Ring);
      if(ps<0) ps+=26;
      else if(ps>25) ps-=26;
      o=(BWiring[ps]-'A')-(pos-Ring);
      if(o>25) o-=26;
      else if(o<0) o+=26;
    }

  return(o);
}

void RUEDA::PrintW()
{
  fprintf(stdout,"%s-%s\n",ID,Wiring);
  return;

}
