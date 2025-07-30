#include "Engine.hpp"

std::unordered_map<std::string, OrderBook> Engine::order_books;


void Engine::AddBook(std::string n) {
    order_books.emplace(n, OrderBook(n));
}

bool Engine::BookExists(std::string n) {
    return order_books.count(n);
}