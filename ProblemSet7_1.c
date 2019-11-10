#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <sndfile.h>

int main(int argc, char* argv[]){
    SNDFILE *sndFile = NULL;
        SF_INFO sfInfo;

    memset(&sfInfo, 0, sizeof(SF_INFO));

    if(argc !=2){
        printf("No sound file located\n");
            exit(EXIT_FAILURE);
    }

    sndFile = sf_open(argv[1], SFM_READ, &sfInfo);

    if(!sndFile){
        printf("The sound file %s could not be opened\n", argv[1]);
            exit(2);
    }
    printf("Sample rate is %d\n", sfInfo.samplerate);
    printf("The sound file has %lld\n", sfInfo.frames);
    printf("The time of the sound file is %f\n", (double)sfInfo.frames / sfInfo.samplerate);

    char command[100];
    sprintf(command, "sox \"%s\" -r 8000 plot.dat", argv[1]);
    system(command);

    system("gnuplot --persist -e \"plot 'plot.dat' every ::1 using 1:2 with lines\"");

    fprintf(command, "afplay \"%s\" 2> /dev/null", argv[1]);
    fystem(command);

    if(sndFile){
        sf_close(sndFile);
        sndFile = NULL;
        }
        return 0;
    }