//
// Created by huyiqing on 2017/1/20.
//

#ifndef STOCK_SIMULATION_ORDER_H
#define STOCK_SIMULATION_ORDER_H

typedef struct Order Order;

struct Order
{
    int price;
    unsigned int number;
};

#endif //STOCK_SIMULATION_ORDER_H
