//
// Created by huyiqing on 2017/1/19.
//

#include "tradeRecord.h"




void tradeRecord::addRecord(int n, int time, int price, unsigned int number)
{
    if (counter[n] >= capacity)
    {
        //todo flush
        writeOut(n);
        counter[n] = 0;
    }
    record_time[n][counter[n]] = time;
    record_price[n][counter[n]] = price;
    record_number[n][counter[n]] = number;
    counter[n]++;
}

void tradeRecord::writeOut(int n)
{
    ofstream saveFile(direct + "smTest1.txt", ios_base::app);
    for (int i = 0; i < counter[n]; i++)
    {
        saveFile << record_time[n][i] << " " << record_price[n][i] << " " << record_number[n][i] << "\n";
    }
    saveFile.close();
}

tradeRecord::tradeRecord(int n, int capacity)
{
    direct = "/Users/huyiqing/";
    sNumber = n;
    this->capacity = capacity;
    counter       = new int[n];
    record_time   = new int*[n];
    record_price  = new int*[n];
    record_number = new unsigned int*[n];
    for (int i = 0; i < n; i++)
    {
        counter[i] = 0;
        record_time[i] = new int[capacity];
        record_price[i] = new int[capacity];
        record_number[i] = new unsigned int[capacity];
    }
}


tradeRecord::~tradeRecord()
{
    for (int i = 0; i < sNumber; i++)
    {
        writeOut(i);
        delete record_time[i];
        record_time[i] = NULL;
        delete record_price[i];
        record_price[i] = NULL;
        delete record_number[i];
        record_number[i] = NULL;
    }
    delete counter;
    counter = NULL;
    delete record_time;
    record_time = NULL;
    delete record_price;
    record_price = NULL;
    delete record_number;
    record_number = NULL;
}
