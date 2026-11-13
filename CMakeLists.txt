cmake_minimum_required(VERSION 3.16)

project(SimpleOrderBook VERSION 1.0.0 LANGUAGES CXX)

add_library(order_book
    src/order_book.cpp
)

target_include_directories(order_book
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_compile_features(order_book PUBLIC cxx_std_17)

add_executable(simple_order_book
    src/main.cpp
)
target_link_libraries(simple_order_book PRIVATE order_book)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(order_book PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(simple_order_book PRIVATE -Wall -Wextra -Wpedantic)
elseif(MSVC)
    target_compile_options(order_book PRIVATE /W4 /permissive-)
    target_compile_options(simple_order_book PRIVATE /W4 /permissive-)
endif()
