//
// Created by huyiqing on 2017/1/15.
//

#ifndef STOCK_SIMULATION_MARKETORDERGENERATOR_H
#define STOCK_SIMULATION_MARKETORDERGENERATOR_H

#include <vector>
#include <map>
#include <random>
#include "randomTable.h"

using namespace std;

// 传入参数，传出订单
class marketOrderGenerator
{
public:
    marketOrderGenerator(int n, long totalTU, double* _alpha_p, double* _beta_p, double* _alpha_v, double* _beta_v);
    ~marketOrderGenerator();

    const map<int, unsigned int>* generateBuyOrder(int timeU, int** priceRecord, int* pCell, int* pFloor);             //买单
    const map<int, unsigned int>* generateSellOrder(int timeU, int** priceRecord, int* pCell, int* pFloor);//卖单

    void geneMarketChange_buySide(int* closePriceYestoday);   //生成当日市场买方报价参数
    void geneMarketChange_sellSide(int* closePriceYestoday);  //生成买方报价参数
    void geneMarketVolumnChange_buySide(int* volumnYestoday); //生成买方订单量
    void geneMarketVolumnChange_sellSide(int* volumnYestoday);//生成卖方订单量

    const int** getBuysideOffset();
    const double** getBuysideRatio();
    const int** getSellsideOffset();
    const double** getSellsideRatio();
    const int** getVolumnBuysideOffset();
    const double** getVolumnBuysideRatio();
    const int** getVolumnSellsideOffset();
    const double** getVolumnSellsideRatio();

    void print_buyOrder();
    void print_sellOrder();
private:
    const int stockNumber;
    const long totalTimeUnits;
    map<int, unsigned int>* buyOrder;
    map<int, unsigned int>* sellOrder;

    double*  beta_p;
    double*  alpha_p;
    double*  beta_v;
    double*  alpha_v;
    double** Xtable_buy_cumu_r; //[0 - N]  *  [0 - (TTimeUnits-1)]      |||  (0 - 大盘）
    int**    Xtable_buy_offset; //[0 - (n-1)] * [0 - (TTimeUnits-1)]
    double** Xtable_sell_cumu_r;
    int**    Xtable_sell_offset;
    double** Vtable_buy_cumu_r;
    int**    Vtable_buy_offset;
    double** Vtable_sell_cumu_r;
    int**    Vtable_sell_offset;

    randomTable randomT;
};


#endif //STOCK_SIMULATION_MARKETORDERGENERATOR_H
