//
// Created by huyiqing on 2017/1/16.
//

#include "orderProcessor.h"


orderProcessor::orderProcessor(int n):stockNumber(n)
{
    priceCache = new int[stockNumber];
    volumeCache = new int[stockNumber];
    volumeFlowCache = new long[stockNumber];
    undoBuyOrder = new map<int, unsigned int>[stockNumber];
    undoSellOrder = new map<int, unsigned int>[stockNumber];
    topFiveBuyOrderCache = new Order*[stockNumber];
    topFiveSellOrderCache = new Order*[stockNumber];
    for (int i = 0; i < stockNumber; i++)
    {
        undoBuyOrder[i][0] = 0; //Dummy head, getPriceNRecord2
        topFiveSellOrderCache[i] = new Order[5];
        topFiveBuyOrderCache[i] = new Order[5];
    }
}


orderProcessor::~orderProcessor()
{
    delete []undoBuyOrder;
    delete []undoSellOrder;
    delete []priceCache;
    delete []volumeCache;
    delete []volumeFlowCache;
    priceCache = NULL;
    for (int i = 0; i < stockNumber; i++)
    {
        delete topFiveSellOrderCache[i];
    }
    delete topFiveSellOrderCache;
    topFiveSellOrderCache = NULL;
    for (int i = 0; i < stockNumber; i++)
    {
        delete topFiveBuyOrderCache[i];
    }
    delete topFiveBuyOrderCache;
    topFiveBuyOrderCache = NULL;
}

void orderProcessor::setOpenPrice_iniVolumn_iniVolumnFlow(int *price0)
{
    for (int i = 0; i < stockNumber; i++)
    {
        priceCache[i] = price0[i];
        volumeCache[i] = 0;
        volumeFlowCache[i] = 0;
    }
}

void orderProcessor::addBuyOrder(const map<int, unsigned int>* temp)
{
    for (int i = 0; i < stockNumber; i++)
    {
        map<int, unsigned int>::const_iterator iter;
        for (iter = temp[i].begin(); iter != temp[i].end(); iter++)
        {
            undoBuyOrder[i][iter->first] += iter->second;
        }
    }
}

void orderProcessor::addSellOrder(const map<int, unsigned int>* temp)
{
    for (int i = 0; i < stockNumber; i++)
    {
        map<int, unsigned int>::const_iterator iter;
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
const int* orderProcessor::getPriceNRecord(int date, int timeUnitNow, tradeRecord* tr, bool usingRecord)
{

    for (int i = 0; i < stockNumber; i++)
    {
        volumeCache[i] = 0;
        volumeFlowCache[i] = 0;
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
                volumeCache[i] += iterBuy->second;
                volumeFlowCache[i] += iterSell->first * iterBuy->second;
                if (usingRecord) {
                    tr->addRecord(i, date, timeUnitNow, iterSell->first, iterBuy->second);
                } //todo record
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
            if (usingRecord) {
                tr->addRecord(i, date, timeUnitNow, iterSell->first, iterSell->second);
            } //todo record
            volumeCache[i] += iterSell->second;
            volumeFlowCache[i] += iterSell->first * iterSell->second;
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
const int* orderProcessor::getPriceWithoutMove()
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

const map<int, unsigned int>* orderProcessor::getUndoSellOrder()
{
    return undoSellOrder;
}
const map<int, unsigned int>* orderProcessor::getUndoBuyOrder()
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

Order** orderProcessor::getTopSellFive()
{
    for (int i = 0; i < stockNumber; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            topFiveSellOrderCache[i][j].price = 0;
            topFiveSellOrderCache[i][j].number = 0;
        }
        int counter = 0;
        map<int, unsigned int>::iterator it;
        for (it = undoSellOrder[i].begin(); it != undoSellOrder[i].end()
                                            && counter < 5; it++)
        {
            topFiveSellOrderCache[i][counter].price = it->first;
            topFiveSellOrderCache[i][counter].number = it->second;
            counter++;
        }
    }
    return topFiveSellOrderCache;
}

Order** orderProcessor::getTopBuyFive()
{
    for (int i = 0; i < stockNumber; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            topFiveBuyOrderCache[i][j].price = 0;
            topFiveBuyOrderCache[i][j].number = 0;
        }
        map<int, unsigned int>::iterator it;
        it = undoBuyOrder[i].end();
        int counter = 0;
        for (it--; it->first != 0 && counter < 5; it--)
        {
            topFiveBuyOrderCache[i][counter].price = it->first;
            topFiveBuyOrderCache[i][counter].number = it->second;
            counter++;
        }
    }
    return topFiveBuyOrderCache;
}

Order* orderProcessor::getTopSellFive(int n)
{
    for (int j = 0; j < 5; j++)
    {
        topFiveSellOrderCache[n][j].price = 0;
        topFiveSellOrderCache[n][j].number = 0;
    }
    int counter = 0;
    map<int, unsigned int>::iterator it;
    for (it = undoSellOrder[n].begin(); it != undoSellOrder[n].end()
                                        && counter < 5; it++)
    {
        topFiveSellOrderCache[n][counter].price = it->first;
        topFiveSellOrderCache[n][counter].number = it->second;
        counter++;
    }
    return topFiveSellOrderCache[n];
}

Order* orderProcessor::getTopBuyFive(int n)
{
    for (int j = 0; j < 5; j++)
    {
        topFiveBuyOrderCache[n][j].price = 0;
        topFiveBuyOrderCache[n][j].number = 0;
    }
    map<int, unsigned int>::iterator it;
    it = undoBuyOrder[n].end();
    int counter = 0;
    for (it--; it->first != 0 && counter < 5; it--)
    {
        topFiveBuyOrderCache[n][counter].price = it->first;
        topFiveBuyOrderCache[n][counter].number = it->second;
        counter++;
    }
    return topFiveBuyOrderCache[n];
}

const int* orderProcessor::getPrices()
{
    return priceCache;
}

const int  orderProcessor::getPrices(int n)
{
    return priceCache[n];
}

const int* orderProcessor::getVolume()
{
    return volumeCache;
}

const int  orderProcessor::getVolume(int n)
{
    return volumeCache[n];
}

const long* orderProcessor::getVolumeFlow()
{
    return volumeFlowCache;
}

const long orderProcessor::getVolumeFlow(int n)
{
    return volumeFlowCache[n];
}