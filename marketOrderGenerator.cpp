//
// Created by huyiqing on 2017/1/15.
//

#include "marketOrderGenerator.h"




marketOrderGenerator::marketOrderGenerator(int n, long totalTU):stockNumber(n), totalTimeUnits(totalTU)
{
    buyOrder = new map<int, unsigned int>[n];
    sellOrder = new map<int, unsigned int>[n];
    alpha = new double[n];
    beta = new double[n];
    Xtable_buy_cumu_r = new double* [n + 1];
    Xtable_sell_cumu_r = new double* [n + 1];
    for (int i = 0; i <= n; ++ i)
    {
        Xtable_buy_cumu_r[i] = new double[totalTU];
        Xtable_sell_cumu_r[i] = new double[totalTU];
    }
    Xtable_buy_offset = new int*[n];
    Xtable_sell_offset = new int*[n];
    for (int i = 0; i < n; ++ i)
    {
        Xtable_buy_offset[i] = new int[totalTU];
        Xtable_sell_offset[i] = new int[totalTU];
    }
}

marketOrderGenerator::~marketOrderGenerator()
{
    delete alpha; alpha = NULL;
    delete beta; beta = NULL;
    delete []buyOrder;
    buyOrder = NULL;
    delete []sellOrder;
    sellOrder = NULL;
    delete []Xtable_buy_cumu_r;
    Xtable_buy_cumu_r = NULL;
    delete []Xtable_buy_offset;
    Xtable_buy_offset = NULL;
    delete []Xtable_sell_cumu_r;
    Xtable_buy_cumu_r = NULL;
    delete []Xtable_sell_offset;
    Xtable_buy_offset = NULL;
}

const map<int, unsigned int>* marketOrderGenerator::generateBuyOrder(int timeU, int** priceRecord, int* pCell, int* pFloor)
{
    for (int i = 0; i < stockNumber; i++)
    {
        buyOrder[i].clear();
        buyOrder[i][4000] = 2;
        buyOrder[i][4100] = 6;
        buyOrder[i][4400] = 3;
        buyOrder[i][4500] = 9;
        buyOrder[i][4580] = 2;
        buyOrder[i][4620] = 3;
        buyOrder[i][4700] = 7;
        buyOrder[i][5000] = 6;
        buyOrder[i][5100] = 10;
        buyOrder[i][5200] = 1;
    }

    return buyOrder;
}

const map<int, unsigned int>* marketOrderGenerator::generateSellOrder(int timeU, int** priceRecord, int* pCell, int* pFloor)
{
    for (int i = 0; i < stockNumber; i++)
    {
        sellOrder[i].clear();
        sellOrder[i][4200] = 3;
        sellOrder[i][4300] = 3;
        sellOrder[i][4400] = 3;
        sellOrder[i][4500] = 3;
        sellOrder[i][4600] = 3;
        sellOrder[i][4700] = 3;
        sellOrder[i][5000] = 3;
        sellOrder[i][5090] = 6;
        sellOrder[i][5100] = 9;
        sellOrder[i][5300] = 5;
        sellOrder[i][5400] = 1;
    }

    return sellOrder;
}

void marketOrderGenerator::getAlphaBeta() //todo
{
    for (int i = 0; i < stockNumber; i++)
    {
        alpha[i] = 0;
        beta[i] = 1;
    }
}

void marketOrderGenerator::geneMarketChange_buySide(int* closePriceYestoday)
{
    int upDown[totalTimeUnits];
    int votaMulti[totalTimeUnits];
    double bp = 0.2 / totalTimeUnits;  //todo
    double upProb = 0.5;
    long remain = totalTimeUnits;
    double U1;
    long U2;
    long quat = totalTimeUnits >> 3;
    long counter = 0;
    while (remain > 0)
    {
        U1 = (double)rand() / RAND_MAX;

        if (remain >= quat) {
            U2 =(long)( quat * ((double) rand() / RAND_MAX));
        } else {
            U2 =(long)( remain * ((double) rand() / RAND_MAX));
        }
        if (U2 <= 0) {
            U2 = -U2;
            U2 ++;
        }
        for (long i = counter; i < counter + U2; ++ i)
        {
            if (U1 >= upProb) {
                upDown[i] = 1;
            } else {
                upDown[i] = -1;
            }
        }
        counter += U2;
        remain -= U2;
    }

    //get votaMulti
    long brange = totalTimeUnits / 400;
    long bsrange = totalTimeUnits / 800;
    long mid = totalTimeUnits / 2;
    for (int i = 0; i < totalTimeUnits; ++ i)
    {
        if (i < bsrange || (i > mid - bsrange && i < mid + bsrange)
            || i > totalTimeUnits - bsrange)
        {
            votaMulti[i] = 4;
        } else if (i < brange || (i > mid - brange && i < mid + brange)
                   || i > totalTimeUnits - brange)
        {
            votaMulti[i] = 2;
        } else votaMulti[i] = 1;
    }

    for (long i = 0; i < totalTimeUnits; ++ i)
    {
        Xtable_buy_cumu_r[0][i] = bp * upDown[i] * votaMulti[i];
        for (int j = 1; j <= stockNumber; ++ j)
        {
            Xtable_buy_cumu_r[j][i] = alpha[j-1] + beta[j-1] * Xtable_buy_cumu_r[0][i] + bp*2*((double) rand() / RAND_MAX)*upDown[i];
            if (i > 0)
            {
                Xtable_buy_cumu_r[j][i] = Xtable_buy_cumu_r[j][i-1] * (1 + Xtable_buy_cumu_r[j][i]);
            } else {
                Xtable_buy_cumu_r[j][i] += 1.0;
            }
            Xtable_buy_offset[j-1][i] =(int)( Xtable_buy_cumu_r[j][i] * closePriceYestoday[j-1]);
        }
    }
}

void marketOrderGenerator::geneMarketChange_sellSide(int* closePriceYestoday)
{
    int upDown[totalTimeUnits];
    int votaMulti[totalTimeUnits];
    double bp = 0.2 / totalTimeUnits;  //todo
    double upProb = 0.5;
    long remain = totalTimeUnits;
    double U1;
    long U2;
    long quat = totalTimeUnits >> 3;
    long counter = 0;
    while (remain > 0)
    {
        U1 = (double)rand() / RAND_MAX;

        if (remain >= quat) {
            U2 =(long)( quat * ((double) rand() / RAND_MAX));
        } else {
            U2 =(long)( remain * ((double) rand() / RAND_MAX));
        }
        if (U2 <= 0) {
            U2 = -U2;
            U2 ++;
        }
        for (long i = counter; i < counter + U2; ++ i)
        {
            if (U1 >= upProb) {
                upDown[i] = 1;
            } else {
                upDown[i] = -1;
            }
        }
        counter += U2;
        remain -= U2;
    }

    //get votaMulti
    long brange = totalTimeUnits / 400;
    long bsrange = totalTimeUnits / 800;
    long mid = totalTimeUnits / 2;
    for (int i = 0; i < totalTimeUnits; ++ i)
    {
        if (i < bsrange || (i > mid - bsrange && i < mid + bsrange)
            || i > totalTimeUnits - bsrange)
        {
            votaMulti[i] = 4;
        } else if (i < brange || (i > mid - brange && i < mid + brange)
                   || i > totalTimeUnits - brange)
        {
            votaMulti[i] = 2;
        } else votaMulti[i] = 1;
    }

    for (long i = 0; i < totalTimeUnits; ++ i)
    {
        Xtable_sell_cumu_r[0][i] = bp * upDown[i] * votaMulti[i];
        for (int j = 1; j <= stockNumber; ++ j)
        {
            Xtable_sell_cumu_r[j][i] = alpha[j-1] + beta[j-1] * Xtable_sell_cumu_r[0][i] + bp*2*((double) rand() / RAND_MAX)*upDown[i];
            if (i > 0)
            {
                Xtable_sell_cumu_r[j][i] = Xtable_sell_cumu_r[j][i-1] * (1 + Xtable_sell_cumu_r[j][i]);
            } else {
                Xtable_sell_cumu_r[j][i] += 1.0;
            }
            Xtable_sell_offset[j-1][i] =(int)( Xtable_sell_cumu_r[j][i] * closePriceYestoday[j-1]);
        }
    }
}

const int** marketOrderGenerator::getBuysideOffset()
{
    return (const int**)Xtable_buy_offset;
}

const double** marketOrderGenerator::getBuysideRatio()
{
    return (const double**)Xtable_buy_cumu_r;
}

const int** marketOrderGenerator::getSellsideOffset()
{
    return (const int**)Xtable_sell_offset;
}

const double** marketOrderGenerator::getSellsideRatio()
{
    return (const double**)Xtable_sell_cumu_r;
}

void marketOrderGenerator::generateRandomTable()
{

}


