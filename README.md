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

## Optional performance measurements

The benchmark is excluded from normal builds. Enable it with the
`ORDER_BOOK_ENABLE_PERFORMANCE_MEASUREMENTS` CMake option:

```sh
cmake -S . -B build-benchmark -DCMAKE_BUILD_TYPE=Release \
  -DORDER_BOOK_ENABLE_PERFORMANCE_MEASUREMENTS=ON
cmake --build build-benchmark --target order_book_benchmark
./build-benchmark/order_book_benchmark
```

Enabling the option downloads the pinned Google Benchmark v1.9.4 dependency
through CMake FetchContent. Google Benchmark reports the average time per add
and cancel operation over 100,000 operations. It also supports repetitions and
machine-readable output, for example:

```sh
./build-benchmark/order_book_benchmark --benchmark_repetitions=5 \
  --benchmark_report_aggregates_only=true \
  --benchmark_format=json --benchmark_out=benchmark-results.json
```

Use a Release build for meaningful performance measurements. Results also
depend on the machine, compiler, and system load.

The `order_book` library is declared in `include/order_book.hpp`; the example
program in `src/main.cpp` demonstrates adding, cancelling, and querying orders.
Adding an order with an invalid price, non-positive quantity, or duplicate ID
throws `std::invalid_argument`. Cancelling an unknown ID is a no-op, and
`getBestBid()` returns `-1` when no orders remain.
