#ifndef MARKETDATANODE_H
#define MARKETDATANODE_H

struct MarketDataNode
{
	MarketDataNode(int mktId, double price, int qy):
		marketId(mktId), price(price), qty(qy)
	{}
	MarketDataNode():
	    prev(nullptr), next(nullptr)
    {}
	void ChangeQty(int newQty) {
		this->qty = newQty;
	}
	// pointers
	MarketDataNode *prev;
	MarketDataNode *next;

	// fix attributes
	int marketId;
	double price;
	int qty;

};

#endif
