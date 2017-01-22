//
// Created by huyiqing on 2017/1/15.
//

#ifndef STOCK_SIMULATION_MARKETORDERGENERATOR_H
#define STOCK_SIMULATION_MARKETORDERGENERATOR_H

#include <vector>
#include <map>

using namespace std;

// 传入参数，传出订单
class marketOrderGenerator
{
public:
    marketOrderGenerator(int n);
    ~marketOrderGenerator();

    const map<int, unsigned int>* generateBuyOrder();             //买单
    const map<int, unsigned int>* generateSellOrder();            //卖单
    void generateRandomTable();
private:
    const int stockNumber;
    float offset;
    float alpha;
    map<int, unsigned int>* buyOrder;
    map<int, unsigned int>* sellOrder;
};


#endif //STOCK_SIMULATION_MARKETORDERGENERATOR_H
