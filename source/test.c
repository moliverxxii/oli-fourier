#include "main.h"

void random_sample(complex double* sample, int size)
{
    int n;
    for(n=0; n<size; ++n)
    {
	sample[n] = arc4random();
    }
}
