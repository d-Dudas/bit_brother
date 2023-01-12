#include <stdio.h>

void print_cpu_uptime() {
	int uptime_secs, days, hours, minutes, secs;
	FILE *fp;
	fp = fopen("/proc/uptime", "r");
	fscanf(fp, "%d", &uptime_secs);
	fclose(fp);

	days = uptime_secs / (24 * 60 * 60);
	uptime_secs = uptime_secs % (24 * 60 * 60);
	hours = uptime_secs / (60 * 60);
	uptime_secs = uptime_secs % (60 * 60);
	minutes = uptime_secs / 60;
	secs = uptime_secs % 60;

	char cd[3], ch[3], cm[3], cs[3];
	if(days < 10)
		sprintf(cd, "0%d", days);
	else
		sprintf(cd, "%d", days);
	if(hours < 10)
		sprintf(ch, "0%d", hours);
	else
		sprintf(ch, "%d", hours);
	if(minutes < 10)
		sprintf(cm, "0%d", minutes);
	else
		sprintf(cm, "%d", minutes);
	if(secs < 10)
		sprintf(cs, "0%d", secs);
	else
		sprintf(cs, "%d", secs);

	printf("\tUptime: %s:%s:%s:%s\n", cd, ch, cm, cs);
}
