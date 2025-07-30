#include "PriceLevel.hpp"


void PriceLevel::AddOrder(Order &o) {
    orders.push(o);
}


Order PriceLevel::PopOrder(void) {
    Order o = orders.front();
    orders.pop();
    return o;
}