#include "main.h"

/*Racines de l'unité et les puissances
 * root_unit[N][freq] = exp(-i*2pi*freq*n/N)
 * 
 *
 */

#ifdef OLI_RACINES
static double complex root_unit[MAX_FFT][MAX_FFT];
#endif /* OLI_RACINES*/

void fourier_init()
{
#ifdef OLI_RACINES
    int freq;
    int order;
    double exp_factor;
    for(order=1; order<=MAX_FFT; ++order)
    {
	for(freq=0; freq<MAX_FFT; ++freq)
	{
	    exp_factor = 2.0 * M_PI * (double)(freq) / (double)(order);

	    root_unit[order-1][freq] = cexp(-exp_factor*I);
	}
    }
#endif /* OLI_RACINES*/
}

/* 0 < order <= MAX_FFT
 * 0 <= freq < order
 *
 *
 */
static inline double complex root_unit_func(int order, int freq)
{
#ifdef OLI_RACINES
    return root_unit[order-1][freq];
#else
    double exp_factor;
    exp_factor = 2.0 * M_PI * (double)(freq) / (double)(order);
    return cexp(-exp_factor*I);
#endif /* OLI_RACINES*/
}

static double complex coef_even[FFT_LEVELS][H_MAX_FFT];
static double complex coef_odd[FFT_LEVELS][H_MAX_FFT];
static double complex fourier_even[FFT_LEVELS][H_MAX_FFT];
static double complex fourier_odd[FFT_LEVELS][H_MAX_FFT];
void fourier(double complex* input, double complex* output, int size)
{
    int level;
    int size2;
    for(
	    level=0,size2=1;
	    size2<size;
	    size2 = size2<<1,++level
       );
    --level;


    int frequency = 0;
    int n;
    int h_size = size >> 1;
    if(size>1)
    {
	for(n=0;n<size;n+=2)
	{
	    coef_even[level][n>>1] = input[n];
	    coef_odd[level][n>>1] = input[n+1];
	}
	fourier(coef_even[level], fourier_even[level], h_size);
	fourier(coef_odd[level], fourier_odd[level], h_size);
	for(frequency=0;frequency<size;++frequency)
	{
	    output[frequency] = fourier_even[level][frequency&(h_size-1)]
		+ root_unit_func(size, frequency)
		* fourier_odd[level][frequency&(h_size-1)];
	}
    }
    else
    {
	output[0] = input[0];
    }


}

void fourier2(double complex* input, double complex* output, int size)
{
    int frequency;
    int n;
    int mask = size-1;
    int root_index;
    for(frequency=0; frequency<size; ++frequency)
    {
	output[frequency] = 0;
	for(n=0,root_index = 0; n<size; ++n, root_index += frequency)
	{
	    output[frequency]
		+= input[n] * root_unit_func(size, root_index&mask);

	}

    }
}
