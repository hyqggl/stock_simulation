//
// Created by huyiqing on 2017/1/19.
//

#ifndef STOCK_SIMULATION_TRADERECORD_H
#define STOCK_SIMULATION_TRADERECORD_H

#include <vector>
using namespace std;

class tradeRecord {
public:
    tradeRecord(int n);
    ~tradeRecord();
    void addRecord(int n, int time, int price, unsigned int number);
private:
    vector<vector<int>>            record_time;
    vector<vector<int>>           record_price;
    vector<vector<unsigned int>> record_number;
};


#endif //STOCK_SIMULATION_TRADERECORD_H
