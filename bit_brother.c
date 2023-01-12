#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "cpu_name.h"
#include "cpu_usage.h"
#include "cpu_ghz.h"
#include "cpu_processes.h"
#include "cpu_threads.h"
#include "cpu_uptime.h"
#include "cpu_usage_graph.h"
#include "mem_data.h"
#include "mem_graph.h"
#include "disks_data.h"
#include "ethernet_data.h"
#include "wifi_data.h"
#include "gpu_data.h"


void update_cpu_graph_array(long double *cpu_graph, long double new_value)
{
	for(int i = 1; i < 10; i++)
	{
		cpu_graph[i-1] = cpu_graph[i];
	}
	cpu_graph[9] = new_value;

}

void update_mem_graph_array(long double *mem_graph, long double *total_mem ,long double *avl_mem)
{
	long double used_mem = (*total_mem - *avl_mem) / *total_mem * 100;
	for(int i = 1; i < 10; i++)
	{
		mem_graph[i-1] = mem_graph[i];
	}
	mem_graph[9] = used_mem;
}

void resetOutput(int x) {
	for(int i = 0; i <= x; i++)
	{
		printf("\033[1A");
		printf("\033[K");
	}
}

void moveUpTheCursor(int x) {
	for(int i = 0; i <= x; i++)
	{
		printf("\033[1A");
	}
}

void print_cpu_data(long int *cpu_usage_values, long double *cpu_utilization, long double *cpu_graph) {

		printf("CPU:\n");
		print_cpu_name();
		print_cpu_usage(cpu_usage_values, cpu_utilization);
		update_cpu_graph_array(cpu_graph, *cpu_utilization);
		print_cpu_ghz();
		print_cpu_processes();
		print_cpu_threads();
		print_cpu_uptime();
		print_cpu_graph(cpu_graph);
}

void print_mem_data(long double *total, long double *avl, long double *mem_graph){

	printf("Memory:\n");
	print_mem(total, avl);
	update_mem_graph_array(mem_graph, total, avl);
	print_mem_graph(mem_graph, total);

}

int main(int argc, char** argv){

	long int cpu_usage_values[3] = {0};
	long double cpu_utilization = 0;
	long double cpu_graph[10] = {0};
	long double mem_graph[10] = {0};
	long double total_mem, avl_mem;
	int lines_printed = 0, printed = 0, disks_lines = 0;
	unsigned long long ethernet_received = 0, ethernet_sent = 0, wifi_received = 0, wifi_sent = 0;

	//printf("\n\t\tThe Bit Brother is watching you\n\n");
	
	while(1)
	{
		print_cpu_data(cpu_usage_values, &cpu_utilization, cpu_graph); // 19 lines
		if(printed == 0)
			lines_printed += 19;
		print_mem_data(&total_mem, &avl_mem, mem_graph); // 17 lines
		if(printed == 0)
			lines_printed += 17;
		if(printed == 0)
			disks_lines = disks_data(); // lines printed
		else
			disks_data();
		if(printed == 0)
			lines_printed += disks_lines;
		print_ethernet_data(&ethernet_received, &ethernet_sent); // 3 lines
		if(printed == 0)
			lines_printed += 3;
		//moveUpTheCursor(2);
		print_wifi_data(&wifi_received, &wifi_sent); // 3 lines
		print_gpu_data(); // 4 lines
		if(printed == 0)
			lines_printed += 4;

		printed = 1;
		sleep(1);

		//resetOutput(lines_printed);
		system("clear");

	}
	
	return 0;
}
