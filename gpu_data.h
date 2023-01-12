#include <string.h>

#define BUFFSIZE 1024

void print_gpu_data()
{
    char str[BUFFSIZE];
    char *token, *endptr;
    long double total_memory, used_memory;

    FILE *fp = popen("lspci -v -s $(lspci | grep VGA | awk '{print $1}')", "r");
    fgets(str, BUFFSIZE, fp);
    fclose(fp);
    token = strtok(str, ":"); token = strtok(NULL, ":"); token = strtok(NULL, "(");

    fp = fopen("/sys/class/drm/card0/device/memory_accounting/kernel/available_memory", "r");
    fgets(str, BUFFSIZE, fp);
    fclose(fp);

    str[strlen(str)-1] = '\0';

    total_memory = strtoll(str, &endptr, 10) / (1024.0 * 1024.0 * 1024.0);
    if(total_memory <= 0.01)
        total_memory = total_memory * 1024.0;

    fp = fopen("/sys/class/drm/card0/device/memory_accounting/kernel/used_memory", "r");
    fgets(str, BUFFSIZE, fp);
    fclose(fp);

    str[strlen(str)-1] = '\0';

    used_memory = strtoll(str, &endptr, 10) / (1024.0 * 1024.0 * 1024.0);
    if(used_memory <= 0.01)
        used_memory = used_memory * 1024.0;

    printf("GPU:\n");
    printf("\tGPU:%s\n", token);
    printf("\tTotal memory: %.2Lf GB\n", total_memory);
    printf("\tUsed memory: %.2Lf GB (%.2Lf%%)\n", used_memory, (used_memory / total_memory) * 100);

}