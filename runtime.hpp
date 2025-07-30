#ifndef _RUNTIME_HPP
#define _RUNTIME_HPP

#include <string>
#include <stdint.h>

enum class OrderType {BUY, SELL};


struct IncomingOrder {
    std::string name;
    OrderType order_type;
    double price;
    uint64_t id;
    uint32_t qty;
};




#endif
