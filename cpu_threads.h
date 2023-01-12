#include <stdio.h>

void print_cpu_threads() {
	int num_threads = 0;
	FILE *fp;
	fp = popen("ps -eL | wc -l", "r");
	fscanf(fp, "%d", &num_threads);
	pclose(fp);
	printf("\tThreads: %d\n", num_threads);
}
