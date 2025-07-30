#ifndef _PRICE_LEVEL_HPP
#define _PRICE_LEVEL_HPP


#include "Order.hpp"
#include <queue>



class PriceLevel {
    public:
        PriceLevel(double p): price(p) {};

        double price;
        std::queue<Order> orders;

        void AddOrder(Order &o);
        Order PopOrder(void);

};







#endif
