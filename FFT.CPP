#include <conio.h>
#include <iostream.h>
#include <string.h>
#include "fft.h"
#include "fftio.h"

int
main(int argc, string_t* argv)
{
	fhandle_t in,out;
	string_t fname;
	error_t error_code;
	int cant_samples,i=0;

	Ccomplex* sample_array;

	clrscr(); //borro la pantalla para mayor claridad

	if(error_code=procesaParametros(argc,argv,fname,cant_samples)) //proceso los parametros de invocacion
		return error_code;

	if (error_code=openFiles(fname,in,out)) //abro los archivos
		return error_code;

	if (error_code=getSamples(in,cant_samples,sample_array)) //parseo el file
		return error_code;											//tomando las muestras

	if (error_code=fft(cant_samples,sample_array))
	{
		delete sample_array;
		return error_code;
	}

	saveResult(out,sample_array,cant_samples);

	delete sample_array;//libero la memoria alocada

	closeFiles(in,out);

	return OK;
}

/**************************************************************************/
int
fft(int cant_samples,Ccomplex* fft_array)
{
	int gamma,cant_mar,grupo,i,g,m;
	Ccomplex a,b,c,t;
	int auxi0,auxi1,auxi2;
	Ccomplex* twiddle;

	gamma=(int)(log(cant_samples)/log(2)); //saco la cantidad de etapas
	cant_mar=cant_samples/2;   //saco la cantidad mariposas
	grupo=1;	//inicializo el grupo

	if (getTwiddles(twiddle,cant_samples/2)) //obtengo los twiddle factors
	{
		fprintf(stderr,"Error en la alocacion de memoria para el vector twiddle. Abortando\n");
		return ERROR_MALLOC;
	}

	//realizo el calculo
	for(i=0;i<gamma;i++)
	{
		for(g=0;g<grupo;g++)
			for(m=0;m<cant_mar;m++)
			{
				auxi0=m+2*cant_mar*g;
				auxi1=m+2*cant_mar*g+(cant_samples/pow2(i+1));
				auxi2=bitReverse(2*g,gamma);

				a=fft_array[auxi0];
				b=fft_array[auxi1];
				c=twiddle[auxi2];
				t=b*c;
				fft_array[auxi0]=a+t;
				fft_array[auxi1]=a-t;
			}

		cant_mar/=2;
		grupo*=2;
	}
	//ordeno el vector de resultados
	sortFFTArray(fft_array,cant_samples,gamma);

	return OK;
}

int
getTwiddles(Ccomplex* & twiddle,int cant)
{
	if(!(twiddle=new Ccomplex[cant]))
		return ERROR_MALLOC;
	else
	{
		int i;

		for (i=0;i<cant;i++) //genero el vector de twiddle factors
		{
			twiddle[i].setReal(cos(-2*M_PI*i/(cant*2)));
			twiddle[i].setImag(sin(-2*M_PI*i/(cant*2)));
		}

		for (i=0;i<cant;i++)//limpio el vector de twiddle factors
		{
			if(fabs(twiddle[i].getReal())<EPSILON)
				twiddle[i].setReal(0);

			if(fabs(twiddle[i].getImag())<EPSILON)
				twiddle[i].setImag(0);
		}

		return OK;
	}
}

void
sortFFTArray(Ccomplex* fft_array,int cant_samples,int gamma)
{
	int k,g;
	Ccomplex auxi;

	for (k=0;k<cant_samples;k++)
	{
		g=bitReverse(k,gamma);

		if(g>k)
		{
			auxi=fft_array[k];
			fft_array[k]=fft_array[g];
			fft_array[g]=auxi;
		}
	}
}
int
pow2(int i)
{
	int a=1;

	a<<=i;
	return a;
}
int
bitReverse(int n,int gamma)
{
	int a=0,i=0;
	for (i=0;i<gamma-1;i++)
	{
		a|=n&1;
		n>>=1;
		a<<=1;
	}

	a|=n&1;

	return a;
}