#ifndef TRANSPORT_H
    #define TRANSPORT_H

    #define BUS_PRICE   1.00
    #define SUB_PRICE   2.00
    #define TRAIN_PRICE 3.00
    #define BUS2_PRICE  1.00

    /* function signatures */
    void setBusPrice(float);
    void setSubPrice(float);
    void setTrainPrice(float);
    void setBus2Price(float);
    float getBusPrice(void);
    float getSubPrice(void);
    float getTrainPrice(void);
    float getBus2Price(void);
#endif
