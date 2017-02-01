//
// Created by huyiqing on 2017/1/23.
//

#include "agentOG.h"




agentOG::agentOG()
{

}

agentOG::~agentOG()
{

}

agentOG::stockHoldBasic::stockHoldBasic(int holderId, int stockId, int quantity, int cost, int aToSell)
:holderId(holderId), stockId(stockId), quantity(quantity), cost(cost), avaliableToSell(aToSell)
{

};