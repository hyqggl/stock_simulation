//
// Created by huyiqing on 2017/1/16.
//

#include "market.h"

market::market(int n):stockNumber(n),dateNow(0)
{
    stockPricesRecord = new int*[stockNumber];
    volumeRecord      = new int*[stockNumber];
    volumeFlowReocrd = new long*[stockNumber];
    for (int i = 0; i < stockNumber; i++)
    {
        stockPricesRecord[i] = new int[totalTimeUnits];
        volumeRecord[i]      = new int[totalTimeUnits];
        volumeFlowReocrd[i] = new long[totalTimeUnits];
    }

}

market::~market()
{
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
}