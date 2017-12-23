// To Test
#include <string>
#include <iostream>
#include <queue>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::queue;

#include "MarketDataList.h"
#include "MarketDataManager.h"
#include "MarketInfo.h"
#include "OrderDecision.h"
#include "OrderManage.h"


int main() {
    queue<string> ApQ, FaQ, TwQ, AmQ, MiQ, GoQ,
    YoQ, YeQ;
    std::thread taskAp(orderThread, ApQ);
    std::thread taskFa(orderThread, FaQ);
    std::thread taskTw(orderThread, TwQ);
    std::thread taskAm(orderThread, AmQ);
    std::thread taskMi(orderThread, MiQ);
    std::thread taskGo(orderThread, GoQ);
    std::thread taskYo(orderThread, YoQ);
    std::thread taskYe(orderThread, YeQ);
    taskAp.detach();
    taskFa.detach();
    taskTw.detach();
    taskAm.detach();
    taskMi.detach();
    taskGo.detach();
    taskYo.detach();
    taskYe.detach();
    // Record market data lists' ptrs in a table
	return 0;
}
