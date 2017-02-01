#include <iostream>
#include "random_demo.cpp"
#include "orderProcessor.h"
#include "market.h"
#include "randomTable.h"
#include <fstream>
#include <time.h>
#include <random>


using namespace std;

int main() {

    int n = 2;    //股票数


    tradeRecord* p_Tr = nullptr;
    bool usingTradeRecord = false;   //是否使用实时记录器
    tradeRecord tr(usingTradeRecord);
//    bool usingTradeRecord = true;
    //后面的记录保存路径请自行修改
//    tradeRecord tr(usingTradeRecord, n, 5, "/Users/huyiqing/smTest/tradeRecord/");
    p_Tr = &tr;

    int totalDays = 2;             //模拟天数
    int totalTimeUnits = 1;        //每天时间单位数

    bool usingGeneralRecord = false;    //是否使用普通记录器

    //订单处理器
    orderProcessor op(n);
    //市场订单生成器
    marketOrderGenerator mog(n, totalTimeUnits);
    //自行修改一般记录存储地址
    market mkt(n, totalTimeUnits, mog, op, "/Users/huyiqing/smTest/", p_Tr, usingTradeRecord);

    //计时开始
    clock_t start, finish;
    double totalTime;
    start = clock();

    mkt.initialize();
    if (usingGeneralRecord) {
        mkt.initializeRecord();
    }

    for (int day = 1; day <= totalDays; ++ day)
    {

        mkt.initialize_day();

        for (int i = 1; i <= totalTimeUnits; i++) {
            mkt.runAUnit();
            mkt.record(i);
        }

        mkt.endOfDay();
        if (usingGeneralRecord) {
            mkt.writeOut(day, totalTimeUnits);
        }
    }




    //计时结束
    finish = clock();
    totalTime = (double_t)(finish - start) / CLOCKS_PER_SEC;
    cout << totalTime << endl;

    return 0;
}