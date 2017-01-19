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
    int n = 1000;
    marketOrderGenerator mog(n);
    vector<int> initialPrices;
    for (int i = 0; i < n; i++)
    {
        initialPrices.push_back(4800);
    }
    orderProcessor op(n, initialPrices);
    op.addBuyOrder(mog);
    op.addSellOrder(mog);

    auto a = op.getPriceNRecord2();
//    auto a = op.getPrice();
    for (int i = 0; i < a.size(); i++)
    {
        cout<<a[i]<<" ";
    }
    cout<<endl;
    auto so = op.getUndoSellOrder();
    auto bo = op.getUndoBuyOrder();
    cout<<"Sell"<<endl;
    for (int i = 0; i < so.size(); i++)
    {
        map<int, unsigned int>::reverse_iterator it;
        for (it = so[i].rbegin(); it != so[i].rend(); it++)
        {
            cout<<it->first<<" : "<<it->second<<endl;
        }
    }
    cout<<"Buy"<<endl;
    for (int i = 0; i < bo.size(); i++)
    {
        map<int, unsigned int>::reverse_iterator it;
        for (it = bo[i].rbegin(); it != bo[i].rend(); it++)
        {
            cout<<it->first<<" : "<<it->second<<endl;
        }
    }
    finish = clock();
    totalTime = (double_t)(finish - start) / CLOCKS_PER_SEC;
    cout<<totalTime;
    return 0;
}