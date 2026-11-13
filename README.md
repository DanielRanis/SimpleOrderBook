# SimpleOrderBook

A C++17 limit order book for buy orders with prices in the inclusive range
`[100, 163]`. Orders at the same price are stored in arrival order. The best
bid is cached, and a 64-bit bitmap tracks non-empty price levels.

## Build and run

```sh
cmake -S . -B build
cmake --build build
./build/simple_order_book
```

The `order_book` library is declared in `include/order_book.hpp`; the example
program in `src/main.cpp` demonstrates adding, cancelling, and querying orders.
Adding an order with an invalid price, non-positive quantity, or duplicate ID
throws `std::invalid_argument`. Cancelling an unknown ID is a no-op, and
`getBestBid()` returns `-1` when no orders remain.
