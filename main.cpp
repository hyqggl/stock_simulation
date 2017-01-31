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

//    randomTable rt;
//    rt.generateGaussTable();
//    rt.printGeneratedGaussList(8);
//    random_main();

    int n = 2;


    tradeRecord* p_Tr = nullptr;
    bool usingTradeRecord = false;
    tradeRecord tr(usingTradeRecord);
//    bool usingTradeRecord = true;
//    tradeRecord tr(usingTradeRecord, n, 5, "/Users/huyiqing/smTest/tradeRecord/");
    p_Tr = &tr;

    int totalDays = 2;
    int totalTimeUnits = 10000;

    bool usingGeneralRecord = false;

    market mkt(n, totalTimeUnits, p_Tr, usingTradeRecord);

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
    cout<<totalTime;

    return 0;
}