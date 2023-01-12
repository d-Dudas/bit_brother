#include <string.h>

#define BUFSIZE 1024

long double getDouble(char *str)
{
    char *token;
    char *endptr;

    token = strtok(str, ":");
    token = strtok(NULL, "\n");
    return (strtold(token, &endptr) / 1048576);
}

void print_mem(long double *total, long double *avl) {

    char *str = (char*)malloc(sizeof(char) * BUFSIZE);
    FILE* fp;
    fp = fopen("/proc/meminfo", "r");

    // Read total memory
    fgets(str, BUFSIZE, fp);
    long double memTotal = getDouble(str);

    // Read free memory
    fgets(str, BUFSIZE, fp);
    long double memFree = getDouble(str);

    // Read available memory
    fgets(str, BUFSIZE, fp);
    long double memAvailable = getDouble(str);

    // Read cached memory
    fgets(str, BUFSIZE, fp); // this is the buffers memory
    fgets(str, BUFSIZE, fp); // this is the cached memory
    long double cached = getDouble(str);

    fclose(fp);

    printf("\tTotal memory: %.2Lf GB\n", memTotal);
    printf("\tFree memory: %.2Lf GB\n", memFree);
    printf("\tAvailable memory: %.2Lf GB\n", memAvailable);
    printf("\tCached memory: %.2Lf GB\n", cached);

    *total = memTotal;
    *avl = memAvailable;
}