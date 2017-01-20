//
// Created by huyiqing on 2017/1/15.
//

#include "marketOrderGenerator.h"




marketOrderGenerator::marketOrderGenerator(int n)
{
    buyOrder.clear();
    sellOrder.clear();
    for (int i = 0; i < n; i++)
    {
        map<int, unsigned int> m1;
        map<int, unsigned int> m2;
        buyOrder.push_back(m1);
        sellOrder.push_back(m2);
    }
}

marketOrderGenerator::~marketOrderGenerator()
{

}

const vector<map<int, unsigned int>>& marketOrderGenerator::generateBuyOrder()
{
    for (int i = 0; i < buyOrder.size(); i++)
    {
        buyOrder[i].clear();
        buyOrder[i][4000] = 2;
        buyOrder[i][4100] = 6;
        buyOrder[i][4400] = 3;
        buyOrder[i][4500] = 9;
        buyOrder[i][4580] = 2;
        buyOrder[i][4620] = 3;
        buyOrder[i][4700] = 7;
        buyOrder[i][5000] = 6;
        buyOrder[i][5100] = 10;
        buyOrder[i][5200] = 1;
    }

    return buyOrder;
}

const vector<map<int, unsigned int>>& marketOrderGenerator::generateSellOrder()
{
    for (int i = 0; i < sellOrder.size(); i++)
    {
        sellOrder[i].clear();
        sellOrder[i][4200] = 3;
        sellOrder[i][4300] = 3;
        sellOrder[i][4400] = 3;
        sellOrder[i][4500] = 3;
        sellOrder[i][4600] = 3;
        sellOrder[i][4700] = 3;
        sellOrder[i][5000] = 3;
        sellOrder[i][5090] = 6;
        sellOrder[i][5100] = 9;
        sellOrder[i][5300] = 5;
        sellOrder[i][5400] = 1;
    }

    return sellOrder;
}

void marketOrderGenerator::generateRandomTable()
{

}