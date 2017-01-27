//
// Created by huyiqing on 2017/1/15.
//

#ifndef STOCK_SIMULATION_MARKETORDERGENERATOR_H
#define STOCK_SIMULATION_MARKETORDERGENERATOR_H

#include <vector>
#include <map>
#include <random>

using namespace std;

// 传入参数，传出订单
class marketOrderGenerator
{
public:
    marketOrderGenerator(int n, long totalTU);
    ~marketOrderGenerator();

    const map<int, unsigned int>* generateBuyOrder(int timeU, int** priceRecord, int* pCell, int* pFloor);             //买单
    const map<int, unsigned int>* generateSellOrder(int timeU, int** priceRecord, int* pCell, int* pFloor);//卖单

    void getAlphaBeta();
    void geneMarketChange_buySide(int* closePriceYestoday);
    void geneMarketChange_sellSide(int* closePriceYestoday);
    const int** getBuysideOffset();
    const double** getBuysideRatio();
    const int** getSellsideOffset();
    const double** getSellsideRatio();
    void generateRandomTable();
private:
    const int stockNumber;
    const long totalTimeUnits;
    map<int, unsigned int>* buyOrder;
    map<int, unsigned int>* sellOrder;

    double*  beta;
    double*  alpha;
    double** Xtable_buy_cumu_r; //[0 - N]  *  [0 - (TTimeUnits-1)]      |||  (0 - 大盘）
    int**    Xtable_buy_offset; //[0 - (n-1)] * [0 - (TTimeUnits-1)]
    double** Xtable_sell_cumu_r;
    int**    Xtable_sell_offset;
    double** VTable_buy_r;
};


#endif //STOCK_SIMULATION_MARKETORDERGENERATOR_H
