#include <string.h>

/**
 * Print the CPU ghz
 */
void print_cpu_ghz(){

	// The informations about the CPU are in this file
	FILE* fd = fopen("/proc/cpuinfo", "r");

	char str[1024];
	char *ptr, *token;

	double ghz;
	
	// The CPU power is on the 8th line
	for(int i = 0; i < 8; i++)
		fgets(str, 1024, fd);
	
	fclose(fd);

	// Only the numeric part of the line is necessary
	token = strtok(str, ":");
	token = strtok(NULL, "\n");

	// Transform the value in double and then convert it to GHz (*0.001)
	ghz = strtod(token, &ptr) * 0.001;

	// Print the information
	printf("\tCPU speed: %.2lf GHz\n", ghz);
}



