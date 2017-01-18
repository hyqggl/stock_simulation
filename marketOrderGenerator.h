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
    marketOrderGenerator(int n);           //构造函数
    ~marketOrderGenerator();          //析构函数

    void generateRandomTable();       //生成随机数表
    const vector<map<int, unsigned int>>& generateBuyOrder();             //买单
    const vector<map<int, unsigned int>>& generateSellOrder();            //卖单


private:
    float offset;
    float alpha;
    vector<map<int, unsigned int>> buyOrder;
    vector<map<int, unsigned int>> sellOrder;
};


#endif //STOCK_SIMULATION_MARKETORDERGENERATOR_H
