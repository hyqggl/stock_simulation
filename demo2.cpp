//
// Created by huyiqing on 2017/1/16.
//
//中国银行股票投资回报与风险分析  -by Freddy
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;
vector<double> x;


double mx_fun(vector<double> x, double mx)
{ mx=0.0;
    for (int i=0;i<x.size();i++){
        mx+=x[i]/x.size();
    }
    return mx;
}

double vx_fun(vector<double> x, double vx, double mx)
{ vx=0.0;
    for (int i=0;i<x.size();i++){
        vx+=pow(x[i]- mx_fun(x,mx),2)/(x.size()-1);
    }
    return vx;
}



int main(){
    ifstream source1("bank of china.txt");

    double a;
    if (source1.is_open()){
        while(!source1.eof()){
            source1 >> a;
            x.push_back(a);
        }
        source1.close();
    }
    double beta=0.0,mx=0.0, my=0.0,vx=0.0,vy=0.0;


    double mean= mx_fun(x, mx);
    double var=vx_fun(x,vx, mx);


    double sdv=sqrt(var);

    cout<< "The average return of Bank of china is ： " << mean<<endl;
    cout<<"The volatility（standard deviation） of Bank of china is ： "<< sdv <<endl;



    return 0;

}