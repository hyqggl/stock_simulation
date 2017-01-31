#include <iostream>
#include "random_demo.cpp"
#include "orderProcessor.h"
#include "market.h"
#include "randomTable.h"
#include <fstream>
#include <vector>
#include <time.h>
#include <random>

using namespace std;

int main() {

//    randomTable rt;
//    rt.generateGaussTable();
//    rt.generateGaussTable();
//    rt.printGeneratedGaussList(8);
//    random_main();

    int n = 2;

    bool usingTradeRecord = false;
    tradeRecord* p_Tr = nullptr;
//    tradeRecord tr(usingTradeRecord, n, 5, "/Users/huyiqing/smTest/tradeRecord/");
    tradeRecord tr(false);
    p_Tr = &tr;

 /*   marketOrderGenerator mog(n, 10000);
    mog.getAlphaBeta();
    int flag_price[2] = {4800, 4800};
    int flag_volumn[2] = {10000, 100000000};
    mog.geneMarketChange_buySide(flag_price);
    mog.geneMarketChange_sellSide(flag_price);
    mog.geneMarketVolumnChange_buySide(flag_volumn);
    mog.geneMarketVolumnChange_sellSide(flag_volumn);


    int cell_flag[2] = {5400, 5400};
    int floor_flag[2] = {4500, 4500};
    mog.generateBuyOrder(1, NULL, cell_flag, floor_flag);
    mog.print_buyOrder();
    mog.generateSellOrder(1, NULL, cell_flag, floor_flag);
    mog.print_sellOrder();
*/

    int totalTimeUnits = 10000;

    market mkt(n, totalTimeUnits, p_Tr, usingTradeRecord);

    //计时开始
    clock_t start, finish;
    double totalTime;
    start = clock();

    mkt.initialize();

    for (int day = 1; day <= 1; ++ day)
    {

        mkt.initialize_day();

        for (int i = 1; i <= 10000; i++) {
            mkt.runAUnit();
            mkt.record(i);
        }

        mkt.endOfDay();
//    mkt.initializeRecord();
//    mkt.writeOut(1);

    }
    //计时结束
    finish = clock();
    totalTime = (double_t)(finish - start) / CLOCKS_PER_SEC;
    cout<<totalTime;

    return 0;
}