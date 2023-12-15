#include "maquina.hpp"
maquina::maquina()
{
  tipo=M4;
  enigma.Modelo(M4);
}
void maquina::WalzeCfg(char *wlz)
{
  if(tipo==M4)
    {
      if(strlen(wlz)==4)
	{
	  enigma.setWalze(wlz);
	  strcpy(Walze,wlz);  
	}
      else if(strlen(wlz)==3)
	{
	  tipo=KC;
	  enigma.Modelo(tipo);
	  enigma.setWalze(wlz);
	  strcpy(Walze,wlz);  
	}
      else
	return;
    }
  else
    {
      if(strlen(wlz)==3)
	{
	  enigma.setWalze(wlz);
	  strcpy(Walze,wlz);  
	}
      else if(strlen(wlz)==4)
	{
	  tipo=M4;
	  enigma.Modelo(tipo);
	  enigma.setWalze(wlz);
	  strcpy(Walze,wlz);  
	}
      else
	return;
    }
}


void maquina::config(int tp, char *wlz, char *r, char *k, char *st)
{
  tipo=tp;
  enigma.Modelo(tipo);

  if(wlz)
    {
      enigma.setWalze(wlz);
      strcpy(Walze,wlz);
    }
  if(r)
    {
      enigma.setRing(r);
      strcpy(Ring,r);
    }
  
  if(k)
    {
      enigma.setKey(k);
      strcpy(Start,k);
    }
  
  if((tipo==0)&&(st!=NULL))
    enigma.Plug(st);
  
  return;
}

maquina::~maquina()
{

  return;
}
int maquina::command(int cmd,char *param)
{
  // fprintf(stderr,"cmd %i\n",cmd);
  switch(cmd)
  {
  case QCODE:
    {
      maqerr(quickcode(param));
      break;
    }
  case QUIT:
      {
	fprintf(stdout,"Saliendo...\n");
	return(1);
      }
  case SETWALZE:
      {
	maqerr(setwalze(param));
	//	enigma->Reset();
	break;
      }
  case SETRINGS:
      {
	maqerr(setring(param));
	break;
      }
  case SETSTART:
      {
	maqerr(setstart(param));
	break;
      }
  case PLUGSTEK:
      {
	plug(param);
	break;
      }
  case UNPLUGST:
      {
	unplug(param);
	break;
      }
  case CODEFILE:
      {
	maqerr(codefile(param));
	break;
      }
  case CODETEXT:
      {
	maqerr(codetext(param));
	break;
      }
  case RESETSTA:
      {
	enigma.Reset();
	break;
      }
  case M4:
    {
      maqerr(cambiamaq("M4"));
      break;
    }
  case KC:
    {
      maqerr(cambiamaq("KC"));
      break;
    }
  case KD:
    {
      maqerr(cambiamaq("KD"));
      break;
    }
  case KF:
    {
      maqerr(cambiamaq("KF"));
      break;
    }
  case KS:
   {
      maqerr(cambiamaq("KS"));
      break;
    }
  case CAMBIAMAQ:
    {
      fprintf(stdout,"%s\n",param);
      maqerr(cambiamaq(param));
      break;
    }
  case SETUKW:
    {
      maqerr(setukw(param));
      break;
    }
  case NOCMD:
    {
      fprintf(stderr,"Comando desconocido %i\n",cmd);
      break;
    }
  case SUBERUEDA:
  case BAJARUEDA:
  {
    mueverueda(cmd,param);
    break;
  }
  default:
   {
      break;
    }
  }
  return(0);
}
int maquina::traducecom(char *comando,char *param)
{


  if(extrae(comando,param))
    {
      if(comando[0]==EOF)
	return(QUIT);
      
      if ((!strcmp(comando,"quit"))||
	(!strcmp(comando,"QUIT")) ||
	  (!strcmp(comando,"salir"))||
	  (!strcmp(comando,"SALIR")))    
	return (QUIT);
      
      if((!strcmp(comando,"UKW"))||
	 (!strcmp(comando,"ukw")))
	return(SETUKW);
      
      if((!strcmp(comando,"WALZE"))||
	 (!strcmp(comando,"walze"))||
	 (!strcmp(comando,"ruedas"))||
	 (!strcmp(comando,"RUEDAS")))
	return(SETWALZE);
      
      if ((!strcmp(comando,"RING"))||
	  (!strcmp(comando,"ring")))
	return(SETRINGS);
      
      if ((!strcmp(comando,"TIPO"))||
	  (!strcmp(comando,"tipo")))
	return(CAMBIAMAQ);
      
      if((!strcmp(comando,"START"))||
	 (!strcmp(comando,"start")))
	return(SETSTART);
      
      if((!strcmp(comando,"PLUG"))||
	 (!strcmp(comando,"plug")))
	return(PLUGSTEK);
      
      if((!strcmp(comando,"M4"))||
	 (!strcmp(comando,"m4")))
	return(M4);
      
      if((!strcmp(comando,"KC"))||
	 (!strcmp(comando,"kc")))
	return(KC);
      
      if((!strcmp(comando,"KD"))||
	 (!strcmp(comando,"kd")))
	return(KD);
      
      if((!strcmp(comando,"KF"))||
	 (!strcmp(comando,"kf")))
	return(KF);
      
      if((!strcmp(comando,"KS"))||
	 (!strcmp(comando,"ks")))
	return(KS);
      
      
      if((!strcmp(comando,"CODE"))||
	 (!strcmp(comando,"code")))
	return(QCODE);
      
      if((!strcmp(comando,"UNPLUG"))||
	 (!strcmp(comando,"unplug")))
	return(UNPLUGST);
      
      if((!strcmp(comando,"TEXTO"))||
	 (!strcmp(comando,"texto")))
	return(CODETEXT);
      
      if((!strcmp(comando,"FILE"))||
	 (!strcmp(comando,"file"))||
	 (!strcmp(comando,"fichero"))||
	 (!strcmp(comando,"FICHERO")))
	return(CODEFILE);
      
      if((!strcmp(comando,"RESET"))||
	 (!strcmp(comando,"reset")))
	return(RESETSTA);
      
      if((!strcmp(comando,"UP"))||
	 (!strcmp(comando,"up"))||
	 (!strcmp(comando,"SUBE"))||
	 (!strcmp(comando,"sube")))
	return(SUBERUEDA);
      
      if((!strcmp(comando,"DOWN"))||
	 (!strcmp(comando,"down"))||
	 (!strcmp(comando,"BAJA"))||
	 (!strcmp(comando,"baja")))
	return(BAJARUEDA);
      
      return(NOCMD);
    }
  else
    return(0);
}

int maquina::loop()
{
  //  char comando[255];
  char param[50];
  int cmd=0;
  int quit=0;

  while(!quit)
  {
    fprintf(stdout,"\n");
    enigma.PrintConfig();
    fprintf(stdout,"\n");
    char *comando=readline(">>:");
    if(!comando)
      break;
    add_history(comando);
    cmd=traducecom(comando,param);
    quit=command(cmd,param);
    free(comando);
  }
  return(0);
}

int maquina::plug(char *param)
{
  if(!strlen(param))
    return(SINPARAMETRO);

  enigma.Plug(param);
  return(0);
  // int len;
  // int i;
  // char sb[3];

  // if(!strlen(param)) 
  //   return(SINPARAMETRO);

  // extrae(param,NULL);
  // len=strlen(param);
  // sb[2]='\0';
  // for(i=0;i<len;i+=2)
  //   {
  //     sb[0]=param[i];
  //     sb[1]=param[i+1];
  //     if(maqerr(enigma->Plug(sb)))
  // 	fprintf(stderr,"%c - %c\n",sb[0],sb[1]);
  //   }
  // return(0);
}
int maquina::unplug(char *param)
{
  int i;
  char sb[3];
  int len;

  if(!strlen(param))
    { 
      enigma.UnPlug(0,0);
      return(0);
    }

  extrae(param,NULL);
  len=strlen(param);
  sb[2]='\0';
  for(i=0;i<len;i+=2)
    {
      sb[0]=param[i];
      sb[1]=param[i+1];
      if(maqerr(enigma.UnPlug(sb[0],sb[1])))
	fprintf(stderr,"%c - %c\n",sb[0],sb[1]);
    }

  return(0);
}
int maquina::setwalze(char *param)
{
 
  if(!strlen(param)) 
    return(SINPARAMETRO);
  
  extrae(param,NULL);
  enigma.setWalze(param);
  return(0);
}

int maquina::mueverueda(int cmd,char *param)
{
  if(!strlen(param)) 
    return(SINPARAMETRO);
  
  extrae(param,NULL);
  
  switch(param[0])
  {
    case '1':
      {
	if (cmd==SUBERUEDA)
	{
	  Start[0]++;
	  Ring[0]++;
	  if(Start[0]>'Z')
	    Start[0]='A';
	  
	  if(Ring[0]>'Z')
	    Ring[0]='A';
	
	}
	else
	{
	  Start[0]--;
	  Ring[0]--;
	  
	  if(Start[0]<'A')
	    Start[0]='Z';
	  
	  if(Ring[0]<'A')
	    Ring[0]='Z';
	}
	break;
      }
      case '2':
      {
	if (cmd==SUBERUEDA)
	{
	  Start[1]++;
	  Ring[1]++;
	  
	  if(Start[1]>'Z')
	    Start[1]='A';
	  
	  if(Ring[1]>'Z')
	    Ring[1]='A';
	
	}
	else
	{
	  Start[1]--;
	  Ring[1]--;
	  
	  if(Start[1]<'A')
	    Start[1]='Z';
	  
	  if(Ring[1]<'A')
	    Ring[1]='Z';
	}      
      
	break;
      }
      case '3':
      {
	if (cmd==SUBERUEDA)
	{
	  Start[2]++;
	  Ring[2]++;
	  if(Start[2]>'Z')
	    Start[2]='A';
	  if(Ring[2]>'Z')
	    Ring[2]='A';
	
	}
	else
	{
	  Start[2]--;
	  Ring[2]--;
	  if(Start[2]<'A')
	    Start[2]='Z';
	  if(Ring[2]<'A')
	    Ring[2]='Z';
	}      
	break;
      }
      default:
	return(WALZE_RUEDAS_INCORRECTAS);
    }

  enigma.setRing(Ring);
  enigma.setKey(Start);

  return(0);
}

int maquina::setring(char *param)
{
  if(!strlen(param)) 
    return(SINPARAMETRO);
 
  extrae(param,NULL);
  strcpy(Ring,param);
  enigma.setRing(Ring);
  return(0);

}

int maquina::setstart(char *param)
{
  if(!strlen(param)) 
    return(SINPARAMETRO);
  
  extrae(param,NULL);
  strcpy(Start,param);
  enigma.setKey(Start);
  return(0);
}
// int maquina::setzusats(char *param)
// {
 
//   if(!strlen(param)) 
//     return(SINPARAMETRO);
  
//   extrae(param,NULL);
//   return(enigma->ZusatCfg(param));
// }
int maquina::codefile(char *param)
{
  int k;
  int ci,co;
  FILE *of,*fi;
  char outf[50];
  
  if(!strlen(param))
    return(SINPARAMETRO);
  
  if(!extrae(param,outf))
    return(SINPARAMETRO);
  
  fi=fopen(param,"r");
  
  if(!fi) 
    return(ERRFICHERO);

  if(extrae(outf,NULL))
  {
    of=fopen(outf,"w");
    if(!of)
    {
      fclose(fi);
      return(ERRFICHERO);
    }
    fprintf(stdout,"Fichero de salida: %s\n",outf);
    enigma.PrintConfig();
  } 
  else
    of=stdout;
    fprintf(of,"\n");
  k=0;
  do
  {
      do
      {
	ci=fgetc(fi);
      } while((!(((ci>='a')&&(ci<='z'))||((ci>='A')&&(ci<='Z'))||(ci=='-')))&&(ci!=EOF));
      if(ci!=EOF)
      {
	co=enigma.Code(ci);
	fprintf(of,"%c",co);
      }

  } while(ci!=EOF);
  fprintf(of,"\n");
  if(of!=stdout) 
    fclose(of);
  
  fclose(fi);

  return(0);
}
int maquina::quickcode(char *param)
{

  int codelen;
  int i;
  char ci;
  codelen=strlen(param);

  if(codelen<=0)
    return(SINPARAMETRO);

  for(i=0;i<codelen;i++)
    {
      ci=param[i];
      if( 
	 ((ci>='a')&&(ci<='z'))||
	 ((ci>='A')&&(ci<='Z')))
	fprintf(stdout,"%c",enigma.Code(ci));
    }
  fprintf(stdout,"\n");
  return(0);

}

int maquina::codetext(char *param)
{
  int k;
  int ci,co;
  FILE *of;

  if(strlen(param))
  {
    extrae(param,NULL);
    of=fopen(param,"w");
    if(!of)
       return(ERRFICHERO);
    enigma.PrintConfig();
  } 
  else
    of=stdout;
      
  fprintf(stdout,"ESC para salir\n");

  k=0;
  do
  {
    do
    {
      do
      {
	ci=fgetc(stdin);
	if(ci==10)
	{
	  fprintf(of,"\n");
	  k=0;
	}
      } while((!(((ci>='a')&&(ci<='z'))||((ci>='A')&&(ci<='Z'))||(ci=='-')))&&(ci!=27));
      if(ci!=27)
      {
	co=enigma.Code(ci);
	fprintf(of,"%c",co);
      }
      k++;
    }while ((k<5)&&(ci!=27));
    fprintf(of," ");
    k=0;
  } while(ci!=27);
  
  if(of!=stdout) 
    fclose(of);

  while(fgetc(stdin)!=10);

  return(0);
}
int maquina::cambiamaq(char *param)
{
  if(!strlen(param)) 
    return(SINPARAMETRO);

  extrae(param,NULL);

  if(param[0]=='M')
    {
      tipo=M4;
      enigma.Modelo(M4);
    }
  else if (param[0]=='K')
    {

      switch(param[1])
	{
	case 'D':
	  {
	    tipo=KD;
	    enigma.Modelo(KD);
	    break;
	  }
	case 'F':
	  {
	    tipo=KF;
	    enigma.Modelo(KF);
	    break;
	  }
	case 'S':
	  {
	    tipo=KS;
	    enigma.Modelo(KS);
	    break;
	  }
	case 'C':
	default:
	  {
	    tipo=KC;
	    enigma.Modelo(KC);
	    break;
	  }
	}
    }
  
  else
    return(TIPOINCORRECTO);
  
  

  return(0);
}


int maquina::setukw(char *param)
{
  if(!strlen(param)) 
    return(SINPARAMETRO);
  
  if(tipo==M4)
    {
      extrae(param,NULL);
      enigma.setUkw(param);
      return(0);
    }
  else
    return(1);
}
int maquina::maqerr(int err)
{
  switch(err)
    {
    case 0:
      return(0);
    case ERRFICHERO:
      {
	fprintf(stderr,"No se puede abrir fichero\n" );
      }
    case PLUG_YA_PLUG:
      {
	fprintf(stderr,"Letras ya conectadas\n");
	break;
      }
    case UNPLUG_NO_PLUG:
      {
	fprintf(stderr,"Letras no conectadas. Imposible desconectarlas\n");
	break;
      }
    case SINPARAMETRO:
      {
	fprintf(stderr,"Falta parametro\n");
	break;
      }
    case WALZE_RUEDAS_REPETIDAS:
      {
	fprintf(stderr,"Ruedas repetidas");
	break;
      }
    case WALZE_RUEDAS_INCORRECTAS:
      {
	fprintf(stderr,"Ruedas incorrectas\n");
	break;
      }
    case START_LETRAS_INCORRECTAS:
      {
	fprintf(stderr,"Letras de comienzo incorrectas\n");
	break;
      }
    case RING_LETRAS_INCORRECTAS:
      {
	fprintf(stderr,"Letras de ringstellung incorrectas\n");
	break;
      }
    case UNPLUG_LETRAS_INCORRECTAS:
      {
	fprintf(stderr,"Letras del Stecker incorrectas\n");
	break;
      }
    // case ZUSAT_INCORRECTO:
    //   {
    // 	fprintf(stderr,"Zusatswalze incorrecta\n");
    // 	break;
    //   }
    case UKW_INCORRECTO:
      {
	fprintf(stderr,"Umkerwehr incorrecto\n");
	break;
      }
    default:
      {
	fprintf(stderr,"Error desconocido:%i\n",err);
	exit(1);
      }
    }
  return(err);
}

int extrae(char *a,char *b)
{
  int i=0,j=0;
  int len=0;
  int flag=0;
  char lab[50];
  if(!a) 
    return(0);

  len=strlen(a);
  while((!letra(a[i],2))&&(i<len)) // Elimina los primeros espacios
      i++;
  if(i>=len) 
    return(0);

  while(letra(a[i],2)&&(i<len)) // Copia el primer texto
  {
    lab[j]=a[i];
    i++;
    j++;
  }
  lab[j]='\0';
  if(b)
  {
    while((!letra(a[i],2))&&(i<len)) //elimina m�s espacios
      i++;
    j=0;
    while(i<len)
    {
      b[j]=a[i];
      i++;
      j++;
    }
    b[j]='\0';
  }
  strcpy(a,lab);
  return(1);
}
int letra(char c,int num)
{
  char abc[]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char Num[]="0123456789";
  char esp[]=".-";
  int len;

  len=strlen(abc);
  for(int i=0;i<len;i++)
  {
    if(c==abc[i]) 
      return(1);
  }
 
  if (num)
  {
    len=strlen(Num);
    for(int i=0;i<len;i++)
    {
      if(c==Num[i])
	return(2);
    }
  }
  if(num!=1)
  {
    len=strlen(esp);
    for(int i=0;i<len;i++)
    {
      if(c==esp[i])
	return(3);
    }
  }
  
  return(0);
}
