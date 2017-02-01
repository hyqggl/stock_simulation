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
    tradeRecord(bool ou = false, int n = 0, int capacity = 0, string dir = "");
    ~tradeRecord();
    bool initialize();
    void addRecord(int n, int date, int time, int price, unsigned int number);
    void writeOut(int n);
private:
    const bool                 onUsing;
    int                  sNumber;  //股票数
    int*                 counter;  //计数器，记录每只股票当前记录条数
    int                 capacity;  //最大记录容量
    int**            record_date;
    int**            record_time;
    int**           record_price;
    unsigned int** record_number;
    string                direct;  //记录存储地址
    bool             initialized;
    string*        recordNameSet;
};


#endif //STOCK_SIMULATION_TRADERECORD_H
