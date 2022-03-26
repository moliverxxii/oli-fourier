#include "main.h"

static double complex root_unit[MAX_FFT+1][MAX_FFT];

/*Racines de l'unité et les puissances
 * root_unit[N][freq] = exp(-i*2pi*freq*n/N)
 * 
 *
 */

void fourier_init()
{
    int freq;
    int order;
    double exp_factor;
    for(order=1; order<=MAX_FFT; ++order)
    {
	for(freq=0; freq<MAX_FFT; ++freq)
	{
	    exp_factor = 2.0 * M_PI * (double)(freq) / (double)(order);

	    root_unit[order-1][freq] = cexp(exp_factor*I);
	}
    }
}

/* 0 < order <= MAX_FFT
 * 0 <= freq < order
 *
 *
 */
static inline double complex root_unit_func(int order, int freq)
{
    return root_unit[order-1][freq];
}

void fourier(double complex* input, double complex* output, int size)
{
    double complex coef_even[H_MAX_FFT];
    double complex coef_odd[H_MAX_FFT];
    double complex fourier_even[H_MAX_FFT];
    double complex fourier_odd[H_MAX_FFT];
    int frequency = 0;
    int n;
    int h_size = size >> 1;
    if(size>1)
    {
	for(n=0;n<size;n+=2)
	{
	    coef_even[n>>1] = input[n];
	    coef_odd[n>>1] = input[n+1];
	}
	fourier(coef_even, fourier_even, h_size);
	fourier(coef_odd, fourier_odd, h_size);
	for(frequency=0;frequency<size;++frequency)
	{
	    output[frequency] = fourier_even[frequency&(h_size-1)]
		+ root_unit_func(size, frequency)
		* fourier_odd[frequency&(h_size-1)];
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
