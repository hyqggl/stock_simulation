//
// Created by huyiqing on 2017/1/15.
//

#include "marketOrderGenerator.h"




marketOrderGenerator::marketOrderGenerator()
{

}

marketOrderGenerator::~marketOrderGenerator()
{

}

vector<int*> marketOrderGenerator::generateOrder(vector<int*>& a)
{

    for (int j = 0; j <= sizeof(a.at(0)) / sizeof(int) / 2; j++)
    {
        a.at(0)[j] = j + 1;
    }
    for (int j = sizeof(a.at(0)) / sizeof(int) / 2 + 1; j <= sizeof(a.at(0)) / sizeof(int); j++)
    {
        a.at(0)[j] = 15 - j;
    }

    return a;
}

void marketOrderGenerator::generateRandomTable()
{

}