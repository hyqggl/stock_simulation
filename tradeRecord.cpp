//
// Created by huyiqing on 2017/1/19.
//

#include "tradeRecord.h"

tradeRecord::tradeRecord(int n)
{
    for (int i = 0; i < n; i++)
    {
        vector<int> time;
        record_time.push_back(time);
        vector<int> price;
        record_price.push_back(price);
        vector<unsigned int> number;
        record_number.push_back(number);
    }
}

tradeRecord::~tradeRecord()
{

}

void tradeRecord::addRecord(int n, int time, int price, unsigned int number)
{
    record_time[n].push_back(time);
    record_price[n].push_back(price);
    record_number[n].push_back(number);
}