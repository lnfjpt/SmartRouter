#ifndef ORDERDECISION_H
#define ORDERDECISION_H

// To Test
#include <iostream>
using std::cout;
#include <string>
using std::string;

#include "Order.h"
#include "MarketDataManager.h"
#include "MarketInfo.h"

struct TradeBuf {
	double price;
	int qty;
	int marketId;
};

int ProcessTradeBuf(TradeBuf *tradeBuf, int bufIdx, int leftQty, double buyPrice, string &symbol) {
	int totQty = 0;
	for (int i = 0; i <= bufIdx; ++i) {
		totQty += tradeBuf[i].qty;
	}
	int tmpLeftQty = leftQty;
	for (int i = 0; i <= bufIdx; ++i) {
		int tradeQty = (leftQty*tradeBuf[i].qty)/totQty;
		int remainder = tradeQty%100;
		tradeQty = remainder == 0? tradeQty:(tradeQty - remainder + 100);
		tradeQty = tradeQty < tmpLeftQty? tradeQty:tmpLeftQty;
		tradeQty = tradeQty < tradeBuf[i].qty? tradeQty:tradeBuf[i].qty;
		tmpLeftQty -= tradeQty;
		// Send trade message
		// To Test
		cout << "BUY " << tradeQty << " " << symbol << "@" << tradeBuf[i].price << " FROM " << MARKET_NAME[tradeBuf[i].marketId] << '\n';
	}
	return tmpLeftQty;
}

void OrderDecision(Order &order, TableHead &tableHead, MarketDataList *table[]) {
	string symbol = order.getSymbol();
	// Get the marketDataList's index in table according to the symbol
	int idx = 0;
	while (true) {
		// Lock tableHead
		int tableSize = tableHead.size;
		for (; idx < tableSize && tableHead.symbols[idx] != symbol; ++idx) {}
		// Unlock tableHead
		if (idx < tableSize) break;
	}

	double price = order.getPrice();
	int leftQty = order.getQty();
	TradeBuf tradeBuf[MARKET_N_MAX];

	// Just one pass
	int bufIdx = -1;
	int tmpLeftQty = leftQty;
	// Lock table[idx]
	for (table[idx]->ListIdxInit(); table[idx]->ListIdxValid(); table[idx]->ListIdxNext()) {
		if (table[idx]->GetIdxNodePrice() <= price) { // trade may happen
			// Greedy method
			if (bufIdx < 0 || tradeBuf[bufIdx].price == table[idx]->GetIdxNodePrice()) { // append to the buf
				++bufIdx;
				tradeBuf[bufIdx].price = table[idx]->GetIdxNodePrice();
				tradeBuf[bufIdx].qty = table[idx]->GetIdxNodeQty();
				tradeBuf[bufIdx].marketId = table[idx]->GetIdxNodeMarketId();
			} else {
				// process the previous trade chance
				tmpLeftQty = ProcessTradeBuf(tradeBuf, bufIdx, tmpLeftQty, price, symbol);
				// refresh the tradeBuf
				bufIdx = 0;
				tradeBuf[bufIdx].price = table[idx]->GetIdxNodePrice();
				tradeBuf[bufIdx].qty = table[idx]->GetIdxNodeQty();
				tradeBuf[bufIdx].marketId = table[idx]->GetIdxNodeMarketId();
			}
		} else {
			break;
		}
	}
	// process the left trade chance
	tmpLeftQty = ProcessTradeBuf(tradeBuf, bufIdx, tmpLeftQty, price, symbol);
	// Unlock table[idx]

	// // listen the trade results from markets and update order leftQty
}

#endif
