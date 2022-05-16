// INITIALIZING THE LIBRARIES
#include <math.h>
#include <stdint.h>
#include <time.h> 
#include <stdio.h>

#define N 464
#define pi 3.142857
//const int n;

int main(int argc, char **argv)
{
	 int i, k;
	 float ci, dct1[N], dct[N], sum;
	 double time_spent = 0.0;
	 
    // Creating audio buffer (Let Sampling Frequency =  kHz)
    int16_t buf[N] = {0}; // initializing the buffer
    int n;                
     
    // Opening audio file and reading the raw samples with FFmpeg.
    FILE *pipein;
    
    pipein = popen("ffmpeg -i audio.wav -f s16le -ac 1 -", "r");
    fread(buf, 2, N, pipein);
    pclose(pipein);
     
    // Printing the values from the buffer to a file
    FILE *csvfile;
    csvfile = fopen("dragos_samples.csv", "w");
    for (n = 0; n < N; ++n) 
    fprintf(csvfile, "%d\n", buf[n]);
    fclose(csvfile);
	 clock_t begin = clock();
	for (i = 0; i < N; i++) {
        
// ci and depends on frequency 

	if (i == 0) {
		ci = 1 / sqrt(N);
	}
	else {
		ci = sqrt(2) / sqrt(N);
	}
		
  // sum will temporarily store the sum of the cosine signals
	sum = 0; 
	 
	
	
	for (k = 0; k < N; k++) {
		dct1[k] = 0;
		for (n = 0; n < N; n++) {
			dct1[k] = dct1[k] + buf[n] * cos((2 * k + 1) * i * pi / (2 * N));
			sum = sum + dct1[k];
		}
	}
	dct[i] = ci * sum;
 
 
    // Saving the DCT values in a file
    FILE *dctvalues;
    dctvalues = fopen("dctvalues.csv", "a");
    fprintf(dctvalues, "%f\n", dct[i]);
    fclose(dctvalues);
	
	
	printf("%f\n", dct[i]);
}  
 clock_t end = clock();
   time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
   printf("The elapsed time is %f seconds", time_spent);
            
	return 0;
}

