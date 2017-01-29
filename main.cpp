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

    marketOrderGenerator mog(n, 10000);
    mog.getAlphaBeta();
    int flag[2] = {4800, 4800};
    int flag2[2] = {10000, 100000000};
//    mog.geneMarketChange_sellSide(flag);
    mog.geneMarketChange_buySide(flag);
    mog.geneMarketVolumnChange_buySide(flag2);
//    mog.geneMarketVolumnChange_sellSide(flag2);
//    const int** xy = mog.getSellsideOffset();
//    const double** xz = mog.getSellsideRatio();
//    const int** xy1 = mog.getVolumnBuysideOffset();
//    const double** xz1 = mog.getVolumnBuysideRatio();
//        const int** xy1 = mog.getVolumnSellsideOffset();
//    const double** xz1 = mog.getVolumnSellsideRatio();
/*    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 10000; j++)
        {
            cout << xy1[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i <= 2; i++)
    {
        for (int j = 0; j < 10000; j++)
        {
            cout << xz1[i][j] << " ";
        }
        cout << endl;
    }*/

    int cell_flag[2] = {5400, 5400};
    int floor_flag[2] = {4500, 4500};
    mog.generateBuyOrder(1, NULL, cell_flag, floor_flag);
    mog.print_buyOrder();

/*    market mkt(n, 10000, p_Tr, usingTradeRecord);

    //计时开始
    clock_t start, finish;
    double totalTime;
    start = clock();

    mkt.initialize();
    mkt.initialize_day();

    for (int i = 1; i <= 1; i++) {
        mkt.runAUnit();
        mkt.record(i);
    }
    mkt.writeOut(1);


    //计时结束
    finish = clock();
    totalTime = (double_t)(finish - start) / CLOCKS_PER_SEC;
    cout<<totalTime;
    */
    return 0;
}