//
// Created by huyiqing on 2017/1/16.
//

#ifndef STOCK_SIMULATION_ORDERPROCESSOR_H
#define STOCK_SIMULATION_ORDERPROCESSOR_H

#include <vector>
#include <map>
#include "marketOrderGenerator.h"
#include "tradeRecord.h"
#include "order.h"

using namespace std;

class orderProcessor {

public:
    orderProcessor(int n, vector<int>& priceCache);
    ~orderProcessor();
    void addBuyOrder (marketOrderGenerator &mog);
    void addSellOrder(marketOrderGenerator &mog);
    void shake();
    const int*        getPrice();
    const int* getPriceNRecord(int time, tradeRecord& tr);
    const int* getPriceNRecord2();
    const vector<map<int, unsigned int>>& getUndoBuyOrder();  //todo 换掉vector
    const vector<map<int, unsigned int>>& getUndoSellOrder(); //todo 换掉vector
    const map<int, unsigned int>& getUndoBuyOrder(int n);
    const map<int, unsigned int>& getUndoSellOrder(int n);
    Order** getTopBuyFive();
    Order** getTopSellFive();
    Order* getTopBuyFive(int n);
    Order* getTopSellFive(int n);
private:
    int stockNumber;
    int* priceCache;
    vector<map<int, unsigned int>>  undoBuyOrder;
    vector<map<int, unsigned int>> undoSellOrder;
    Order**  topFiveBuyOrderCache;
    Order** topFiveSellOrderCache;
};


#endif //STOCK_SIMULATION_ORDERPROCESSOR_H
