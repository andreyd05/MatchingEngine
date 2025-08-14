#ifndef _PRICE_LEVEL_HPP
#define _PRICE_LEVEL_HPP


#include "Order.hpp"
#include <queue>
#include <stdio.h>



class PriceLevel {
    public:
        PriceLevel() {};
        PriceLevel(double p): price(p) {};

        double price;
        std::queue<Order> orders;

        void AddOrder(Order &o);
        Order GetOrder(void);

};







#endif
