#include "maquina.hpp"

maquina::maquina()
{
  tipo=M4;
  enigma.Modelo(M4);

  // Salir
  command_map["salir"]=QUIT;
  command_map["quit"]=QUIT;
  command_map["exit"]=QUIT;

  // Seleccionar Reflector
  command_map["ukw"]=SETUKW;

  // Seleccionar ruedas
  command_map["walze"]=SETWALZE;
  command_map["ruedas"]=SETWALZE;

  // Configurar anillo
  command_map["ring"]=SETRINGS;

  // Posicion de inicio
  command_map["start"]=SETSTART;
  command_map["key"]=SETWALZE;

  command_map["reset"]=RESETSTA;
  // Stecker
  command_map["plug"]=PLUGSTEK;
  command_map["stecker"]=PLUGSTEK;
  command_map["unplug"]=UNPLUGST;
  
  // Tipo de maquina
  command_map["tipo"]=CAMBIAMAQ;
  command_map["M4"]=SETM4; // Militar M3 y M4
  command_map["KF"]=KF; // Comercial, conexion F (Enigma española)
  command_map["KC"]=KC;
  command_map["KD"]=KD;
  command_map["KS"]=KS;

  // Codificacion
  command_map["code"]=QCODE;
  command_map["texto"]=CODETEXT;
  command_map["fichero"]=CODEFILE;

  // Lista comandos
  command_map["ayuda"]=LISTACMD;
  command_map["help"]=LISTACMD;
  command_map["lista"]=LISTACMD;
 
  
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
int maquina::command(int cmd,std::string param)
{

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
	enigma.Reset();
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
  case SETM4:
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
      fprintf(stdout,"%s\n",param.data());
      maqerr(cambiamaq(param));
      break;
    }
  case SETUKW:
    {
      maqerr(setukw(param));
      break;
    }
  case LISTACMD:
    {
      Ayuda();
      break;
    }
  case NOCMD:
    {
      //      fprintf(stderr,"Comando desconocido %i\n",cmd);
      break;
    }
  default:
   {
      break;
    }
  }
  return(0);
}
int maquina::traducecom(char *comando,std::string &param)
{
  if(strlen(comando)<1)
    return -1;

  std::string cmd=strtok(comando," ");
  const char *p=strtok(NULL," ");
  if(p!=NULL)
    param=p;
  else
    param="";
	       
  const int CMD=command_map[cmd];
  if(!CMD)
    return(-1);
  else
    return(CMD);
}

int maquina::loop()
{

  std::string param;
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

int maquina::plug(std::string param)
{
  if(!param.length())
    return(SINPARAMETRO);

  enigma.Plug(param.data());
  return(0);
}
int maquina::unplug(std::string param)
{
  const int len=param.length();

  if(!len)
    { 
      enigma.UnPlug(0,0);
      return(0);
    }

  char sb[3];
  sb[2]='\0';
  for(int i=0;i<len;i+=2)
    {
      sb[0]=param[i];
      sb[1]=param[i+1];
      if(maqerr(enigma.UnPlug(sb[0],sb[1])))
	fprintf(stderr,"%c - %c\n",sb[0],sb[1]);
    }

  return(0);
}
int maquina::setwalze(std::string param)
{
 
  if(!param.length()) 
    return(SINPARAMETRO);
  
  enigma.setWalze(param.data());
  return(0);
}

int maquina::setring(std::string param)
{
  if(!param.length()) 
    return(SINPARAMETRO);
 
  strcpy(Ring,param.data());
  enigma.setRing(Ring);
  return(0);

}

int maquina::setstart(std::string param)
{
  if(!param.length())
    return(SINPARAMETRO);
  
  strcpy(Start,param.data());
  enigma.setKey(Start);
  return(0);
}


int maquina::codefile(std::string param)
{
  
  if(!param.length())
    return(SINPARAMETRO);


  char *filein=strtok((char*) param.data()," ");
  char *fileout=strtok(NULL," ");
  
  if(!filein)
    return(SINPARAMETRO);
	   
  FILE *fi=fopen(filein,"r");
  
  if(!fi) 
    return(ERRFICHERO);
  
  FILE *of=fileout!=NULL ? fopen(fileout,"w"): stdout;

  char ci,co;
  int k=0;
  const int grupo = tipo==M4 ? 5 :4;
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
	  k++;
	  if(!(k%grupo))
	    fprintf(of," ");
	}
      
    } while(ci!=EOF);
  fprintf(of,"\n");
  if(of!=stdout) 
    fclose(of);
  
  fclose(fi);
  
  return(0);
}


int maquina::quickcode(std::string param)
{

 int codelen=param.length();

  if(codelen<=0)
    return(SINPARAMETRO);

  int k=0;
  const int grupo = tipo==M4 ? 5 :4;
  
  for(int i=0;i<codelen;i++)
    {
      const char ci=param[i];
      if( 
	 ((ci>='a')&&(ci<='z'))||
	 ((ci>='A')&&(ci<='Z')))
	{
	  fprintf(stdout,"%c",enigma.Code(ci));
	  k++;
	  if(!(k%grupo))
	    fprintf(stdout," ");
	}
    }
  fprintf(stdout,"\n");
  return(0);

}

int maquina::codetext(std::string param)
{
  FILE *of;

  if(param.length()>0)
  {
    of=fopen(param.data(),"w");
    if(!of)
      return(ERRFICHERO);
    enigma.PrintConfig();
  } 
  else
    of=stdout;
      
  fprintf(stdout,"ESC para salir\n");

  int k=0;
  char ci;
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
	      const char co=enigma.Code(ci);
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
int maquina::cambiamaq(std::string param)
{
  if(!param.length()) 
    return(SINPARAMETRO);
  
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


int maquina::setukw(std::string param)
{
  if(!param.length()) 
    return(SINPARAMETRO);
  
  if(tipo==M4)
    {
      enigma.setUkw(param.data());
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
    case RUEDAS_REPETIDAS:
      {
	fprintf(stderr,"Ruedas repetidas");
	break;
      }
    case RUEDAS_INCORRECTAS:
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


void maquina::Ayuda()
{
  printf("Lista de acciones y comandos: \n");
  printf("-----------------------------\n");
  printf("*  Maquina M4 (Kriegsmarine) *\n");
  printf("   ruedas YXXX || walze  YXXX     Configurar ruedas\n");
  printf("                              con Y={B|G} corresponde a la rueda 'extra' Beta o Gamma\n");
  printf("                                  X={1|2|3|4|5|6|7|8}  sin repetir numero de rueda\n\n");
  printf("   ukw {B|C}                      Seleccion de la rueda reflectora.\n\n");
  printf("   ring xxxx                      Configurar el anillo de las ruedas\n");
  printf("                              con x={A...Z}\n\n");
  printf("   start xxxx | key xxxx          Configurar la posición de inicio ruedas\n");
  printf("                              con x={A...Z}\n\n");
  printf("  plug ABCDEFGH...                Conecta el Stecker\n");
  printf("                                  Conecta A con B, C con D, E con F, etc...\n\n");
  printf("  unplug                          Desconecta el Stecker\n");
  printf("  NOTA: La configuracion BBxxx, con anillo Axxx e inicio Axxx es equivalente a una maquina M3 (Wehrmacht) con reflector B\n");
  printf("      y la configuracion CGxxx, con anillo Axxx e inicio Axxx es equivalente a una maquina M3 (Wehrmacht) con reflector C\n\n");
  

  printf("*  Maquina K (comercial) *\n");
  printf("   ruedas XXX || walze  XXX       Configurar ruedas\n");
  printf("                              con X={1|2|3} sin repetir número de rueda\n\n");
  printf("   ring xxxx                      Configurar el anillo del reflector y  ruedas\n");
  printf("                              con x={A...Z}\n\n");
  printf("   start xxxx | key xxxx          Configurar la posición del reflector y ruedas\n");
  printf("                              con x={A...Z}\n\n");


  printf("*  Tipo de máquina  *\n");
  printf("  tipo {M4|KF|KC|KD|KS}           Selecciona tipo de máquina\n");
  printf("                                  Se puede omitir el comando 'tipo'\n");
  printf("  M4                              Máquina  militar (Kriegsmarine/Wehrmacht)\n");
  printf("  KF                              Modelo comercial usado en España durante la guerra civil\n");  
  printf("  KD | KD | KS                    Máquina  comercial, con distintos cableados de ruiedas\n\n");


  printf("*  Codificación *\n");
  printf("  texto                           Modo edicion para codificar un texto. salir con ESC\n");
  printf("  code <texto>                    Codifica el <texto>\n");
  printf("  fichero <filein> [fileout]      Abre y codifica el <filein>, y lo escribe en <fileout>\n");
  printf("                                  Si no se indica fileout, escribe en la consola\n");

  
  printf("*  Otros comandos  *\n");
  printf("  reset                           Restablece la posición de inicio\n");
  printf("  salir | quit | exit | ctrl+d    Salir\n");
  printf("  ayuda | help | lista            Muestra esta ayuda\n");
  printf("\n-----------------------------\n");
  return;



}
