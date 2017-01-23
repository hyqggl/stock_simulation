#include <iostream>
#include "random_demo.cpp"
#include "orderProcessor.h"
#include "market.h"
#include <fstream>
#include <vector>
#include <time.h>

using namespace std;

int main() {

//    random_main();

    int n = 2;

    bool usingTradeRecord = false;
    tradeRecord* p_Tr = nullptr;
//    tradeRecord tr(usingTradeRecord, n, 5, "/Users/huyiqing/smTest/tradeRecord/");
    tradeRecord tr(false);
    p_Tr = &tr;

    market mkt(n, p_Tr, usingTradeRecord);

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
    return 0;
}