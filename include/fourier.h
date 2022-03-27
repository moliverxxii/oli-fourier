#ifndef FOURIER_H_
#define FOURIER_H_

#define FFT_LEVELS 16
#define MAX_FFT (1<<FFT_LEVELS)
#define H_MAX_FFT (MAX_FFT>>1)
void fourier_init();
void fourier(double complex* input, double complex* output, int size);
void fourier2(double complex* input,double complex* output, int size);

#endif /* FOURIER_H_ */
