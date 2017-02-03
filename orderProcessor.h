//
// Created by huyiqing on 2017/1/16.
//

#ifndef STOCK_SIMULATION_ORDERPROCESSOR_H
#define STOCK_SIMULATION_ORDERPROCESSOR_H

#include <map>
#include "marketOrderGenerator.h"
#include "tradeRecord.h"
#include "order.h"

using namespace std;

/**
 * 订单处理器
 */
class orderProcessor {

public:
    /**
     * @param n 股票数量
     * @param priceCache 初始价格（开盘价）
     */
    orderProcessor(int n);
    ~orderProcessor();
    void setOpenPrice_iniVolumn_iniVolumnFlow(int *price0);                 //设置开盘价
    void addBuyOrder (const unordered_map<int, unsigned int>* t);   //把生成的买单加到未处理队列
    void addSellOrder(const unordered_map<int, unsigned int>* t);   //把生成的卖单加到未处理队列
    void shake();        //todo 抖动未处理订单，模拟订单撤回
    const int*        getPriceWithoutMove();   //单得到价格，不处理
    const int* getPriceNRecord(int date, int timeUnitNow, tradeRecord* tr = nullptr, bool usingRecord = false); //处理订单，得到价格，并记录
    const int* getPriceNRecord2();  //测试用
    const map<int, unsigned int>* getUndoBuyOrder();    //得到未处理买单队列
    const map<int, unsigned int>* getUndoSellOrder();   //得到未处理卖单队列
    const map<int, unsigned int>& getUndoBuyOrder(int n);
    const map<int, unsigned int>& getUndoSellOrder(int n);
    Order** getTopBuyFive();        //得到买五
    Order** getTopSellFive();       //得到卖五
    Order* getTopBuyFive(int n);
    Order* getTopSellFive(int n);
    const int*  getPrices();
    const int   getPrices(int n);
    const int*  getVolume();
    const int   getVolume(int n);
    const long* getVolumeFlow();
    const long  getVolumeFlow(int n);
private:
    const int stockNumber;
    int* priceCache;      //每轮价格
    int* volumeCache;     //每轮成交量
    long* volumeFlowCache; //每轮每份订单的（价格*成交量）和
    map<int, unsigned int>*  undoBuyOrder;
    map<int, unsigned int>* undoSellOrder;
    Order**  topFiveBuyOrderCache;          //买五
    Order** topFiveSellOrderCache;          //卖五
};


#endif //STOCK_SIMULATION_ORDERPROCESSOR_H
