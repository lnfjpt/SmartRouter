// To Test
#include <string>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include "MarketDataList.h"
#include "MarketDataManager.h"
#include "OrderDecision.h"
#include "MarketInfo.h"


int main() {
    // Record market data lists' ptrs in a table
	MarketDataList *table[SYMBOL_NUM_MAX];
	TableHead tableHead;

	// receive market data in the form (marketId, symbol, price, qty)
	// Index the list according to the symbol
	const int N = 10;
	int marketIdS[N] 		= {1, 		1, 		1, 		1, 		1, 		2, 		1, 		1, 		1, 		0};
	std::string symbolS[N] 	= {"MS", 	"MS", 	"MS",	"FC",	"FC",	"MS",	"MS",	"MS",	"FC",	"FC"};
	double priceS[N]		= {5.5,		6.7,	5.0,	55.3,	56.5,	5.5,	5.0,	5.5,	58.3,	56.5};
	int qtyS[N]				= {200,		200,	200,	200,	200,	200,	0,		100,	200,	100};

	for (int i = 0; i < N; ++i) {
		int marketId = marketIdS[i];
		std::string symbol = symbolS[i];
		double price = priceS[i];
		int qty = qtyS[i];
		//
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
	// Test MarketDataManager
	for (int i = 0; i < tableHead.size; ++i) {
		cout << tableHead.symbols[i] << endl;
		for (table[i]->ListIdxInit(); table[i]->ListIdxValid(); table[i]->ListIdxNext()) {
			cout << MARKET_NAME[table[i]->GetIdxNodeMarketId()] << '\t' << table[i]->GetIdxNodeQty() << "@" << table[i]->GetIdxNodePrice() << endl;
		}
	}
	cout << endl;
	// Test OrderDecision
	while (true) {
		double price;
		int qty;
		std::string symbol;
		cin >> qty >> price >> symbol;
		if (qty == 0) break;
		Order order(Side::Buy, symbol, qty, price, TimeInForce::IOC);
		OrderDecision(order, tableHead, table);
	}

	// Clean
	for (int i = 0; i < tableHead.size; ++i) {
		delete table[i];
	}

	int t;
	cin >> t;
	return 0;
}
