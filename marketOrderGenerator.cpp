//
// Created by huyiqing on 2017/1/15.
//

#include "marketOrderGenerator.h"




marketOrderGenerator::marketOrderGenerator(int n):stockNumber(n)
{
    buyOrder = new map<int, unsigned int>[n];
    sellOrder = new map<int, unsigned int>[n];
}

marketOrderGenerator::~marketOrderGenerator()
{
    delete []buyOrder;
    buyOrder = NULL;
    delete []sellOrder;
    sellOrder = NULL;
}

const map<int, unsigned int>* marketOrderGenerator::generateBuyOrder()
{
    for (int i = 0; i < stockNumber; i++)
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

const map<int, unsigned int>* marketOrderGenerator::generateSellOrder()
{
    for (int i = 0; i < stockNumber; i++)
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
