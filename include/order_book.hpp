#ifndef ORDER_BOOK_HPP
#define ORDER_BOOK_HPP

#include <array>
#include <cstddef>
#include <cstdint>
#include <list>
#include <unordered_map>

class OrderBook {
public:
    static constexpr int MIN_PRICE = 100;
    static constexpr int MAX_PRICE = 163;

    void addOrder(int orderId, int price, int quantity);

    void cancelOrder(int orderId);

    // Returns -1 when the book is empty.
    int getBestBid() const noexcept;

    std::size_t orderCount() const noexcept;

private:
    struct Order {
        int id;
        int quantity;
    };

    using PriceLevel = std::list<Order>;

    struct OrderLocation {
        std::size_t priceIndex;
        PriceLevel::iterator order;
    };

    static constexpr std::size_t PRICE_LEVEL_COUNT = MAX_PRICE - MIN_PRICE + 1;

    static int highestSetBit(std::uint64_t bits) noexcept;

    std::array<PriceLevel, PRICE_LEVEL_COUNT> levels_;
    std::unordered_map<int, OrderLocation> orders_;
    std::uint64_t nonEmptyLevels_ = 0;
    int bestBid_ = -1;
};

#endif
