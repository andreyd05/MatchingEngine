#ifndef _ENGINE_HPP
#define _ENGINE_HPP

#include "../include/OrderBook.hpp"
#include <unordered_map>


class Engine {
    public:
        std::unordered_map<std::string, OrderBook> order_books;



};




#endif
