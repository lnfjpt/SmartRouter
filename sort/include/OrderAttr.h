#ifndef ORDER_ATTR_H
#define ORDER_ATTR_H

enum class TimeInForce : char
{
    Day = '1',
    GTC = '2', 
    IOC = '3'
};

enum class Side : char
{
    Sell = '1', 
    Buy= '2'
};

enum class OrderStatus : char
{
    New = '0', 
    Partial = '1', 
    Filled = '2', 
    Rejected = '3', 
    Expired = '4'
};

enum class MsgType : char
{
    Single = 'D',
    Msg = '8'
};

#endif