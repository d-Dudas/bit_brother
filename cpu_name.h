#include <string.h>

void print_cpu_name(){

	// Open the /proc/cpuinfo file
	FILE* fd = fopen("/proc/cpuinfo", "r");

	// A char array to read the lines
	char* str = (char*)malloc(sizeof(char)*1024);

	// A token to read the columns
	char* nume;

	// Read the 5th line (there is the CPU model)
	for(int i = 0; i < 5; i++)
		fgets(str, 1024, fd);

	// Close the file
	fclose(fd);

	// The line is: cpu model : <model_name>
	// We need only the <model_name>
	nume = strtok(str, ":");
	nume = strtok(NULL, "\n");

	// Print the result
	printf("\tCPU:%s\n", nume);
}
