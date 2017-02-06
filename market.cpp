//
// Created by huyiqing on 2017/1/16.
//

#include "market.h"

using std::cout;
using std::endl;
using std::ofstream;
using std::ios;
using std::ios_base;
using std::fixed;
using std::setprecision;

market::market(int n, int totalTimeU, marketOrderGenerator& _mog, orderProcessor& _op, string recordDir, tradeRecord* trc, bool utr):stockNumber(n),mog(_mog), op(_op),p_tr(trc),totalTimeUnits(totalTimeU)
, recordDir(recordDir), usingTradeRecord(utr)//todo
{
    closePriceYestoday = new int[stockNumber];
    volumnYestoday = new int[stockNumber];
    priceCell = new int[stockNumber];
    priceFloor = new int[stockNumber];
    openPriceToday = new int[stockNumber];
    stockPricesRecord = new int*[stockNumber];
    volumeRecord      = new int*[stockNumber];
    volumeFlowReocrd = new long*[stockNumber];
    for (int i = 0; i < stockNumber; i++)
    {
        stockPricesRecord[i] = new int[totalTimeUnits + 1];
        volumeRecord[i]      = new int[totalTimeUnits + 1];
        volumeFlowReocrd[i] = new long[totalTimeUnits + 1];
    }
}


market::~market()
{
    delete []closePriceYestoday;
    closePriceYestoday = NULL;
    delete []volumnYestoday;
    volumnYestoday = NULL;
    delete []priceCell;
    priceCell = NULL;
    delete []priceFloor;
    priceFloor = NULL;
    delete []openPriceToday;
    openPriceToday = NULL;
    for (int i = 0; i < stockNumber; i++)
    {
        delete stockPricesRecord[i];
        stockPricesRecord[i] = NULL;
        delete volumeRecord[i];
        volumeRecord[i] = NULL;
        delete volumeFlowReocrd[i];
        volumeFlowReocrd[i] = NULL;
    }
    delete stockPricesRecord;
    stockPricesRecord = NULL;
    delete volumeRecord;
    volumeRecord = NULL;
    delete volumeFlowReocrd;
    volumeFlowReocrd = NULL;

    cout << "Market released." << endl;
}

void market::initialize(int* _closePriceYestoday, int* _volumnYestoday)   //todo       closePriceYestoday, price_cell, price_floor, YestodayVolumn
{
    dateNow = 0;
    for (int i = 0; i < stockNumber; i++)
    {
        closePriceYestoday[i] = _closePriceYestoday[i];
        priceCell[i] =(int)(closePriceYestoday[i] * 1.1);
        priceFloor[i] = (int)(closePriceYestoday[i] * 0.9);
        volumnYestoday[i] = _volumnYestoday[i];
    }
}

void market::initialize_day()  //todo  openPriceToday
{
    dateNow++;
    timeUnitNow = 0;

    for (int i = 0; i < stockNumber; i++)
    {
        openPriceToday[i] = closePriceYestoday[i];
    }
    op.setOpenPrice_iniVolumn_iniVolumnFlow(openPriceToday);//todo
    record(timeUnitNow);

    mog.geneMarketChange_buySide(closePriceYestoday); //todo openPrice
    mog.geneMarketChange_sellSide(closePriceYestoday);
    mog.geneMarketVolumnChange_buySide(volumnYestoday);
    mog.geneMarketVolumnChange_sellSide(volumnYestoday);
}

void market::runAUnit()
{
    timeUnitNow += 1;
    op.addBuyOrder(mog.generateBuyOrder(timeUnitNow, stockPricesRecord, priceCell, priceFloor));
    op.addSellOrder(mog.generateSellOrder(timeUnitNow, stockPricesRecord, priceCell, priceFloor));
    op.getPriceNRecord(dateNow, timeUnitNow, p_tr, usingTradeRecord);
    printPrices();

//    printSellFiveList();
//    printBuyFiveList();

    record(timeUnitNow);
}

void market::endOfDay()
{
    updateClosePriceAndVolumn(timeUnitNow);
}

bool market::initializeRecord()
{
    ofstream sf(recordDir + "tRecord.txt", ios::out);
    sf.close();
    return true;
}

void market::record(int timeUnit_N, int n)
{
    if (n < 0) {
        const int *PR_C = op.getPrices();
        const int *VR_C = op.getVolume();
        const long *VF_C = op.getVolumeFlow();
        for (int i = 0; i < stockNumber; i++) {
            stockPricesRecord[i][timeUnit_N] = PR_C[i];
            volumeRecord[i][timeUnit_N] = VR_C[i];
            volumeFlowReocrd[i][timeUnit_N] = VF_C[i];
        }
    } else {

        if (n >=stockNumber) return;

        const int  PR_C = op.getPrices(n);
        const int  VR_C = op.getVolume(n);
        const long VF_C = op.getVolumeFlow(n);
        stockPricesRecord[n][timeUnit_N] = PR_C;
        volumeRecord[n][timeUnit_N] = VR_C;
        volumeFlowReocrd[n][timeUnit_N] = VF_C;
    }
}

bool market::writeOut(int date, int timeUnitNow)
{
    //todo
    //依次为 股票ID， 日期， 当日时间点，股价，交易量，交易额
    ofstream sf(recordDir + "tRecord.txt", ios_base::app);
    for (int i = 0; i < stockNumber; i++) {
        for (int j = 0; j <= timeUnitNow; j++) {
            sf << i << " " << date << " " << j << " "
                     << stockPricesRecord[i][j] << " "
                     << volumeRecord[i][j] << " "
                     << volumeFlowReocrd[i][j] << " ";
            if (volumeRecord[i][j] == 0) {
                sf << 0 << "\n";
            } else {
                sf << (double) (volumeFlowReocrd[i][j] / volumeRecord[i][j]) << "\n";
            }
        }
    }
    sf.close();
    return true;
}

void market::updateClosePriceAndVolumn(int timeU)  //todo 优化
{
    const int*  PR_C = op.getPrices();
    for (int i = 0; i < stockNumber; i++)
    {
        closePriceYestoday[i] = PR_C[i];
        volumnYestoday[i] = 0;
        for (int j = 1; j <= timeU; ++ j)
        volumnYestoday[i] += volumeRecord[i][j]; //overFlow
    }
}

void market::printUndoOrder()
{
    const map<int, unsigned int>* so = op.getUndoSellOrder();
    const map<int, unsigned int>* bo = op.getUndoBuyOrder();
    cout<<"Sell"<<endl;
    for (int i = 0; i < stockNumber; i++)
    {
        map<int, unsigned int>::const_reverse_iterator it;
        for (it = so[i].rbegin(); it != so[i].rend(); it++)
        {
            cout<<it->first<<" : "<<it->second<<endl;
        }
    }
    cout<<"Buy"<<endl;
    for (int i = 0; i < stockNumber; i++)
    {
        map<int, unsigned int>::const_reverse_iterator it;
        for (it = bo[i].rbegin(); it != bo[i].rend(); it++)
        {
            cout<<it->first<<" : "<<it->second<<endl;
        }
    }
}

void market::printPrices()
{
    const int* a = op.getPrices();

    cout << "当前价格： " << endl;

    cout.setf(ios::fixed);

    for (int i = 0; i < stockNumber; i++)
    {
        cout<< "[" << (i+1) << "] " << fixed << setprecision(2) << (a[i] / 100.0) << endl;
    }

    cout << endl;

    cout.unsetf(ios::fixed);
}

void market::printSellFiveList(int n)
{
    if (n < 0) {

        Order **so5 = op.getTopSellFive();
        for (int i = 0; i < stockNumber; i++) {
            cout << "[ " << i << " ] " << "卖五（手）" << endl;
            for (int j = 4; j >= 0; j--) {
                cout << so5[i][j].price << " : " << so5[i][j].number << endl;
            }
        }
        cout << endl;

    } else {

        if (n >= stockNumber) return;

        Order *so5 = op.getTopSellFive(n);
        cout << "[ " << n << " ] " << "卖五（手）" << endl;
        for (int j = 4; j >= 0; j--) {
            cout << so5[j].price << " : " << so5[j].number << endl;
        }
        cout << endl;

    }
}

void market::printBuyFiveList(int n)
{
    if (n < 0) {
        Order **bo5 = op.getTopBuyFive();
        for (int i = 0; i < stockNumber; i++) {
            cout << "[ " << i << " ] " << "买五（手）" << endl;
            for (int j = 0; j < 5; j++) {
                cout << bo5[i][j].price << " : " << bo5[i][j].number << endl;
            }
        }
        cout << endl;
    } else {

        if (n>= stockNumber) return;

        Order *bo5 = op.getTopBuyFive(n);
        cout << "[ " << n << " ] " << "买五（手）" << endl;
        for (int j = 0; j < 5; j++) {
            cout << bo5[j].price << " : " << bo5[j].number << endl;
        }
        cout << endl;
    }
}



const int market::getDateNow()
{
    return dateNow;
}

const int market::getTimeUnitNow()
{
    return timeUnitNow;
}

const int market::getStockNumber()
{
    return stockNumber;
}


//[0 - (stockNum-1)]   x   [0 - totalTimeUnits]
const int** market::getPrices()
{
    return (const int**)stockPricesRecord;
}

//[0 - (stockNum-1)]   x   [0 - totalTimeUnits]
const int** market::getVolumn()
{
    return (const int**)volumeRecord;
}

//[0 - (stockNum-1)]   x   [0 - totalTimeUnits]
const long** market::getVolumnFlow()
{
    return (const long**)volumeFlowReocrd;
}

