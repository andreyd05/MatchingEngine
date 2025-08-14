#include "runtime.hpp"
#include "Engine.hpp"
#include <mutex>
#include <thread>
#include <condition_variable>
#include <iostream>
#include <unistd.h>

static std::queue<IncomingOrder> buy_queue;
static std::queue<IncomingOrder> sell_queue;
static PriceLevel market_buy_book(0);

static std::mutex buy_queue_mutex;
static std::mutex market_buy_book_mutex;
static std::mutex sell_queue_mutex;
static std::mutex engine_mutex;
static bool run_threads = true;

// routines
void network_parser_thread_fn(void);
void buy_parser_thread_fn(void);
void sell_parser_thread_fn(void);

void send_order_back(uint64_t id);




int main() {
    
    
    






    std::thread network_parser(network_parser_thread_fn);
    std::thread buy_parser(buy_parser_thread_fn);
    std::thread sell_parser(sell_parser_thread_fn);



    IncomingOrder o;
    o.id = 1;
    o.name = "GOOG";
    o.order_type = OrderType::SELL;
    o.price = 1000;
    o.qty = 1;

    sell_queue_mutex.lock();
    printf("Placing sell order..\n");
    sell_queue.push(o);
    printf("Placed\n");
    sell_queue_mutex.unlock();

    usleep(1000000);
    




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

        if(buy_queue.empty()) {
            // mutex
            buy_queue_mutex.unlock();
            continue;
        }


        incoming_order = buy_queue.front();
        buy_queue.pop();

        // mutex
        buy_queue_mutex.unlock();
        engine_mutex.lock();

        OrderBook &book = Engine::order_books[incoming_order.name];
        std::map<double, PriceLevel, std::greater<double>> &price_map = book.sell_price_levels;
        
        // mutex
        engine_mutex.unlock();
        
        while(!price_map.empty() && incoming_order.qty > 0) {// handle running out of sell orders after this block
            book.book_mutex.lock();
            
            if(price_map.begin()->second.price > incoming_order.price) {
                // Add sell order to queue since all buy orders are under price
                Order _o;
                _o.id = incoming_order.id;
                _o.qty = incoming_order.qty;
                
                book.buy_price_levels[incoming_order.price].orders.push(_o);
                book.book_mutex.unlock();
                continue;
            }

            // book.name = incoming_order.name;
            
            while(!price_map.empty() && incoming_order.qty > 0) {
                PriceLevel &price_level = price_map.begin()->second;

                while(!price_level.orders.empty() && incoming_order.qty > 0) {
                    Order &sell_order = price_level.orders.front();

                    if(sell_order.qty >= incoming_order.qty) {
                        sell_order.qty -= incoming_order.qty;
                        send_order_back(incoming_order.id);
                        incoming_order.qty = 0;
                    } else {
                        incoming_order.qty -= sell_order.qty;
                        send_order_back(sell_order.id);
                        price_level.orders.pop();
                    }
                }
            }

            if(price_map.empty()) {

            }

            if(incoming_order.qty > 0) {
                // Add sell order to queue since no sell offers remain
                Order _o;
                _o.id = incoming_order.id;
                _o.qty = incoming_order.qty;
                book.sell_price_levels[incoming_order.price].orders.push(_o);

                book.book_mutex.unlock();
                continue;
            }
        }

        // mutex
        book.book_mutex.unlock();
    }

    return;
}

// Takes orders from sell queue and processes/matches them
void sell_parser_thread_fn(void) {
    IncomingOrder incoming_order;

    while(run_threads) {
        // mutex
        sell_queue_mutex.lock();

        if(sell_queue.empty()) {
            // mutex
            sell_queue_mutex.unlock();
            continue;
        }


        incoming_order = sell_queue.front();
        sell_queue.pop();

        // mutex
        sell_queue_mutex.unlock();            
        engine_mutex.lock();

        OrderBook &book = Engine::order_books[incoming_order.name];
        std::map<double, PriceLevel> &price_map = book.buy_price_levels;
        
        // mutex
        engine_mutex.unlock();
        
        while(!price_map.empty() && incoming_order.qty > 0) {
            book.book_mutex.lock();
            
            if(price_map.begin()->second.price < incoming_order.price) {
                // Add sell order to queue since all buy orders are under price
                Order _o;
                _o.id = incoming_order.id;
                _o.qty = incoming_order.qty;
                
                book.sell_price_levels[incoming_order.price].orders.push(_o);
                book.book_mutex.unlock();
                continue;
            }

            // book.name = incoming_order.name;
            
            while(!price_map.empty() && incoming_order.qty > 0) {
                PriceLevel &price_level = price_map.begin()->second;

                while(!price_level.orders.empty() && incoming_order.qty > 0) {
                    Order &sell_order = price_level.orders.front();

                    if(sell_order.qty >= incoming_order.qty) {
                        sell_order.qty -= incoming_order.qty;
                        send_order_back(incoming_order.id);
                        incoming_order.qty = 0;
                    } else {
                        incoming_order.qty -= sell_order.qty;
                        send_order_back(sell_order.id);
                        price_level.orders.pop();
                    }
                }
            }

            if(price_map.empty()) {

            }

            if(incoming_order.qty > 0) {
                // Add sell order to queue since no sell offers remain
                Order _o;
                _o.id = incoming_order.id;
                _o.qty = incoming_order.qty;

                book.sell_price_levels[incoming_order.price].orders.push(_o);

                book.book_mutex.unlock();
                continue;
            }
        }

        // mutex
        book.book_mutex.unlock();
    }

    return;
}

void send_order_back(uint64_t id) {
    return;
}
