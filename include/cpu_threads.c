#include <stdio.h>

void print_cpu_threads() {
	int num_threads = 0;
	FILE *fp;

	// We can print the threads with a command
	// and then count them with another command
	fp = popen("ps -eL | wc -l", "r");

	// Convert the data to int
	fscanf(fp, "%d", &num_threads);
	pclose(fp);
	printf("\tThreads: %d\n", num_threads);
}
