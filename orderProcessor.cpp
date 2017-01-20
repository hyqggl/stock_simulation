//
// Created by huyiqing on 2017/1/16.
//

#include "orderProcessor.h"


orderProcessor::orderProcessor(int n, vector<int>& priceC)
{
    priceCache = new int[n];
    stockNumber = n;
    for (int i = 0; i < n; i++)
    {
        priceCache[i] = priceC[i];
    }
    undoBuyOrder.clear();
    undoSellOrder.clear();
    topFiveBuyOrderCache.clear();
    topFiveSellOrderCache.clear();
    for (int i = 0; i < n; i++)
    {
        map<int, unsigned int> m1;
        m1[0] = 0; //Dummy head, getPriceNRecord2
        map<int, unsigned int> m2;
        undoBuyOrder.push_back(m1);
        undoSellOrder.push_back(m2);
        map<int, unsigned int> m3;
        map<int, unsigned int> m4;
        topFiveSellOrderCache.push_back(m3);
        topFiveBuyOrderCache.push_back(m4);
    }
}


orderProcessor::~orderProcessor()
{
    delete []priceCache;
    priceCache = NULL;
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

/**
 * 得到价格，同时改变订单队列
 * @return
 */
const int* orderProcessor::getPriceNRecord(int time, tradeRecord& tr)
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
                tr.addRecord(i, time, iterSell->first, iterBuy->second); //todo record
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
            tr.addRecord(i, time, iterSell->first, iterSell->second); //todo record
            iterBuy->second -= iterSell->second;
            sellM.erase(iterSell++);
        }
        priceCache[i] = price;
    }

    return priceCache;
}

/**
 * 只得到价格
 * 不改变订单队列
 * @return
 */
const int* orderProcessor::getPrice()
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

/**
 * 废弃，只用作测试
 * @return
 */
const int* orderProcessor::getPriceNRecord2()
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

const map<int, unsigned int>& orderProcessor::getUndoSellOrder(int n)
{
    return undoSellOrder[n];
}
const map<int, unsigned int>& orderProcessor::getUndoBuyOrder(int n)
{
    return undoBuyOrder[n];
}

const vector<map<int, unsigned int>>& orderProcessor::getTopSellFive()
{
    for (int i = 0; i < stockNumber; i++)
    {
        topFiveSellOrderCache[i].clear();
        map<int, unsigned int>::iterator it;
        for (it = undoSellOrder[i].begin(); it != undoSellOrder[i].end()
                                            && topFiveSellOrderCache[i].size() < 5; it++)
        {
            topFiveSellOrderCache[i][it->first] = it->second;
        }
    }
    return topFiveSellOrderCache;
}

const vector<map<int, unsigned int>>& orderProcessor::getTopBuyFive()
{
    for (int i = 0; i < stockNumber; i++)
    {
        topFiveBuyOrderCache[i].clear();
        map<int, unsigned int>::iterator it;
        it = undoBuyOrder[i].end();
        for (it--; it->first != 0 && topFiveBuyOrderCache[i].size() < 5; it--)
        {
            topFiveBuyOrderCache[i][it->first] = it->second;
        }
    }
    return topFiveBuyOrderCache;
}

const map<int, unsigned int>& orderProcessor::getTopSellFive(int n)
{
    topFiveSellOrderCache[n].clear();
    map<int, unsigned int>::iterator it;
    for (it = undoSellOrder[n].begin(); it != undoSellOrder[n].end()
                                        && topFiveSellOrderCache[n].size() < 5; it++)
    {
        topFiveSellOrderCache[n][it->first] = it->second;
    }
    return topFiveSellOrderCache[n];
}

const map<int, unsigned int>& orderProcessor::getTopBuyFive(int n)
{
    topFiveBuyOrderCache[n].clear();
    map<int, unsigned int>::iterator it;
    it = undoBuyOrder[n].end();
    for (it--; it->first != 0 && topFiveBuyOrderCache[n].size() < 5; it--)
    {
        topFiveBuyOrderCache[n][it->first] = it->second;
    }
    return topFiveBuyOrderCache[n];
}
