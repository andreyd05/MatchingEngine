#include "include/Engine.hpp"
#include <mutex>
#include <thread>

std::queue<Order> buy_queue;
std::queue<Order> sell_queue;
PriceLevel market_buy_book(0);

std::mutex buy_queue_mutex;
std::mutex market_buy_book_mutex;
std::mutex sell_queue_mutex;


void request_parser_thread_fn(void);




int main() {
    
    
    






    std::thread parser(request_parser_thread_fn);



    parser.join();



    return 0;
}





// Takes all incoming requests and sorts it into the proper queue
void request_parser_thread_fn(void) {
    return;
}
