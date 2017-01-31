//
// Created by huyiqing on 2017/1/16.
//

#ifndef STOCK_SIMULATION_MARKET_H
#define STOCK_SIMULATION_MARKET_H

#include <stddef.h>
#include "orderProcessor.h"
#include <iostream>
#include <iomanip>

class market {
public:
    /**
     * 初始化
     * @param n          股票数
     * @param totalTimeU 总时间单位数
     * @param trc        传入的 实时记录器 指针
     * @param utr        是否使用 实时记录器， 默认为不使用时（同时传入空指针）
     */
    market(int n, long totalTimeU, tradeRecord* trc = nullptr, bool utr = false);
    ~market();                //释放内存
    void initialize();        //总体初始化
    void initialize_day();    //一天开始的初始化
    void runAUnit();          //运行一个时间单位
    void endOfDay();          //一天结束，更新相关数据
    void record(int timeUnit_N, int n = -1);  //记录下该时间单位运行后的股价、交易量、交易额，n<0 时更新全部股票，否则更新单个股票。默认更新全部股票

    bool initializeRecord();  //记录IO初始化，清空/新建文件
    bool writeOut(int date, int timeUnitNow);  //写入当日直到某时间单位的记录

    void updateClosePriceAndVolumn(int timeU);

    void printUndoOrder();
    void printPrices();
    void printSellFiveList(int n = -1);
    void printBuyFiveList(int n = -1);

private:
    int**  stockPricesRecord;   //用于记录每天每只股票价格
    int**  volumeRecord;        //.................交易量
    long** volumeFlowReocrd;    //.................交易额

    long   totalTimeUnits;      //总时间单位
    const int   stockNumber;    //股票数
    int   dateNow;              //当前日期，从1起算
    int   timeUnitNow;          //当前时间单位，0为开盘时间单位

    int*  closePriceYestoday;   //昨日收盘价
    int*  volumnYestoday;       //昨日成交量
    int*  priceCell;            //此日最高价
    int*  priceFloor;           //此日最低价
    int*  openPriceToday;       //今日开盘价

    string recordDir;           //记录所在地址
    bool usingTradeRecord;      //是否使用 实时记录器

    orderProcessor op;
    marketOrderGenerator mog;
    tradeRecord* p_tr;
};


#endif //STOCK_SIMULATION_MARKET_H
