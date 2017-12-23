// To Test
#include <string>
#include <iostream>
#include <queue>
#include <string>
#include <thread>
#include <fstream> 

using std::string;
using std::ifstream;
using std::queue;

/* All symbols:
    Apple
    Facebook
    Twitter
    Amazon
    Microsoft
    Google
    Youtube
    Yelp

    FIX message:
        order_id, price, qty, symbol, side
*/



void sendMessage(int market, int symbols, int side, long price, long qty, long **allPrice[3][8][2], int state)
{
    return;
}

void bookingHandle(int market, int symbols, int side, long price, long qty, long **allPrice[3][8][2])
{
    int length, remainQty;
    length = allPrice[market][symbols][side][0][0];
    remainQty = qty;
    for (int i=0; i<length; i++)
    {
        if (side == 0)
            if (allPrice[market][symbols][side][i][0]<=price)
            {
                if (remainQty>allPrice[market][symbols][side][i][1])
                {
                    remainQty -= allPrice[market][symbols][side][i][1];
                    sendMessage(market, symbols, side, allPrice[market][symbols][side][i][0], allPrice[market][symbols][side][i][1], allPrice, 0);
                    allPrice[market][symbols][side][i][1] = 0;
                }
                else
                {
                    sendMessage(market, symbols, side, allPrice[market][symbols][side][i][0], remainQty, allPrice, 0);
                    allPrice[market][symbols][side][i][1] -= remainQty;
                    remainQty = 0;
                }
            }
        if (side == 1)
            if (allPrice[market][symbols][side][i][0]>=price)
            {
                if (remainQty>allPrice[market][symbols][side][i][1])
                {
                    remainQty -= allPrice[market][symbols][side][i][1];
                    sendMessage(market, symbols, side, allPrice[market][symbols][side][i][0], allPrice[market][symbols][side][i][1], allPrice, 0);
                    allPrice[market][symbols][side][i][1] = 0;
                }
                else
                {
                    sendMessage(market, symbols, side, allPrice[market][symbols][side][i][0], remainQty, allPrice, 0);
                    allPrice[market][symbols][side][i][1] -= remainQty;
                    remainQty = 0;
                }
            }
        if (remainQty == 0)
            break;
    }
    if (remainQty)
        std::cout<<"failed"<<std::endl;
    return;
}

int main() 
{
    // Initial the price of symbols in each market
    long **allPrice[3][8][2]; //market;symbol;side;
    string market[3] = {"NYSE", "IEX", "NASDAQ"};
    string symbols[8] = {"Apple", "Facebook", "Twitter", "Amazon", "Microsoft", "Google", "Youtube", "Yelp"};
    string side[2] = {"sell","buy"};
    ifstream infile;
    for (int i = 0; i<3; i++)
        for (int j = 0; j<8; j++)
            for (int k = 0; k<2; k++)
            {
                string content;
                infile.open("../price/"+symbols[j]+"_"+market[i]+"_"+side[k]);
                queue<string> price;
                while(std::getline(infile,content))
                    price.push(content);
                infile.close();
                int length;
                length = price.size();
                allPrice[i][j][k] = new long*[length+1];
                for (int l=0; l<length+1; l++)
                    allPrice[i][j][k][l] = new long[2];
                allPrice[i][j][k][0][0] = allPrice[i][j][k][1][0] = length;
                int index = 1;
                long priceSymbol, qty;
                while(!price.empty())
                {
                    content = price.front();
                    priceSymbol = std::stol(content.substr(0, content.find(' ')));
                    qty = std::stol(content.substr(content.find(' ')+1, content.size()-content.find(' ')-1));
                    allPrice[i][j][k][index][0] = priceSymbol;
                    allPrice[i][j][k][index][1] = qty;
                    price.pop();
                    index++;
                }
                //std::cout<<length<<std::endl;
            }
    //symbolsTrade(0, 3, 1, 23904, 1000, allPrice);
    for (int i = 0; i<3; i++)
        for (int j = 0; j<8; j++)
            for (int k = 0; k<2; k++)
            {
                for (int l=0; l < 10; l++)
                    delete []allPrice[i][j][k][l];
                delete []allPrice[i][j][k];
            } 
	return 0;
}
