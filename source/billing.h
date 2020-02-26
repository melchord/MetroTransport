#ifndef BILLING_H
    #define BILLING_H
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <limits.h>
    #include <time.h>
    #include <stdbool.h>
    
    #define OK          0
    #define TOO_LONG    1
    #define NO_INPUT    2
    #define MAX_COMMAND_INPUT   3
    #define STUDENT .75
    #define ELDER   .50


    /* function signatures */
    void promptAndRead(char*);
    int getLine(char*, char*, size_t);
    void performNext(char*);
    void purchaseIndividual(char*);
    void purchaseMonthly(char*);
    void useIndividual(char*);
    void proceedIndiv(int);
    void calculateIndividual(int, int);
    void useMonthly(char*);
    void proceedMonthly(int);
    float calculateMonthly(int, float);

#endif
