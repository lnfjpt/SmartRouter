# -*- coding:utf-8 -*-

import random

symbols = ['Apple', 'Facebook', 'Twitter', 'Amazon', 'Microsoft', 'Google', 'Youtube', 'Yelp']
market = ['NYSE', 'IEX', 'NASDAQ']

for i in symbols:
    midPrice = random.randint(100,300)*100
    for j in market:
        sellPrice = []
        buyPrice = []
        numBuy = random.randint(10,20)
        numSell = random.randint(10,20)
        currentPrice = midPrice + random.randint(0,10)*100
        for k in range(numSell):
            quantity = random.randint(5+k*10,50+k*30)*100
            deltaPrice = random.randint(1,10)
            currentPrice +=  deltaPrice
            sellPrice.append([currentPrice, quantity])
        currentPrice = midPrice - random.randint(0,10)*100
        for k in range(numBuy):
            quantity = random.randint(5+k*10,50+k*30)*100
            deltaPrice = random.randint(1,10)
            currentPrice -=  deltaPrice
            buyPrice.append([currentPrice, quantity])
        f1 = open(i+'_'+j+'_sell', 'a')
        for k in sellPrice:
            f1.write(str(k[0]) + ' ' + str(k[1]) + '\n')
        f1.close()
        f2 = open(i+'_'+j+'_buy', 'a')
        for k in buyPrice:
            f2.write(str(k[0]) + ' ' + str(k[1]) + '\n')
        f2.close()