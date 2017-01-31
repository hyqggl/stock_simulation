//
// Created by huyiqing on 2017/1/23.
//

#ifndef STOCK_SIMULATION_AGENTOG_H
#define STOCK_SIMULATION_AGENTOG_H

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
    //买订单成交(部分成交）      未成交订单--     订单占用资金--     持仓量++                 记录+
    //卖订单成交(部分成交）      未成交订单--     持仓--           可用资金++                记录+
    //买订单撤销      未成交订单--     可用资金+        买订单占用资金-             记录
    //卖订单撤销      没成交订单--      持仓可卖++                                记录


    //一天结束时撤销所有未成交订单
    //结算


    class stockHold
    {
    public:
        stockHold();
    private:
        int a;
    };


private:
    //持仓         持有人id， 股票ID, 持仓量， 总成本， 可卖
    //未成交买订单
    //未成交卖订单
    //买订单占用资金
    //可用资金
    //订单记录    日期   时间点(发出)   发出者     ID   买卖方向    量    结果    订单完结时间
    //持仓记录
    //总资产
};


#endif //STOCK_SIMULATION_AGENTOG_H
