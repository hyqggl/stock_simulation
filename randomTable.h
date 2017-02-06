//
// Created by huyiqing on 2017/1/23.
//

#ifndef STOCK_SIMULATION_RANDOMTABLE_H
#define STOCK_SIMULATION_RANDOMTABLE_H

#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <map>
#include <iostream>

using std::pair;

class randomTable {
public:
    randomTable();
    ~randomTable();
    void generateGaussTable();
    double gaussrand();
    pair<int*, unsigned int*> getGaussOrderSample_byGroup(int n);
    pair<int*, unsigned int*> getGaussOrderSample_byNumber(int n);

    void printGeneratedGaussList(int n);

private:
    double gauss_V1, gauss_V2, gauss_S;
    int gauss_phase;
    int gaussTable_Num;
    int**          gaussTable_first;
    unsigned int** gaussTable_second;
    bool     gaussTableGened;
};


#endif //STOCK_SIMULATION_RANDOMTABLE_H
