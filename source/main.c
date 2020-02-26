/*
 * main.c 
 *
 * Written by Melchor Dominguez
 * Main class for a metropolitan transpotation project.
 * This is the starting point of the application
 */
#include "billing.h"
#include "billing.c"

/*
 * Entry point of the application
 */
int main(void){

    char line[UCHAR_MAX+1];

    printf("***Welcome to Metropolitan Transportation***\n");

    //Read a line of input from the keyboard
    promptAndRead(line);

    while(atoi(line) != 9){
        performNext(line);
    }

}

