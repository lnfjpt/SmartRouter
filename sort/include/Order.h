#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <string>

#include "OrderAttr.h"

class Order
{
    public:
        Order(Side sideInput, std::string symbolInput, int orderQtyInput, double priceInput,
            TimeInForce timeInforceInput)
        {
            side = sideInput;
            symbol = symbolInput;
            orderQty = orderQtyInput;
            price = priceInput;
            timeInforce = timeInforceInput;
            cumQty = 0;
            orderStatus = OrderStatus::New;
            return;
        }

        explicit Order(const Order & o)
        {
            side = o.side;
            symbol = o.symbol;
            orderQty = o.orderQty;
            price = o.price;
            timeInforce = o.timeInforce;
            cumQty = 0;
            orderStatus = OrderStatus::New;
            return;
        }

        int leavesQty() const
        {
            return orderQty - cumQty;
        }

        bool isTermin() const
        {
            if (leavesQty() == 0)
                return true;
            return false;
        }

        std::string getSymbol() const
        {
            return symbol;
        }
        double getPrice() const {
            return price;
        }
        int getQty() const {
            return orderQty;
        }

        void setQty(int newQty)
        {
            orderQty = newQty;
            return;
        }
    private:
        // --- attribute of fix ---
        Side            side;               //54=1(buy), =2(sell)
        std::string     symbol;             //55 symbol
        int             orderQty;           //38 quantity
        double          price;              //44 price
        TimeInForce     timeInforce;        //59
        MsgType         msgType;            //35

        int             cumQty;             //filled quantity
        OrderStatus     orderStatus;        //status of order
};

#endif
