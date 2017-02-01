//
// Created by huyiqing on 2017/1/23.
//

#ifndef STOCK_SIMULATION_AGENTOG_H
#define STOCK_SIMULATION_AGENTOG_H

#include <map>

using namespace std;

//策略订单生成器
class agentOG {
public:

    agentOG();
    ~agentOG();

    //一天开始   初始化可卖


    //以下在一个时间单元内
    //调用后传出指令
    //调用得到结果


    //发出买订单      未成交订单++     可用资金-        买订单占用资金+，           记录+
    //发出卖订单      未成交订单++     持仓可卖--                                 记录
    //买订单成交(部分成交）      未成交订单--     订单占用资金--     持仓量++        记录+   税费
    //卖订单成交(部分成交）      未成交订单--     持仓--           可用资金++       记录+   税费
    //买订单撤销      未成交订单--     可用资金+        买订单占用资金-             记录
    //卖订单撤销      没成交订单--      持仓可卖++                                记录


    //一天结束时撤销所有未成交订单
    //结算



    class stockHoldBasic
    {
        stockHoldBasic(int holderId, int stockId, int quantity, int cost, int aToSell);
    public:
        int holderId;       //持有人id
        int stockId;        //股票ID
        int quantity;       //持仓量
        int cost;           //总成本
        int avaliableToSell;//可卖
    };

    //                  买卖方向    量    结果    订单完结时间
    class orderBasic
    {
        orderBasic();
    public:
        int issueDate;           //日期
        int issueTimeUnit;       //时间点(发出)
        int manID;               //发出者id
        int orderID;             //订单id
        int stockID;             //股票ID
        bool buyOrSell;          //    1 buy    ,   0 sell
        int quantity;
        bool success;       // 0 no,  1 yes
        int finishTimeUnit;
    };

private:
    int holderId;
    map<int, stockHoldBasic>  stockHold; //持仓    id - o
    //未成交买订单            orderId,
    //未成交卖订单
    long cashOccupied;        //订单占用资金
    long cashAvaliable;       //可用资金
    //订单记录
    //持仓记录
    long asset;               //总资产
    double stampTaxRate;     //印花税率
    double commission_basic;
    int    commission_multi;
};


#endif //STOCK_SIMULATION_AGENTOG_H
