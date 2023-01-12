#include <stdio.h>

#define BUFFSIZE 1024

double get_average_response_time_double_percentage(char* disk) {

    char path[BUFFSIZE]; 
    unsigned long long ios_time, wait_time, total_time;
    double avg_response_time;

    sprintf(path, "/sys/block/%s/stat", disk);
    FILE* fp = fopen(path, "r");
    fscanf(fp, "%*u %*u %*u %*u %*u %*u %*u %*u %*u %llu %llu", &ios_time, &wait_time);
    fclose(fp);

    //printf("ios: %llu; wait: %llu\n", ios_time, wait_time);

    total_time = ios_time;
    avg_response_time = (double)ios_time / wait_time;
    avg_response_time = (avg_response_time/total_time)*100;

    return avg_response_time;
}
