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

public:
    orderProcessor(int n, vector<int>& priceCache);
    ~orderProcessor();
    void addBuyOrder (marketOrderGenerator &mog);
    void addSellOrder(marketOrderGenerator &mog);
    void shake();
    const vector<int>&        getPrice();
    const vector<int>& getPriceNRecord();
    const vector<int>& getPriceNRecord2();
    const vector<map<int, unsigned int>>& getUndoBuyOrder();
    const vector<map<int, unsigned int>>& getUndoSellOrder();
private:
    int        stockNumber;
    vector<int> priceCache;
    vector<map<int, unsigned int>>  undoBuyOrder;
    vector<map<int, unsigned int>> undoSellOrder;
};


#endif //STOCK_SIMULATION_ORDERPROCESSOR_H
