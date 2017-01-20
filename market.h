//
// Created by huyiqing on 2017/1/16.
//

#ifndef STOCK_SIMULATION_MARKET_H
#define STOCK_SIMULATION_MARKET_H

#include <vector>

using namespace std;

/**
 * 用于初始化
 */
class market {
public:
    void getPrices();
private:
    vector<int> stockPrices;

};


#endif //STOCK_SIMULATION_MARKET_H
