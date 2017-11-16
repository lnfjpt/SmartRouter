#ifndef MARKETDATALIST_H
#define MARKETDATALIST_H

#include <string>
#include "MarketDataNode.h"

class MarketDataList
{
public:
	MarketDataList() {
		listHead = new MarketDataNode;
	}
	~MarketDataList() {
		for (MarketDataNode *p = listHead; p != nullptr; ) {
			MarketDataNode *q = p;
			p = p->next;
			delete q;
		}
	}
	void WriteMarketData(int marketId, double price, int qty) {
		for (MarketDataNode *prev = listHead, *p = listHead->next; ; prev = p, p = p->next) {
			if (p == nullptr) { // Insert
				MarketDataNode *q = new MarketDataNode(marketId, price, qty);
				q->prev = prev, q->next = p;
				prev->next = q;
				break;
			}
			else if (p->price > price) { // Insert
				MarketDataNode *q = new MarketDataNode(marketId, price, qty);
				q->prev = prev, q->next = p;
				prev->next = q, p->prev = q;
				break;
			}
			else if (p->price == price && p->marketId == marketId) { // Just change
				if (qty == 0) { // Erase this data item
					prev->next = p->next;
					p->next->prev = prev;
					delete p;
				} else { // Change qty
					p->qty = qty;
				}
				break;
			}
		}
	}
	bool ListIdxValid() {
		return idxPtr == nullptr? false:true;
	}
	bool ListIdxInit() {
		idxPtr = listHead->next;
		return ListIdxValid();
	}
	bool ListIdxNext() {
		idxPtr = idxPtr->next;
		return ListIdxValid();
	}

	int GetIdxNodeMarketId() {
		return idxPtr->marketId;
	}
	double GetIdxNodePrice() {
		return idxPtr->price;
	}
	int GetIdxNodeQty() {
		return idxPtr->qty;
	}

	// std::string &GetListSymbol() {
	    // return symbol;
	// }
	
	// A Lock

private:
	// std::string symbol;
	MarketDataNode *listHead;
	// to index the list nodes
	MarketDataNode *idxPtr;

};

#endif
