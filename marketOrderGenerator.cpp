//
// Created by huyiqing on 2017/1/15.
//

#include "marketOrderGenerator.h"




marketOrderGenerator::marketOrderGenerator(int n, long totalTU):stockNumber(n), totalTimeUnits(totalTU), randomT()
{
    randomT.generateGaussTable(); //生成随机数表

    buyOrder = new map<int, unsigned int>[n];
    sellOrder = new map<int, unsigned int>[n];
    alpha_p = new double[n];
    beta_p = new double[n];
    alpha_v = new double[n];
    beta_v = new double[n];

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

    Vtable_buy_cumu_r = new double* [n + 1];
    Vtable_sell_cumu_r = new double* [n + 1];
    for (int i = 0; i <= n; ++ i)
    {
        Vtable_buy_cumu_r[i] = new double[totalTU];
        Vtable_sell_cumu_r[i] = new double[totalTU];
    }
    Vtable_buy_offset = new int*[n];
    Vtable_sell_offset = new int*[n];
    for (int i = 0; i < n; ++ i)
    {
        Vtable_buy_offset[i] = new int[totalTU];
        Vtable_sell_offset[i] = new int[totalTU];
    }
}

marketOrderGenerator::~marketOrderGenerator()
{
    delete alpha_p; alpha_p = NULL;
    delete beta_p; beta_p = NULL;
    delete alpha_v; alpha_v = NULL;
    delete beta_v; beta_v = NULL;
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

    delete []Vtable_buy_cumu_r;
    Vtable_buy_cumu_r = NULL;
    delete []Vtable_buy_offset;
    Vtable_buy_offset = NULL;
    delete []Vtable_sell_cumu_r;
    Vtable_buy_cumu_r = NULL;
    delete []Vtable_sell_offset;
    Vtable_buy_offset = NULL;
}

const map<int, unsigned int>* marketOrderGenerator::generateBuyOrder(int timeU, int** priceRecord, int* pCell, int* pFloor)
{
    for (int i = 0; i < stockNumber; i++)
    {
        buyOrder[i].clear();
//        buyOrder[i][4000] = 2;
//        buyOrder[i][4100] = 6;
//        buyOrder[i][4400] = 3;
//        buyOrder[i][4500] = 9;
//        buyOrder[i][4580] = 2;
//        buyOrder[i][4620] = 3;
//        buyOrder[i][4700] = 7;
//        buyOrder[i][5000] = 6;
//        buyOrder[i][5100] = 10;
//        buyOrder[i][5200] = 1;
        int* buy_1;
        unsigned int* buy_2;
        int volumn = Vtable_buy_offset[i][timeU - 1];
        pair<int*, unsigned int*> p = randomT.getGaussOrderSample_byNumber(volumn);
        buy_1 = p.first;
        buy_2 = p.second;
        for (int j = 1; j <= buy_1[0]; ++ j)
        {
            int temp = buy_1[j] + Xtable_buy_offset[i][timeU - 1];
            if (temp <= pCell[i] && temp >= pFloor[i]) {
                buyOrder[i][temp] = buy_2[j];
            }
        }
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
        alpha_p[i] = 0;
        beta_p[i] = 1;
        alpha_v[i] = 0;
        beta_v[i] = 1;
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
            Xtable_buy_cumu_r[j][i] = alpha_p[j-1] + beta_p[j-1] * Xtable_buy_cumu_r[0][i] + bp*2*((double) rand() / RAND_MAX)*upDown[i];
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
            Xtable_sell_cumu_r[j][i] = alpha_p[j-1] + beta_p[j-1] * Xtable_sell_cumu_r[0][i] + bp*2*((double) rand() / RAND_MAX)*upDown[i];
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

void marketOrderGenerator::geneMarketVolumnChange_buySide(int *volumnYestoday)
{
    //int upDown[totalTimeUnits];
    double votaMulti[totalTimeUnits];
    double bp[stockNumber];  //todo
    for (int i = 0; i < stockNumber; ++ i)
    {
        bp[i] = volumnYestoday[i] / totalTimeUnits;
    }
    /*double upProb = 0.5;
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
    }*/

    //get votaMulti
    long brange = totalTimeUnits / 400;
    long bsrange = totalTimeUnits / 800;
    long mid = totalTimeUnits / 2;
    for (int i = 0; i < totalTimeUnits; ++ i)
    {
        if (i < bsrange || (i > mid - bsrange && i < mid + bsrange)
            || i > totalTimeUnits - bsrange)
        {
            votaMulti[i] = 1.5;
        } else if (i < brange || (i > mid - brange && i < mid + brange)
                   || i > totalTimeUnits - brange)
        {
            votaMulti[i] = 1.2;
        } else votaMulti[i] = 1;
    }

    for (long i = 0; i < totalTimeUnits; ++ i)
    {
        Vtable_buy_cumu_r[0][i] = (((double) rand() / RAND_MAX ) - 0.5)  * votaMulti[i];
        for (int j = 1; j <= stockNumber; ++ j)
        {
            Vtable_buy_cumu_r[j][i] =1 + alpha_v[j-1] + beta_v[j-1] * Vtable_buy_cumu_r[0][i]
                                      + 0.5*(((double) rand() / RAND_MAX) - 0.5);
//            if (i > 0)
//            {
//                Vtable_buy_cumu_r[j][i] = Vtable_buy_cumu_r[j][i-1] * (1 + Vtable_buy_cumu_r[j][i]);
//            } else {
//                Vtable_buy_cumu_r[j][i] += 1.0;
//            }
            Vtable_buy_offset[j-1][i] =(int)( Vtable_buy_cumu_r[j][i] * bp[j-1]);
        }
    }
}

void marketOrderGenerator::geneMarketVolumnChange_sellSide(int *volumnYestoday)
{
    //int upDown[totalTimeUnits];
    double votaMulti[totalTimeUnits];
    double bp[stockNumber];  //todo
    for (int i = 0; i < stockNumber; ++ i)
    {
        bp[i] = volumnYestoday[i] / totalTimeUnits;
    }
    /*double upProb = 0.5;
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
    }*/

    //get votaMulti
    long brange = totalTimeUnits / 400;
    long bsrange = totalTimeUnits / 800;
    long mid = totalTimeUnits / 2;
    for (int i = 0; i < totalTimeUnits; ++ i)
    {
        if (i < bsrange || (i > mid - bsrange && i < mid + bsrange)
            || i > totalTimeUnits - bsrange)
        {
            votaMulti[i] = 1.5;
        } else if (i < brange || (i > mid - brange && i < mid + brange)
                   || i > totalTimeUnits - brange)
        {
            votaMulti[i] = 1.2;
        } else votaMulti[i] = 1;
    }

    for (long i = 0; i < totalTimeUnits; ++ i)
    {
        Vtable_sell_cumu_r[0][i] = (((double) rand() / RAND_MAX ) - 0.5)  * votaMulti[i];
        for (int j = 1; j <= stockNumber; ++ j)
        {
            Vtable_sell_cumu_r[j][i] =1 + alpha_v[j-1] + beta_v[j-1] * Vtable_sell_cumu_r[0][i]
                                     + 0.5*(((double) rand() / RAND_MAX) - 0.5);
//            if (i > 0)
//            {
//                Vtable_buy_cumu_r[j][i] = Vtable_buy_cumu_r[j][i-1] * (1 + Vtable_buy_cumu_r[j][i]);
//            } else {
//                Vtable_buy_cumu_r[j][i] += 1.0;
//            }
            Vtable_sell_offset[j-1][i] =(int)( Vtable_sell_cumu_r[j][i] * bp[j-1]);
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

const int** marketOrderGenerator::getVolumnBuysideOffset()
{
    return (const int**)Vtable_buy_offset;
}

const double** marketOrderGenerator::getVolumnBuysideRatio()
{
    return (const double**)Vtable_buy_cumu_r;
}

const int** marketOrderGenerator::getVolumnSellsideOffset()
{
    return (const int**)Vtable_sell_offset;
}

const double** marketOrderGenerator::getVolumnSellsideRatio()
{
    return (const double**)Vtable_sell_cumu_r;
}

void marketOrderGenerator::generateRandomTable()
{

}

void marketOrderGenerator::print_buyOrder()
{
    for (int i = 0; i < stockNumber; ++i)
    {
        cout << "========== Buy Order " << i << "============" << endl;
        map<int, unsigned int>::const_iterator it;
        for (it = buyOrder[i].begin(); it != buyOrder[i].end(); ++ it)
        {
            cout << it->first << " : " << it->second << endl;
        }
    }
}

