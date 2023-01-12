#include <string.h>

void print_cpu_usage(int *lastValues)
{
	char str[100]; // In acest string se citeste prima linie din /proc/stat

	char* token; // In acest token vor fi pe rand valorile din linia /proc/stat

	int i = 0, printed = 0; // i - coloana din prima linie /proc/stat; printed
				// printed - daca trebuie sa se updateze statistica
				// afisata
	
	// sum - suma valorilor din prima linie din /proc/stat
	// idle - timpul petrecut in repaus; se citeste din prima linie din /proc/stat
	// lastSum - suma anterioara
	// lasIdle - idle-ul anterior
	long int sum = 0, idle, lastSum = 0, lastIdle = 0;

	// idleFraction - procentajul calculat si afisat
	long double idleFraction;

	// Un loop infinit pentru a updata in continuu statistica	
	while(1){
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
		idleFraction = 100 - (idle-lastIdle)*100.0/(sum-lastSum);

		// Afisam. Daca e prima afisare, atunci e una normala.
		// Altfel, se updateaza ultima linia printata
		if(printed){
			printf("\033[1A");
			printf("\033[K");
			printf("\tCPU usage: %.2LF%%\n", idleFraction);
		}
		else
			printf("\tCPU usage: %.2LF%%\n", idleFraction);

		// Se actualizeaza valorile
		//
		printed++;
		lastIdle = idle;
		lastSum = sum;

		sleep(1);
	}

	return 0;
}

