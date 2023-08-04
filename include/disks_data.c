#include <stdio.h>
#include <string.h>
#include "get_diks_response_time.c"

#define BUFFSIZE 1024

/**
 * Functia "increment_array" face posibila cresterea dinamica a unui vector
 * Primeste ca argument vector care trebuie sa creasca si marimea actuala
 * Returneaza copia vectorului +1 slot nou 
 */
char** increment_array(char** array, int *n)
{
    // Decleram un vector nou de marimea vectorului primit + 1
    char** temp = (char**)malloc(sizeof(char*)*(*n + 1));

    // Datele din vectorul primit se copiaza in vectorul nou
    for(int i = 0; i < *n; i++)
    {
        temp[i] = (char*)malloc(sizeof(char)*strlen(array[i]));
        strcpy(temp[i], array[i]);
    }
    
    // Se creaza noul slot
    temp[*n] = (char*)malloc(sizeof(char) * BUFFSIZE);

    // Se returneaza copia
    return temp;
}

/**
 * Functia detecteaza diskurile din /sys/block/. Cauta cele de tip sda
 * Returneaza un array de stringuri si modifica integerul primit ca argument
 * care reprezinta numarul de diskuri gasiti 
 */
char** get_hard_disk_directories(int *disks_found)
{
    char** hard_disk_directories;
    char path[BUFFSIZE];
    FILE *fp;

    // Lista directoarelor din /sys/block se citeste cu comanda ls
    fp = popen("ls -1 /sys/block | grep '^sda'", "r");
    if(fp == NULL){
        printf("Failed to open \"/sys/block/\"\n");
        exit(1);
    }

    // Se citesc liniile gasite mai sus
    while(fgets(path, BUFFSIZE, fp) != NULL) {
        // Se sterge caracterul '\n' de la finalul stringului
        path[strlen(path)-1] = '\0';
        // Se incrementeaza arrayul
        hard_disk_directories = increment_array(hard_disk_directories, disks_found);
        // Se adauga noul element
        strcpy(hard_disk_directories[*disks_found], path);
        // Se incrementeaza numarul elementelor
        *disks_found = *disks_found + 1;
    }
    
    return hard_disk_directories;
}

/**
 * Pentru fiecare disk gasit, afisam detaliile
*/
void print_disk_data(char *disk)
{
    char path[BUFFSIZE]; 
    char *endptr;
    sprintf(path, "/sys/block/%s/size", disk);

    // Deschidem fisierul care contine capacitatea diskurlui
    FILE *fp = fopen(path, "r");
    fgets(path, BUFFSIZE, fp);
    
    // Convertim in GB
    long int size = (strtol(path, &endptr, 10) * 512) / (1024 * 1024 * 1024);
    printf("\tSize: %ld GB\n", size);

    // Timpul mediu de raspundere se cere dintr-o alta functie
    printf("\tAverage response time: %.2f%%\n", get_average_response_time_double_percentage(disk));
}

/**
 * Se afiseaza detaliile gasite de fiecare disk detectat
*/
void disks_data()
{
    int disks_found = 0;
    char** hard_disk_directories = get_hard_disk_directories(&disks_found);
    for(int i = 0; i < disks_found; i++)
    {
        printf("DISK %d\n", i);
        print_disk_data(hard_disk_directories[i]);
    }

}