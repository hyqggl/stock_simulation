//
// Created by huyiqing on 2017/1/16.
//

#ifndef STOCK_SIMULATION_MARKET_H
#define STOCK_SIMULATION_MARKET_H

#include <stddef.h>
#include "orderProcessor.h"
#include <iostream>
#include <iomanip>

/**
 * 用于初始化
 */
class market {
public:
    market(int n, long totalTimeU, tradeRecord* trc = nullptr, bool utr = false);
    ~market();
    void initialize();
    void initialize_day();
    void runAUnit();
    void record(int timeUnit_N, int n = -1);
    bool initializeRecord();
    bool writeOut(int date);

    void updateClosePrice();

    void printUndoOrder();
    void printPrices();
    void printSellFiveList(int n = -1);
    void printBuyFiveList(int n = -1);

private:
    int**  stockPricesRecord;   //用于记录每天每只股票价格
    int**  volumeRecord;
    long** volumeFlowReocrd;
    long   totalTimeUnits;
    const int   stockNumber;
    int   dateNow;
    int   timeUnitNow;
    int*  closePriceYestoday;
    int*  priceCell;
    int*  priceFloor;
    int*  openPriceToday;
    string recordDir;
    bool usingTradeRecord;

    orderProcessor op;
    marketOrderGenerator mog;
    tradeRecord* p_tr;
};


#endif //STOCK_SIMULATION_MARKET_H
