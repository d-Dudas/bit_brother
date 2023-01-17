#include <string.h>

#define BUFFSIZE 1024

void print_gpu_data()
{
    char str[BUFFSIZE];
    char *token, *endptr;
    long double total_memory, used_memory;

    // The following command list the information about VGA
    // There can also be found the GPU model name
    FILE *fp = popen("lspci -v -s $(lspci | grep VGA | awk '{print $1}')", "r");
    fgets(str, BUFFSIZE, fp);
    fclose(fp);

    // Get only the name from the line
    token = strtok(str, ":"); token = strtok(NULL, ":"); token = strtok(NULL, "(");

    // In the following file is the GPU available memory
    fp = fopen("/sys/class/drm/card0/device/memory_accounting/kernel/available_memory", "r");
    fgets(str, BUFFSIZE, fp);
    fclose(fp);

    str[strlen(str)-1] = '\0';

    // Convert to GB. It is possible that the read data is in kB instea of b. If it is so, than we have to multiply with 1024
    total_memory = strtoll(str, &endptr, 10) / (1024.0 * 1024.0 * 1024.0);
    if(total_memory <= 0.01)
        total_memory = total_memory * 1024.0;

    // In the following file is the GPU used memory
    fp = fopen("/sys/class/drm/card0/device/memory_accounting/kernel/used_memory", "r");
    fgets(str, BUFFSIZE, fp);
    fclose(fp);

    str[strlen(str)-1] = '\0';

    // Convert just as in the available memory's case
    used_memory = strtoll(str, &endptr, 10) / (1024.0 * 1024.0 * 1024.0);
    if(used_memory <= 0.01)
        used_memory = used_memory * 1024.0;

    printf("GPU:\n");
    printf("\tGPU:%s\n", token);
    printf("\tTotal memory: %.2Lf GB\n", total_memory);
    printf("\tUsed memory: %.2Lf GB (%.2Lf%%)\n", used_memory, (used_memory / total_memory) * 100);

}