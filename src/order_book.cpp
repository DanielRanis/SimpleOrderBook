#include "order_book.hpp"

#include <iterator>
#include <stdexcept>

void OrderBook::addOrder(int orderId, int price, int quantity) {
    if (price < MIN_PRICE || price > MAX_PRICE || quantity <= 0) {
        throw std::invalid_argument("price or quantity is outside the valid range");
    }
    if (orders_.find(orderId) != orders_.end()) {
        throw std::invalid_argument("duplicate order ID");
    }

    const auto priceIndex = price - MIN_PRICE;
    auto& level = levels_[static_cast<std::size_t>(priceIndex)];
    level.push_back({orderId, quantity});
    const auto order = std::prev(level.end());

    bool inserted = false;
    try {
        inserted = orders_.emplace(orderId, OrderLocation{priceIndex, order}).second;
    } catch (...) {
        level.pop_back();
        throw;
    }
    if (!inserted) {
        level.pop_back();
        throw std::logic_error("order ID became duplicated during insertion");
    }

    nonEmptyLevels_ |= (std::uint64_t{1} << priceIndex);
    if (price > bestBid_) {
        bestBid_ = price;
    }
}

void OrderBook::cancelOrder(int orderId) {
    const auto orderIt = orders_.find(orderId);
    if (orderIt == orders_.end()) {
        return;
    }

    const int priceIndex = orderIt->second.priceIndex;
    auto& level = levels_[static_cast<std::size_t>(priceIndex)];
    level.erase(orderIt->second.order);
    orders_.erase(orderIt);

    if (level.empty()) {
        nonEmptyLevels_ &= ~(std::uint64_t{1} << priceIndex);
        if (bestBid_ == priceIndex + MIN_PRICE) {
            const int highestIndex = highestSetBit(nonEmptyLevels_);
            bestBid_ = highestIndex == -1 ? -1 : highestIndex + MIN_PRICE;
        }
    }
}

int OrderBook::getBestBid() const noexcept {
    return bestBid_;
}

std::size_t OrderBook::orderCount() const noexcept {
    return orders_.size();
}

int OrderBook::highestSetBit(std::uint64_t bits) noexcept {
    if (bits == 0) {
        return -1;
    }

    int index = 0;
    while (bits >>= 1U) {
        ++index;
    }
    return index;
}
