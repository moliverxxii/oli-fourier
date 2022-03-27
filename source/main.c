#include "main.h"
int main(int argc, char* args[])
{
    FILE* report;
    report = fopen("report.csv","w");
    clock_t time_start = 0;
    clock_t time_end = 0;
    double test_duration;
    float running_time;
    running_time = (float) clock();



    double complex a[MAX_FFT] = {0};
    double complex b[MAX_FFT] = {0};
    double complex c[MAX_FFT] = {0};

    int test_amount;
    if(argc>1)
    {
	test_amount = atoi(args[1]);
	printf("%d\n",test_amount);
    }

    int test_number;
    int n;
    int sample_length;

    fourier_init(); //!!!
    fprintf(report,"\"sample_length\",\"FFT (microseconds)\",\"Slow DFT (microseconds)\"\n");

    for(sample_length = 1; sample_length<=MAX_FFT; sample_length <<= 1)
    {
	printf("taille FFT: %d échantillons\n",sample_length);

	for(test_number = 0; test_number<test_amount; ++test_number)
	{
	    random_sample(a,sample_length);

	    /* FFT test */
	    time_start = clock();
	    fourier(a,b,sample_length);
	    time_end = clock();
	    fprintf(report,"%d,%ld,",
		    sample_length,
		    ((time_end-time_start)));

#define OLI_FFT
#ifdef OLI_FFT
	    /* Slow FT test */
	    time_start = clock();
	    fourier2(a,c,sample_length);
	    time_end = clock();
	    fprintf(report,"%ld\n",time_end-time_start);
#endif /* OLI_FFT */
	}
	printf("FIN FFT%d\n",sample_length);
    }
    running_time += (float) clock();
    running_time /= CLOCKS_PER_SEC;
    printf("durée : %fs\n", running_time);


    fclose(report);

    return EXIT_SUCCESS;
}

