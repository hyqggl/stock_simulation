//
// Created by huyiqing on 2017/1/16.
//

#ifndef STOCK_SIMULATION_MARKET_H
#define STOCK_SIMULATION_MARKET_H

#include <stddef.h>
#include "orderProcessor.h"

/**
 * 用于初始化
 */
class market {
public:
    market(int n);
    ~market();
    void initialize();
    void runAUnit();
    void record();
    bool writeOut();
private:
    int**  stockPricesRecord;   //用于记录每只股票价格
    int**  volumeRecord;
    long** volumeFlowReocrd;
    int   totalTimeUnits;
    const int   stockNumber;
    int   dateNow;
    int*  closePriceYestoday;
    int*  openPriceToday;

};


#endif //STOCK_SIMULATION_MARKET_H
