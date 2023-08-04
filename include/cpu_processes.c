#include <stdio.h>

void print_cpu_processes() {
	int num_processes = 0;
	FILE *fp;

	// We can print the processes with a command
	// and then count them with another command
	fp = popen("ps -e | wc -l", "r");

	// Convert to int
	fscanf(fp, "%d", &num_processes);
	pclose(fp);
	printf("\tProcesses: %d\n", num_processes);
}
