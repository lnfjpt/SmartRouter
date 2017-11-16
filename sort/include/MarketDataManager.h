#ifndef MARKETDATAMANAGER_H
#define MARKETDATAMANAGER_H

#include <string>
using std::string;
#include "MarketDataList.h"
const int SYMBOL_NUM_MAX = 1000;

struct TableHead {
	int size;
	std::string *symbols;
	// A Lock
	TableHead() {
		size = 0;
		symbols = new std::string[SYMBOL_NUM_MAX];
	}
	~TableHead() {
		delete []symbols;
	}
};

void MarketDataManager() {
	// Record market data lists' ptrs in a table
	MarketDataList *table[SYMBOL_NUM_MAX];
	TableHead tableHead;

	// receive market data in the form (marketId, symbol, price, qty)
	int marketId = 0;
	string symbol = "";
	double price = 0.0;
	int qty = 0;

	// Index the list according to the symbol
	while (true) {
		// Lock tableHead
		int idx;
		for (idx = 0; idx < tableHead.size && tableHead.symbols[idx] != symbol; ++idx) {}
		if (idx == tableHead.size) {
			++tableHead.size;
			tableHead.symbols[idx] = symbol;
			// Unlock tableHead
			table[idx] = new MarketDataList;
		}
		// else Unlock tableHead

		// Lock the list in the table
		table[idx]->WriteMarketData(marketId, price, qty);
		// Unlock the list
	}

	// Clean
	for (int i = 0; i < tableHead.size; ++i) {
		delete table[i];
	}
}

#endif
