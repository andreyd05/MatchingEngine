#include "PriceLevel.hpp"


void PriceLevel::AddOrder(Order &o) {
    orders.push(o);
}


Order PriceLevel::GetOrder(void) {
    Order o = orders.front();
    orders.pop();
    return o;
}