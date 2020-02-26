/**
 * transport.c 
 *
 * Class which will hold all the information for the different transportation systems in the
 * metropolitan area
 */
#include "transport.h"

float busPrice = BUS_PRICE;
float subPrice = SUB_PRICE;
float trainPrice = TRAIN_PRICE;
float bus2Price = BUS2_PRICE;

/* Setters can have a future use for administrators to use*/
void setBusPrice(float newPrice){

}

void setSubPrice(float newPrice){

}

void setTrainPrice(float newPrice){

}

void setBus2Price(float newPrice){

}

/* simple getter methods */
float getBusPrice(void){

    return busPrice;

}

float getSubPrice(void){
    return subPrice;
}

float getTrainPrice(void){
    return trainPrice;
}

float getBus2Price(void){
    return bus2Price;
}
