#include "order_book.hpp"

#include <benchmark/benchmark.h>

namespace {

constexpr int ORDER_COUNT = 100'000;
constexpr int PRICE_RANGE = OrderBook::MAX_PRICE - OrderBook::MIN_PRICE + 1;

int priceFor(int id) {
    return OrderBook::MIN_PRICE + id % PRICE_RANGE;
}

void addOrders(OrderBook& book) {
    for (int id = 0; id < ORDER_COUNT; ++id) {
        book.addOrder(id, priceFor(id), 1);
    }
}

class AddOrderFixture : public benchmark::Fixture {
protected:
    OrderBook book;

    void SetUp(const benchmark::State&) override {
        book = OrderBook{};
    }
};

BENCHMARK_DEFINE_F(AddOrderFixture, AddOrder)(benchmark::State& state) {
    int id = 0;
    for (auto _ : state) {
        book.addOrder(id, priceFor(id), 1);
        ++id;
    }
    state.SetItemsProcessed(state.iterations());
}
BENCHMARK_REGISTER_F(AddOrderFixture, AddOrder)->Iterations(ORDER_COUNT);

class CancelOrderFixture : public benchmark::Fixture {
protected:
    OrderBook book;

    void SetUp(const benchmark::State&) override {
        book = OrderBook{};
        addOrders(book);
    }
};

BENCHMARK_DEFINE_F(CancelOrderFixture, CancelOrder)(benchmark::State& state) {
    int id = 0;
    for (auto _ : state) {
        book.cancelOrder(id);
        ++id;
    }
    state.SetItemsProcessed(state.iterations());
}
BENCHMARK_REGISTER_F(CancelOrderFixture, CancelOrder)->Iterations(ORDER_COUNT);

} // namespace

BENCHMARK_MAIN();
