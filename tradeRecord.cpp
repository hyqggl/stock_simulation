//
// Created by huyiqing on 2017/1/19.
//

#include <sstream>
#include <iostream>
#include "tradeRecord.h"

using std::cout;
using std::endl;
using std::stringstream;
using std::ofstream;
using std::ios;
using std::ios_base;


void tradeRecord::addRecord(int n, int date, int time, int price, unsigned int number)
{
    if (onUsing) {
        if (counter[n] >= capacity) {
            //todo flush
            writeOut(n);
            counter[n] = 0;
        }
        record_date[n][counter[n]] = date;
        record_time[n][counter[n]] = time;
        record_price[n][counter[n]] = price;
        record_number[n][counter[n]] = number;
        counter[n]++;
    }
}

void tradeRecord::writeOut(int n)
{
    if (!initialized) {
        std::cout << "Have not initialised the trade record." << std::endl;
        return;
    }
    if (onUsing) {
        //todo
        string st = direct + recordNameSet[n];
        ofstream saveFile(st, ios_base::app);
        for (int i = 0; i < counter[n]; i++) {
            saveFile << n << " "
                     << record_date[n][i] << " "
                     << record_time[n][i] << " "
                     << record_price[n][i] << " "
                     << record_number[n][i] << "\n";
        }
        saveFile.close();
    }
}

bool tradeRecord::initialize()
{
    if (onUsing) {
        stringstream ss;
        ss.clear();
        for (int i = 0; i < sNumber; i++) {
            ss << "Record_";
            ss << i;
            ss << ".txt";
            recordNameSet[i] = ss.str();
            ss.str("");
            ofstream iniF(direct + recordNameSet[i], ios::out);
            iniF.close();
        }
        initialized = true;
    }
    return initialized;
}


tradeRecord::tradeRecord(bool ou, int n, int capacity, string dir):onUsing(ou), sNumber(n),direct(dir)
,initialized(false)
{
    if (onUsing) {
        this->capacity = capacity;
        counter = new int[n];
        record_date = new int *[n];
        record_time = new int *[n];
        record_price = new int *[n];
        record_number = new unsigned int *[n];
        recordNameSet = new string[n];
        for (int i = 0; i < n; i++) {
            counter[i] = 0;
            record_date[i] = new int[capacity];
            record_time[i] = new int[capacity];
            record_price[i] = new int[capacity];
            record_number[i] = new unsigned int[capacity];
        }
        initialize();
    }
}


tradeRecord::~tradeRecord()
{
    if (onUsing) {
        for (int i = 0; i < sNumber; i++) {
            writeOut(i);
            delete record_date[i];
            record_date[i] = NULL;
            delete record_time[i];
            record_time[i] = NULL;
            delete record_price[i];
            record_price[i] = NULL;
            delete record_number[i];
            record_number[i] = NULL;
        }
        delete []counter;
        counter = NULL;
        delete record_date;
        record_date = NULL;
        delete record_time;
        record_time = NULL;
        delete record_price;
        record_price = NULL;
        delete record_number;
        record_number = NULL;
        delete[]recordNameSet;
        recordNameSet = NULL;
    }

    cout << "tradeRecord released." << endl;
}

