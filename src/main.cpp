#include "order_book.hpp"

#include <iostream>

int main() {
    OrderBook book;

    book.addOrder(101, 100, 10);
    book.addOrder(102, 105, 5);
    book.addOrder(103, 105, 7);

    std::cout << "Best bid: " << book.getBestBid() << '\n';
    std::cout << "Open orders: " << book.orderCount() << '\n';

    book.cancelOrder(102);
    std::cout << "Best bid after cancelling order 102: "
              << book.getBestBid() << '\n';

    book.cancelOrder(103);
    std::cout << "Best bid after cancelling order 103: "
              << book.getBestBid() << '\n';
}
