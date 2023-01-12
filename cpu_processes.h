#include <stdio.h>

void print_cpu_processes() {
	int num_processes = 0;
	FILE *fp;
	fp = popen("ps -e | wc -l", "r");
	fscanf(fp, "%d", &num_processes);
	pclose(fp);
	printf("\tProcesses: %d\n", num_processes);
}
