#ifndef ORDERMANAGE_H
#define ORDERMANAGE_H

#include <thread>
#include <iostream>
#include <queue>
#include <string>

using std::string;
using std::queue;

#include "OrderDcision.h"
#include "log-epoll.h"

void orderThread(queue<string> symbolQueue)
{
    while(true):
        if(symbolQueue.empty()):
            continue;
        order = symbolQueue.front();
        symbolQueue.pop();
        if(order == "exit"):
            break;
        else:
            continue;
    return;
}

#endif
