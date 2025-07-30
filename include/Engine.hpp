#ifndef _ENGINE_HPP
#define _ENGINE_HPP

#include "OrderBook.hpp"
#include <unordered_map>


class Engine {
    public:
        static std::unordered_map<std::string, OrderBook> order_books;


};




#endif
