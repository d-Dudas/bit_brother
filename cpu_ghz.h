#include <string.h>

void print_cpu_ghz(){

	FILE* fd = fopen("/proc/cpuinfo", "r");

	char str[1024];
	char *ptr, *token;

	double ghz;

	for(int i = 0; i < 8; i++)
		fgets(str, 1024, fd);
	
	fclose(fd);

	token = strtok(str, ":");
	token = strtok(NULL, "\n");

	ghz = strtod(token, &ptr) * 0.001;

	printf("\tCPU speed: %.2lf GHz\n", ghz);
}



