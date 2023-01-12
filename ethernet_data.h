#include <string.h>


void print_ethernet_data(unsigned long long *ethernet_received, unsigned long long *ethernet_sent) {

    int found = 0;
    char interface[32], line[256];
	unsigned long long second_reading[2], recv_kbps, trans_kbps;

    FILE *fp = popen("ls -1 /sys/class/net", "r");
    while(fgets(interface, 32, fp))
        if(strncmp(interface, "enp", 3) == 0 || strncmp(interface, "eth", 3) == 0)
        {
            found = 1;
            break;
        }
    fclose(fp);
    interface[strlen(interface) - 1] = '\0';

	// Get the second reading of the interface's stats
	FILE* proc_net_dev = fopen("/proc/net/dev", "r");
	if (proc_net_dev == NULL) {
    	perror("Could not open /proc/net/dev");
    	return;
	}
	while (fgets(line, 256, proc_net_dev)) {
    	if (strstr(line, interface) == line) {
        	sscanf(line, "%*s %llu %*s %*s %*s %*s %*s %*s %*s %llu", &second_reading[0], &second_reading[1]);
        	break;
    	}
	}
	fclose(proc_net_dev);

    if(found == 0) {
        second_reading[0] = 0;
        second_reading[1] = 0;
    }

	// Calculate the kbps
	recv_kbps = (second_reading[0] - *ethernet_received) * 8 / 1024;
	trans_kbps = (second_reading[1] - *ethernet_sent) * 8 / 1024;

    *ethernet_received = second_reading[0];
    *ethernet_sent = second_reading[1];

    printf("Ethernet:\n");
	printf("\tReceived: %llu kbps\n", recv_kbps);
	printf("\tTransmit: %llu kbps\n", trans_kbps);
}
