//
// Created by huyiqing on 2017/1/16.
//

#include "orderProcessor.h"


orderProcessor::orderProcessor(int n, vector<int>& priceC)
{
    stockNumber = n;
    for (int i = 0; i < priceC.size(); i++)
    {
        priceCache.push_back(priceC[i]);
    }
    undoBuyOrder.clear();
    undoSellOrder.clear();
    for (int i = 0; i < n; i++)
    {
        map<int, unsigned int> m1;
        map<int, unsigned int> m2;
        undoBuyOrder.push_back(m1);
        undoSellOrder.push_back(m2);
    }
}


orderProcessor::~orderProcessor()
{

}

void orderProcessor::addBuyOrder(marketOrderGenerator &mog)
{
    auto temp = mog.generateBuyOrder();
    for (int i = 0; i < temp.size(); i++)
    {
        map<int, unsigned int>::iterator iter;
        for (iter = temp[i].begin(); iter != temp[i].end(); iter++)
        {
            undoBuyOrder[i][iter->first] += iter->second;
        }
    }
}

void orderProcessor::addSellOrder(marketOrderGenerator &mog)
{
    mog.generateSellOrder();
    auto temp = mog.generateSellOrder();
    for (int i = 0; i < temp.size(); i++)
    {
        map<int, unsigned int>::iterator iter;
        for (iter = temp[i].begin(); iter != temp[i].end(); iter++)
        {
            undoSellOrder[i][iter->first] += iter->second;
        }
    }
}

const vector<int>& orderProcessor::getPrice()
{

    for (int i = 0; i < stockNumber; i++)
    {
        auto sellM = undoSellOrder[i];
        auto buyM = undoBuyOrder[i];
        if (sellM.size() == 0 || buyM.size() == 0)
        {
            continue;
        }
        map<int, unsigned int>::iterator         iterSell;
        map<int, unsigned int>::reverse_iterator rIterBuy;
        iterSell = sellM.begin();
        rIterBuy = buyM.rbegin();
        if (iterSell->first > rIterBuy->first)
        {
            continue;
        }
        int temp = 0;
        int price = 0;
        while (iterSell != sellM.end()
                && rIterBuy != buyM.rend()
                && iterSell->first <= rIterBuy->first)
        {
            price = iterSell->first;
            temp += iterSell->second;
            while (iterSell->first <= rIterBuy->first
                    && rIterBuy != buyM.rend()
                    && temp >= rIterBuy->second)
            {
                temp -= rIterBuy->second;
                iterSell->second -= rIterBuy->second;
                //todo add
                rIterBuy++;
                buyM.erase((iterator)rIterBuy);
            }
            iterSell++;
        }
        priceCache[i] = price;
    }

    return priceCache;
}

orderProcessor::tradeRecord::tradeRecord(int n)
{
    for (int i = 0; i < n; i++)
    {
        vector<int> time;
        record_time.push_back(time);
        vector<int> price;
        record_price.push_back(price);
        vector<unsigned int> number;
        record_number.push_back(number);
    }
}

orderProcessor::tradeRecord::~tradeRecord()
{

}

void orderProcessor::tradeRecord::addRecord(int n, int time, int price, unsigned int number)
{
    record_time[n].push_back(time);
    record_price[n].push_back(price);
    record_number[n].push_back(number);
}