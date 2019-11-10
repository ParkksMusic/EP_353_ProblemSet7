#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sndfile.h>

#define kBufferSize 4096

int main(void){
    SNDFILE *inFile = NULL, *outFile = NULL;
    SF_INFO sfInfo;
    static float buffer[kBufferSize];
    memset(&sfInfo, 0, sizeof(SF_INFO));

    inFile = sf_open("sine.wav", SFM_READ, &sfInfo);
    if(!inFile){
        printf ("Could not open sine.wav\n");
            puts (sf_strerror (NULL));
            return 1;
    }

    if(!sf_format_check(&sfInfo)){
        sf_close(inFile);
            printf("Invalid encoding\n");
            return 1;
    }
    outFile = sf_open("sine10.wav", SFM_WRITE, &sfInfo);

    if(!outFile){
        printf ("Could not pen Sine10.wav");
            puts (sf_strerror(NULL));
            return 1;
    }

    int readcount;
    while((readcount = sf_read_float(inFile, buffer, kBufferSize)) > 0){
        sfInfo.frames *=5;
        printf("%d\n",readcount);
        sf_write_float(outFile, buffer, readcount);
    }

    sf_close(inFile);
        sf_close(outFile);
}