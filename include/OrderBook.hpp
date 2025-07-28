#ifndef _ORDER_BOOK_HPP
#define _ORDER_BOOK_HPP


#include "PriceLevel.hpp"
#include <string>
#include <map>


class OrderBook {
    public:
        std::string name;
        std::map<double, PriceLevel> price_level;
};




#endif
