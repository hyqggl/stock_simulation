//
// Created by huyiqing on 2017/1/19.
//

#ifndef STOCK_SIMULATION_TRADERECORD_H
#define STOCK_SIMULATION_TRADERECORD_H

#include <stddef.h>
#include <fstream>
#include <string>

using namespace std;

class tradeRecord {
public:
    tradeRecord(int n, int capacity);
    ~tradeRecord();
    void addRecord(int n, int time, int price, unsigned int number);
    void writeOut(int n);
private:
    int                  sNumber;
    int*                 counter;  //计数器，记录当前记录条数
    int                 capacity;
    int**            record_time;
    int**           record_price;
    unsigned int** record_number;
    string                direct;
};


#endif //STOCK_SIMULATION_TRADERECORD_H
