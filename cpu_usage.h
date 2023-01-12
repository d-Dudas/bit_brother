#include <string.h>

void print_cpu_usage(long int *lastValues, long double *cpu_utilization)
{

	// lastSum = lastValues[0];
	// lastIdle = lastValues[1];

	char str[100]; // In acest string se citeste prima linie din /proc/stat

	char* token; // In acest token vor fi pe rand valorile din linia /proc/stat

	int i = 0; // i - coloana din prima linie /proc/stat; printed
	
	// sum - suma valorilor din prima linie din /proc/stat
	// idle - timpul petrecut in repaus; se citeste din prima linie din /proc/stat
	long int sum = 0, idle;

	// idleFraction - procentajul calculat si afisat
	long double idleFraction;

	// Se citeste fisierul /proc/stat
	FILE* fp = fopen("/proc/stat", "r");
	// Se seteaza coloana la 0
	i = 0;
	// Se citeste prima linie din fisier
	fgets(str, 100, fp);
	// Se inchide fisierul
	fclose(fp);
	// Se citeste "cpu" si este ignorat
	token = strtok(str, " ");
	// Suma curenta este 0
	sum = 0;
	// Cat timp sunt coloane necitite...
	while(token != NULL){
		// Se citeste urmatoarea coloana
		token = strtok(NULL, " ");
		if(token != NULL){
			// Se aduna la suma
			sum += atoi(token);
			// Daca am ajuns la coloana idle
			// retinem noul idle
			if(i == 3)
				idle = atoi(token);
			i++;
		}
	}

	// Calculam procentajul
	idleFraction = 100 - (idle-lastValues[1])*100.0/(sum-lastValues[0]);

	printf("\tCPU utilization: %.2LF%%\n", idleFraction);

	// Se actualizeaza valorile
	lastValues[1] = idle;
	lastValues[0] = sum;
	*cpu_utilization = idleFraction;

}

