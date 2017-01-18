#include <iostream>
#include "random_demo.cpp"
#include "orderProcessor.h"
#include <fstream>
#include <vector>
#include <time.h>

using namespace std;

int main() {
    clock_t start, finish;
    double totalTime;
    start = clock();
//    random_main();
//    ofstream saveFile("ofsTest1.txt", ios::ate);
//    saveFile<<"new one!\n";
//    saveFile.close();
    int n = 1;
    marketOrderGenerator mog(n);
    vector<int> initialPrices;
    for (int i = 0; i < n; i++)
    {
        initialPrices.push_back(4800);
    }
    orderProcessor op(n, initialPrices);
    op.addBuyOrder(mog);
    op.addSellOrder(mog);
    auto a = op.getPrice();
    for (int i = 0; i < a.size(); i++)
    {
        cout<<a[i]<<" ";
    }
    cout<<endl;
    finish = clock();
    totalTime = (double_t)(finish - start) / CLOCKS_PER_SEC;
    cout<<totalTime;
    return 0;
}