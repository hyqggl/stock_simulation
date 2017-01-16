//
// Created by huyiqing on 2017/1/15.
//

#ifndef STOCK_SIMULATION_MARKETORDERGENERATOR_H
#define STOCK_SIMULATION_MARKETORDERGENERATOR_H

#include <vector>

using namespace std;

class marketOrderGenerator
{
public:
    marketOrderGenerator();           //构造函数
    ~marketOrderGenerator();          //析构函数

    void generateRandomTable();       //生成随机数表
    vector<int*> generateOrder(vector<int*>& a);             //下单


private:
    float offset;
};


#endif //STOCK_SIMULATION_MARKETORDERGENERATOR_H
