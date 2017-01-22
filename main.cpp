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
    int time = 0;
    tradeRecord tr(n, 5);
    marketOrderGenerator mog(n);
    int initialPrices[n];
    for (int i = 0; i < n; i++)
    {
        initialPrices[i] = 4800;
    }
    orderProcessor op(n);
    op.setOpenPrice(initialPrices);
    op.addBuyOrder(mog);
    op.addSellOrder(mog);

    const int* a = op.getPriceNRecord(++time, tr, false);
    for (int i = 0; i < n; i++)
    {
        cout<<a[i]<<" ";
    }
    cout<<endl;


    const map<int, unsigned int>* so = op.getUndoSellOrder();
    const map<int, unsigned int>* bo = op.getUndoBuyOrder();
    cout<<"Sell"<<endl;
    for (int i = 0; i < n; i++)
    {
        map<int, unsigned int>::const_reverse_iterator it;
        for (it = so[i].rbegin(); it != so[i].rend(); it++)
        {
            cout<<it->first<<" : "<<it->second<<endl;
        }
    }
    cout<<"Buy"<<endl;
    for (int i = 0; i < n; i++)
    {
        map<int, unsigned int>::const_reverse_iterator it;
        for (it = bo[i].rbegin(); it != bo[i].rend(); it++)
        {
            cout<<it->first<<" : "<<it->second<<endl;
        }
    }

    Order** so5 = op.getTopSellFive();
    Order** bo5 = op.getTopBuyFive();
    cout<<"Sell5"<<endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 4; j >= 0; j--)
        {
            cout<<so5[i][j].price<<" : "<<so5[i][j].number<<endl;
        }
    }

    cout<<"Buy5"<<endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout<<bo5[i][j].price<<" : "<<bo5[i][j].number<<endl;
        }
    }

    finish = clock();
    totalTime = (double_t)(finish - start) / CLOCKS_PER_SEC;
    cout<<totalTime;
    return 0;
}