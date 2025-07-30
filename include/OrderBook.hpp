#ifndef _ORDER_BOOK_HPP
#define _ORDER_BOOK_HPP


#include "PriceLevel.hpp"
#include <string>
#include <map>
#include <mutex>


class OrderBook {
    public:
        OrderBook(std::string n): name(n) {};

        std::string name;
        std::map<double, PriceLevel> buy_price_levels;
        std::map<double, PriceLevel, std::greater<double>> sell_price_levels;
        std::mutex book_mutex;

        


};




#endif
