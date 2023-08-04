#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "include/cpu_name.c"
#include "include/cpu_usage.c"
#include "include/cpu_ghz.c"
#include "include/cpu_processes.c"
#include "include/cpu_threads.c"
#include "include/cpu_uptime.c"
#include "include/cpu_usage_graph.c"
#include "include/mem_data.c"
#include "include/mem_graph.c"
#include "include/disks_data.c"
#include "include/ethernet_data.c"
#include "include/wifi_data.c"
#include "include/gpu_data.c"


/**
 * Push all the existent values one position up
 * and insert the new values into the array 
 */
void update_cpu_graph_array(long double *cpu_graph, long double new_value)
{
	for(int i = 1; i < 10; i++)
	{
		cpu_graph[i-1] = cpu_graph[i];
	}
	cpu_graph[9] = new_value;

}

/**
 * Push all the existent values one position up
 * and insert the new values into the array  
 */
void update_mem_graph_array(long double *mem_graph, long double *total_mem ,long double *avl_mem)
{
	long double used_mem = (*total_mem - *avl_mem) / *total_mem * 100;
	for(int i = 1; i < 10; i++)
	{
		mem_graph[i-1] = mem_graph[i];
	}
	mem_graph[9] = used_mem;
}

/**
 * Print every data related to CPU
 */
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

/**
 * Print every data related to memory 
 */
void print_mem_data(long double *total, long double *avl, long double *mem_graph){

	printf("Memory:\n");
	print_mem(total, avl);
	update_mem_graph_array(mem_graph, total, avl);
	print_mem_graph(mem_graph, total);

}

int main(int argc, char** argv){

	// Un array cu valorile necesare pentru calcularea
	// procentajului utilizarii CPU
	long int cpu_usage_values[2] = {0};

	// Ultimul procent de utilizare a CPU
	long double cpu_utilization = 0;

	// Valorile grafului CPU
	long double cpu_graph[10] = {0};

	// Valorile grafului memoriei
	long double mem_graph[10] = {0};

	// Valorile necesare pentru calcularea valorilor
	// pentru graful memoriei
	long double total_mem, avl_mem;

	// Valori folositi in procesul de afisare
	int lines_printed = 0, printed = 0, disks_lines = 0;

	// Valori necesare pentru determinarea valorilor legate de conexiunea la internet
	unsigned long long ethernet_received = 0, ethernet_sent = 0, wifi_received = 0, wifi_sent = 0;

	// Se "curata" ecranul
	system("clear");
	
	while(1)
	{
		// Se afiseaza datele si se calculeaza numarul de randuri afisate
		// pentru fiecare componenta
		
		// CPU
		print_cpu_data(cpu_usage_values, &cpu_utilization, cpu_graph); // 19 lines

		// Memoria
		print_mem_data(&total_mem, &avl_mem, mem_graph); // 17 lines

		// Hard disk
		disks_data(); // lines printed

		// Ethernet
		print_ethernet_data(&ethernet_received, &ethernet_sent); // 3 lines

		// Wi-fi
		print_wifi_data(&wifi_received, &wifi_sent); // 3 lines

		// GPU
		// print_gpu_data(); // 4 lines

		sleep(1);

		system("clear");

	}
	
	return 0;
}
