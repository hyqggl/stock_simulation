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
        m1[0] = 0; //Dummy head, getPriceNRecord2
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

const vector<int>& orderProcessor::getPriceNRecord2()
{

    for (int i = 0; i < stockNumber; i++)
    {
        map<int, unsigned int>& sellM = undoSellOrder[i];
        map<int, unsigned int>& buyM = undoBuyOrder[i];
        if (sellM.size() == 0 || buyM.size() == 1)
        {
            continue;
        }
        map<int, unsigned int>::iterator iterSell;
        map<int, unsigned int>::iterator iterBuy;
        iterSell = sellM.begin();
        iterBuy = buyM.end();
        iterBuy--;
        if (iterSell->first > iterBuy->first)
        {
            continue;
        }
        int price = 0;
        while (iterSell != sellM.end()
               && iterSell->first
                  <= iterBuy->first)
        {
            price = iterSell->first;
            while (iterSell->first <= iterBuy->first
                   && iterBuy->first != 0
                   && iterSell->second >= iterBuy->second)
            {
                iterSell->second -= iterBuy->second;
                //record.addRecord(i, 0, iterSell->first, rIterBuy->second);
                buyM.erase(iterBuy--);
            }

            if (iterBuy->first == 0
                || iterSell->first > iterBuy->first)
            {
                if (iterSell->second <= 0)
                {
                    sellM.erase(iterSell);
                }
                break;
            }
            //iterSell.second < rIterBuy.second
            //record.addRecord(i, 0, iterSell->first, iterSell->second);
            iterBuy->second -= iterSell->second;
            sellM.erase(iterSell++); //todo
        }
        priceCache[i] = price;
    }

    return priceCache;
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
                && iterSell->first <= rIterBuy->first)
        {
            price = iterSell->first;
            temp += iterSell->second;
            while (iterSell->first <= rIterBuy->first
                    && rIterBuy != buyM.rend()
                    && temp >= rIterBuy->second)
            {
                temp -= rIterBuy->second;
                ++rIterBuy;
            }
            if (rIterBuy == buyM.rend())
            {
                break;
            }
            if (iterSell->first <= rIterBuy->first)
            {
                iterSell++;
            }
        }
        priceCache[i] = price;
    }

    return priceCache;
}

const vector<int>& orderProcessor::getPriceNRecord()
{

    for (int i = 0; i < stockNumber; i++)
    {
        map<int, unsigned int>& sellM = undoSellOrder[i];
        map<int, unsigned int>& buyM = undoBuyOrder[i];
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
        int price = 0;
        while (iterSell != sellM.end()
               && iterSell->first
                  <= rIterBuy->first)
        {
            price = iterSell->first;
            while (iterSell->first <= rIterBuy->first
                   && rIterBuy != buyM.rend()
                   && iterSell->second >= rIterBuy->second)
            {
                iterSell->second -= rIterBuy->second;
                //record.addRecord(i, 0, iterSell->first, rIterBuy->second);
                buyM.erase((++rIterBuy).base());
            }

            if (rIterBuy == buyM.rend()
                || iterSell->first > rIterBuy->first)
            {
                if (iterSell->second <= 0)
                {
                    sellM.erase(iterSell);
                }
                break;
            }
            //iterSell.second < rIterBuy.second
            //record.addRecord(i, 0, iterSell->first, iterSell->second);
            //something goes wrong, test
            int x = rIterBuy->first;
            int y = rIterBuy->second;
            rIterBuy->second -= iterSell->second;
            x = rIterBuy->first;
            y = rIterBuy->second;
            sellM.erase(iterSell++);
            x = rIterBuy->first;
            y = rIterBuy->second;
        }
        priceCache[i] = price;
    }

    return priceCache;
}

const vector<map<int, unsigned int>>& orderProcessor::getUndoSellOrder()
{
    return undoSellOrder;
}
const vector<map<int, unsigned int>>& orderProcessor::getUndoBuyOrder()
{
    return undoBuyOrder;
}