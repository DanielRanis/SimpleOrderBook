cmake_minimum_required(VERSION 3.16)

project(SimpleOrderBook VERSION 1.0.0 LANGUAGES CXX)

option(ORDER_BOOK_ENABLE_PERFORMANCE_MEASUREMENTS
    "Build the opt-in order-book performance benchmark"
    OFF
)

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

if(ORDER_BOOK_ENABLE_PERFORMANCE_MEASUREMENTS)
    include(FetchContent)

    set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Disable Google Benchmark's own tests")
    FetchContent_Declare(
        google_benchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG v1.9.4
        GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(google_benchmark)

    add_executable(order_book_benchmark
        src/benchmark.cpp
    )
    target_link_libraries(order_book_benchmark PRIVATE order_book benchmark::benchmark)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(order_book PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(simple_order_book PRIVATE -Wall -Wextra -Wpedantic)
    if(TARGET order_book_benchmark)
        target_compile_options(order_book_benchmark PRIVATE -Wall -Wextra -Wpedantic)
    endif()
elseif(MSVC)
    target_compile_options(order_book PRIVATE /W4 /permissive-)
    target_compile_options(simple_order_book PRIVATE /W4 /permissive-)
    if(TARGET order_book_benchmark)
        target_compile_options(order_book_benchmark PRIVATE /W4 /permissive-)
    endif()
endif()
