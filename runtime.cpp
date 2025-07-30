#include "runtime.hpp"
#include "include/Engine.hpp"
#include <mutex>
#include <thread>
#include <condition_variable>

std::queue<IncomingOrder> buy_queue;
std::queue<IncomingOrder> sell_queue;
PriceLevel market_buy_book(0);

std::mutex buy_queue_mutex;
std::mutex market_buy_book_mutex;
std::mutex sell_queue_mutex;
static bool run_threads = true;


void request_parser_thread_fn(void);




int main() {
    
    
    






    std::thread network_parser(request_parser_thread_fn);
    std::thread buy_parser(buy_parser_thread_fn);
    std::thread sell_parser(sell_parser_thread_fn);



    network_parser.join();
    buy_parser.join();
    sell_parser.join();



    return 0;
}





// Takes all incoming requests and sorts it into the proper queue
void network_parser_thread_fn(void) {
    return;
}

// Takes orders from buy queue and processes/matches them
void buy_parser_thread_fn(void) {
    IncomingOrder order;

    while(run_threads) {
        // mutex acquire
        buy_queue_mutex.lock();
        if(!buy_queue.empty()) {
            order = buy_queue.front();
            buy_queue.pop();

            // mutex release
            buy_queue_mutex.unlock();

            








        } else {
            // mutex release
            buy_queue_mutex.unlock();
        }





    }
}

// Takes orders from sell queue and processes/matches them
void sell_parser_thread_fn(void) {
    return;
}
