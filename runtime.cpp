#include "runtime.hpp"
#include "Engine.hpp"
#include <mutex>
#include <thread>
#include <condition_variable>
#include <iostream>

std::queue<IncomingOrder> buy_queue;
std::queue<IncomingOrder> sell_queue;
PriceLevel market_buy_book(0);

std::mutex buy_queue_mutex;
std::mutex market_buy_book_mutex;
std::mutex sell_queue_mutex;
std::mutex engine_mutex;
bool run_threads = true;

// routines
void network_parser_thread_fn(void);
void buy_parser_thread_fn(void);
void sell_parser_thread_fn(void);

void send_order_back(uint64_t id);




int main() {
    
    
    






    std::thread network_parser(network_parser_thread_fn);
    std::thread buy_parser(buy_parser_thread_fn);
    std::thread sell_parser(sell_parser_thread_fn);



    run_threads = false;

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
    IncomingOrder incoming_order;

    while(run_threads) {
        // mutex
        buy_queue_mutex.lock();

        if(!buy_queue.empty()) {
            incoming_order = buy_queue.front();
            buy_queue.pop();

            // mutex
            buy_queue_mutex.unlock();            
            engine_mutex.lock();

            OrderBook &book = Engine::order_books[incoming_order.name];
            std::map<double, PriceLevel, std::greater<double>>& price_map = book.sell_price_levels;
            
            // mutex
            engine_mutex.unlock();
            book.book_mutex.lock();

            book.name = incoming_order.name;
            
            while(!price_map.empty() && incoming_order.qty > 0) {
                PriceLevel &price_level = price_map.begin()->second;

                if(price_level.price <= incoming_order.price) {
                    while(!price_level.orders.empty() && incoming_order.qty > 0) {
                        Order &sell_order = price_level.orders.front();

                        if(sell_order.qty >= incoming_order.qty) {
                            sell_order.qty -= incoming_order.qty;
                            incoming_order.qty = 0;
                            send_order_back(incoming_order.id);
                        } else {
                            incoming_order.qty -= sell_order.qty;
                            price_level.orders.pop();
                        }
                    }
                }
            }




            // mutex
            book.book_mutex.unlock();







        } else {
            // mutex
            buy_queue_mutex.unlock();
        }





    }
}

// Takes orders from sell queue and processes/matches them
void sell_parser_thread_fn(void) {
    return;
}

void send_order_back(uint64_t id) {
    return;
}
