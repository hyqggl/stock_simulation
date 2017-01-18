//
// Created by huyiqing on 2017/1/16.
//

#ifndef STOCK_SIMULATION_ORDERPROCESSOR_H
#define STOCK_SIMULATION_ORDERPROCESSOR_H

#include <vector>
#include <map>
#include "marketOrderGenerator.h"
using namespace std;

class orderProcessor {
    class tradeRecord
    {
    public:
        tradeRecord(int n);
        ~tradeRecord();
        void addRecord(int n, int time, int price, unsigned int number);
    private:
        vector<vector<int>>            record_time;
        vector<vector<int>>           record_price;
        vector<vector<unsigned int>> record_number;
    };
public:
    orderProcessor(int n, vector<int>& priceCache);
    ~orderProcessor();
    void addBuyOrder(marketOrderGenerator &mog);
    void addSellOrder(marketOrderGenerator &mog);
    void shake();
    const vector<int>& getPrice();

private:
    int stockNumber;
    vector<int> priceCache;
    vector<map<int, unsigned int>> undoBuyOrder;
    vector<map<int, unsigned int>> undoSellOrder;
};


#endif //STOCK_SIMULATION_ORDERPROCESSOR_H
