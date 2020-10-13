#include <string.h>
#include "fftio.h"

int
procesaParametros(int argc, string_t* argv, string_t & fname,int & cant_samples)
{
	if (argc!=CANT_PARAM)
	{
		fprintf(stderr,"Error en la invocacion. Ej: fft [nombre del archivo"
							"de entrada]");
		return ERROR_PARAM;
	}
	else
	{
		fname=argv[POS_FNAME_IN];
		cant_samples=atoi(argv[POS_CANT_SAMPLES]);
		return OK;
	}
}
/***************************************************************************/

int
openFiles(string_t fnamein,fhandle_t &in,fhandle_t & out)
{
	char *fnameout;
	char ext[]="FFT";

	if(!(fnameout=new char[strlen(fnamein)+strlen(ext)+1]))
	{
		fprintf(stderr,"No hay memoria suficiente. Abortando.\n");
		return ERROR_MALLOC;
	}
	strcpy(fnameout,fnamein);
	strcat(fnameout,ext);

	if((in=fopen(fnamein,"rb"))==NULL)
	{
		fprintf(stderr,"Error al intentar abrir el archivo de lectura. Abortando.\n");
		return ERROR_FOPEN;
	}

	if((out=fopen(fnameout,"wb"))==NULL)
	{
		fclose(in);
		fprintf(stderr,"Error al intentar abrir el archivo de escritura. Abortando.\n");
		return ERROR_FOPEN;
	}
	return OK;
}
/***************************************************************************/
void
closeFiles(fhandle_t &in, fhandle_t &out)
{
	fclose(in);
	fclose(out);
}
/***************************************************************************/
int
getSamples(fhandle_t in, int cant_samples, Ccomplex* &samples)
{
	error_t error_code;

	if (error_code=power2(cant_samples)) //me fijo si es potencia de 2 (esto puede cambiar en otra implementacion)
	{
		fprintf(stderr,"La cantidad de muestras no es potencia de 2. Abortando");
		return error_code;
	}

	if(!(samples=new Ccomplex[cant_samples]))
	{
		fprintf(stderr,"No hay memoria suficiente para la cantidad de muestras. Abortando.\n");
		return ERROR_MALLOC;
	}
	if (error_code=parseFile(in,samples,cant_samples))
		return error_code;

	else return OK;
}
//funciones auxiliares de i/o

int
power2(int cant_samples)
{
	float b;
	b=log(cant_samples)/log(2);

	if (fabs(((int)b)-b)<EPSILON) //me fijo si es potencia de 2 o no
		return OK;
	else return ERROR_2POWER;
}

int
parseFile(fhandle_t fname,Ccomplex* samples,int cant_samples)
{
	int c=' ',i=0,n=0;
	char buffer[MAX_NUMBER_LEN];

	while (n<cant_samples&&c!=EOF)
	{
		while (isspace(c) && (c=fgetc(fname))!=EOF) // me como los espacios
			;
		buffer[i++]=c;
		while(!isspace(c) && (c=fgetc(fname))!=EOF && i<MAX_NUMBER_LEN)
			buffer[i++]=c;
		buffer[i]='\0';

		if(i)
		{
			samples[n].setImag(0);
			samples[n++].setReal(atof(buffer));
			i=0;
		}
	}

	if (n!=cant_samples)
	{
		fprintf(stderr,"El archivo de entrada contiene menos elementos que los declarados.\n");
		return ERROR_CANT_FILEIN;
	}
	else return OK;
}

void
saveResult(fhandle_t out,Ccomplex* fft_array,int cant_samples)
{
	int i;
	for(i=0;i<cant_samples;i++)
		fprintf(out,"%4f%s%4f\t",fft_array[i].getReal(),fft_array[i].getImag()>=0? "+j":"-j",fft_array[i].getImag());
}