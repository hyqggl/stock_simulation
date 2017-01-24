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

using namespace std;

class randomTable {
public:
    randomTable();
    ~randomTable();
    void generateGaussTable();
    double gaussrand();

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
