/*
 * billing.c
 *
 * Written by Melchor Dominguez
 * The billing class will handle all logic for calculating the prices for different transportation
 * for different individuals.
 *
 */
#include "billing.h"
#include "transport.h"
#include "transport.c"

/* counter for currently bought tickets */
int currentMonthly;
int currentIndividual;

/* hold the next command to use */
int next = 0;

/* pairs for monthly tickets: holds tickey, type of transportation, and discounts*/
struct monthly {
    int key;
    int transportation;
    float discount;

};

/* pairs for tickets, balance, and discounts*/
struct individual{
    int key;
    float balance;
    float discount;
};

/* arrays holding all the tickets*/
struct monthly months[100];
struct individual indivs[100];

/*
 * promptAndRead 
 *
 * Method which will print out the comands
 * @param line - string where command line input will be placed
 */
void promptAndRead(char* line){
    printf("Select one option below\n");
    printf("\t 1--> Purchase an individual ticket\n");
    printf("\t 2--> Purchase a monthly ticket\n");
    printf("\t 3--> Use existing individual ticket\n");
    printf("\t 4--> Use existing monthly ticket\n");
    printf("\t 9--> Quit\n");
    int result = NO_INPUT;
    while( result != OK){
        result = getLine("Enter your choice:", line, MAX_COMMAND_INPUT);
        if(result == TOO_LONG)
            printf("Input was too long, try again\n");
        else if(result == NO_INPUT)
            printf("No input was given, try again\n");
    }

    next = atoi(line);

    
}

/*
 * performNext
 *
 * Method which will perform the next task for the user
 */
void performNext(char* line){
    switch(next){
        case 0:
            promptAndRead(line);
            break;
        case 1:
            purchaseIndividual(line);
            break;
        case 2:
            purchaseMonthly(line);
            break;
        case 3:
            useIndividual(line);
            break;
        case 4:
            useMonthly(line);
            break;
        default:
            printf("an invalid entry was given, returning to main screen\n");
            next = 0;
   }
}

/*
 * purchaseIndividual 
 *
 * Method which will print out all of the commands for individual ticket purchase
 * Assumption: Users can not board transportation here
 * @param line - holds input to check if quiting application
 */
void purchaseIndividual(char* line){
    currentIndividual++;
    printf("Your ticket number is: %i\n", currentIndividual);
    
    printf("Do you qualify for a discount?\n");
    printf("\t 1--> Student\n");
    printf("\t 2--> Elderly\n");
    printf("\t 3--> No\n");
    int result = NO_INPUT;

    while(result != OK){
        result = getLine("Enter your choice:", line, MAX_COMMAND_INPUT);
        if(result == TOO_LONG)
            printf("Input was too long, try again\n");
        else if(result == NO_INPUT)
            printf("No input was given, try again\n");
    }

    int checkDiscount = atoi(line);
    
    result = NO_INPUT;
    while(result != OK){
        result = getLine("Enter how much to deposit into account:", line, UCHAR_MAX +1);
        if(result == TOO_LONG)
            printf("Input was too long, try again\n");
        if(result == NO_INPUT)
            printf("No input was given, try again\n");
    }

    float discount = 1;
    if(checkDiscount == 1 )
        discount = STUDENT;
    else if (checkDiscount == 2)
        discount = ELDER;
    indivs[currentIndividual-1].key = currentIndividual;
    indivs[currentIndividual-1].balance = strtof(line, NULL);
    indivs[currentIndividual-1].discount = discount;
    
    printf("ticket %i balance: %f\n", indivs[currentIndividual-1].key, indivs[currentIndividual-1].balance);

    next = 0;
    
}

/*
 * purchase Monthly
 * Method which will print out all of the commands for individual ticket purchase
 * Assumption: Users can not board transportation here
 * Assumption: User pays full cost
 * @param line - holds input to check if quiting application
 */
void purchaseMonthly(char* line){
    currentMonthly++;
    printf("Your ticket number is: %i\n", currentMonthly);

    printf("Do you qualify for a discount?\n");
    printf("\t 1--> Student\n");
    printf("\t 2--> Elderly\n");
    printf("\t 3--> No\n");
    int result = NO_INPUT;

    while(result != OK){
        result = getLine("Enter your choice:", line, MAX_COMMAND_INPUT);
        if(result == TOO_LONG)
            printf("Input was too long, try again\n");
        else if(result == NO_INPUT)
            printf("No input was given, try again\n");
    }

    int checkDiscount = atoi(line);

    float discount = 1;
    if(checkDiscount == 1)
       discount = STUDENT;
    else if (checkDiscount == 2)
       discount = ELDER;

    printf("Select transportation:\n");
    printf("\t 1--> Bus\n");
    printf("\t 2--> Subway\n");
    printf("\t 3--> Train\n");
    if(discount == ELDER)
            printf("\t 4 --> Elderly Bus\n");

    result = NO_INPUT;
    while(result != OK){
        result = getLine("Enter your choice:", line, MAX_COMMAND_INPUT);
        if(result == TOO_LONG)
            printf("Input was too long, try again\n");
        else if(result == NO_INPUT)
            printf("No input was given, try again\n");
        else if(atoi(line) > 4 || atoi(line) == 0)
            printf("No valid entry selected, try again\n");
    }

    int type = atoi(line);


    months[currentMonthly-1].key = currentMonthly;
    months[currentMonthly-1].transportation = type;
    months[currentMonthly-1].discount = discount;

    float calc = calculateMonthly(months[currentMonthly-1].transportation, discount);
    printf("charged %f\n", calc);

    next = 0;
}

/**
 * calculateMonthly
 *
 * Method which will calculate the monthly price charged
 */
float calculateMonthly(int transportation, float discount){
    time_t now; // time_t is arithmetic time type
    time(&now); //obtain current time
    struct tm *local = localtime(&now);

    float monthDiscount = 1;
    if(local->tm_mday > 15){
        monthDiscount = .5;
    }

    float price = 1;
    switch(transportation){
        case 1:
            price = getBusPrice();
            break;
        case 2:
            price = getSubPrice();
            break;
        case 3:
            price = getTrainPrice();
            break;
        case 4:
            price = getBus2Price();
            break;
        default:
            printf("Other option chosen, bus is the default option\n");
            break;
    }

    price = price * discount * monthDiscount *10 ;  

}

/*
 * useIndividual
 *
 * Method which will help users use their individual tickets
 */
void useIndividual(char* line){
    int result = NO_INPUT;
    while(result != OK){
        result = getLine("please enter your current ticket number:", line, MAX_COMMAND_INPUT);
        if(result == TOO_LONG)
            printf("Input too long, try again\n");
        else if(result == NO_INPUT)
            printf("No input given\n");
        else if(currentIndividual == 0){
            printf("Invalid entry\n");
            result = OK;
        }else{
            int check = atoi(line);
            bool valid = false;
            for(int i = 0; i < currentIndividual; i++){
                if(indivs[0].key == check){
                    proceedIndiv(i);
                    valid = true;
                }
            }
            if(!valid){
                printf("Invalid entry\n");
            }
        }
    }
    
    next = 0;

}

/*
 * proceedIndiv
 *
 * Method which will be executed if the user entered a valid ticket number
 * Assumption: can not increasae account balance
 * @param ticketnum - the reference to the valid ticket 
 */
void proceedIndiv(int ticketRef){

    printf("Current balance: %f\n", indivs[ticketRef].balance);
    printf("What would you like to do?\n");
    char checkOption[MAX_COMMAND_INPUT];
    printf("\t 1 --> board Bus\n");
    printf("\t 2 --> board Subway\n");
    printf("\t 3 --> board Train\n");
    if(indivs[ticketRef].discount == ELDER){
        printf("\t 4 --> board Elderly Bus\n");
    }
    int result = NO_INPUT;
    while(result != OK){
        result = getLine("Enter choice:", checkOption, MAX_COMMAND_INPUT);
        if(result == TOO_LONG)
            printf("Input too long, try again\n");
        else if(result == NO_INPUT)
            printf("no input given, try again\n");
        else if(atoi(checkOption) > 0 && atoi(checkOption) < 5){
            calculateIndividual(ticketRef, atoi(checkOption));
        }else{
            printf("Invalid entry\n");
        }
    }

    next = 0;

}

/*
 * calculateIndividual
 * Method used to calculate individual costs
 */
void calculateIndividual(int ticketRef, int type){
    printf("calculate Individual----\n");
    time_t now; //time_t is arithmetic time type
    time(&now); //obtain current time
    struct tm *local = localtime(&now);
    
    float weekDiscount = .5;
    if(local->tm_wday > 0 && local->tm_wday < 5)
        weekDiscount = 1;

    float price = getBusPrice();
    switch(type){
        case 1:
            price = getBusPrice();
            break;
        case 2:
            price = getSubPrice();
            break;
        case 3:
            price = getTrainPrice();
            break;
        case 4:
            price = getBus2Price();
            break;
        default:
            printf("invalid entry, bus ticket is the default\n");
    }

    price = price * weekDiscount * indivs[ticketRef].discount;
    printf("price:  %f\n", price); 
    if(price > indivs[ticketRef].balance)
        printf("unable to purchase ticket\n");
    else{
        printf("ticket purchased!\n");
        indivs[ticketRef].balance = indivs[ticketRef].balance - price;
    }

    printf("Remaining balance: %f", indivs[ticketRef].balance);

}

/*
 * useMonthly
 * Method when choosing to use a monthly ticket
 */
void useMonthly(char* line){
    int result = NO_INPUT;
    while(result != OK){
        result = getLine("please enter your current ticket number:", line, MAX_COMMAND_INPUT);
        if(result == TOO_LONG)
            printf("Input too long, try again\n");
        else if(result == NO_INPUT)
            printf("No input given, try again\n");
        else if(currentMonthly == 0){
            printf("Invalid entry\n");
        }else{
            int check = atoi(line);
            bool valid = false;
            for(int i =  0; i < currentMonthly; i++){
                if(months[i].key == check){
                    proceedMonthly(i);
                    valid = true;
                }
            }
            if(!valid){
                printf("Invalid entry2\n");
            }
        }
    }

    next = 0;
}

/*
 * proceedMonthly
 * A valid ticket was entered and the user may proceed
 */
void proceedMonthly(int ticketRef){
    printf("Where will you be boarding?\n");
    printf("\t 1--> Bus\n");
    printf("\t 2--> Subway\n");
    printf("\t 3--> Train\n");
    if(months[ticketRef].discount == ELDER){
        printf("\t 4--> Elderly Bus\n");
    }
    
    char transLine[MAX_COMMAND_INPUT];

    int result = NO_INPUT;
    while(result != OK){
        result = getLine("Enter choice", transLine, MAX_COMMAND_INPUT);
        if(result == TOO_LONG)
            printf("Input too long, try again\n");
        else if(result == NO_INPUT)
            printf("No input given, try again\n");
        else{
            if(atoi(transLine) != months[ticketRef].transportation)
                printf("Ticket does not match boarding type\n");
            else
                printf("Ticket is valid, you may proceed\n");
        }
        
    }
}

/**
 * getLine
 *
 * Method which will properly get input from the command line
 * @param prompt - String which contains a prompt to print to user
 * @param buff - buffer where the string will be placed
 * @param sz - maximum size of the input line
 */
int getLine(char* prompt, char* buff, size_t sz){
    int ch, extra; 

    // print out the prompt if one is given
    if(prompt != NULL){
        printf("%s", prompt);
        fflush(stdout);
    }
    
    // get the line from the command line
    if(fgets(buff, sz, stdin) == NULL)
       return NO_INPUT;

    if(buff[0] == '\n')
        return NO_INPUT;
    
    // If it was too long, there'll be no newline. In that case, we flush
    // the end of the line so that excess doesn't affect the next call 
    if(buff[strlen(buff)-1] != '\n'){
        extra = 0;
        while(((ch = getchar()) != '\n') && (ch != EOF))
            extra = 1;
        return (extra == 1) ? TOO_LONG : OK;
    }

   // Otherwise remove newline and give string back to caller
   buff[strlen(buff)-1] = '\0';
   return OK;
}
