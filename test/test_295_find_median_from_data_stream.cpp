//
// Created by Nevin Zheng on 7/12/21.
//

#include <catch2/catch.hpp>
#include "295_find_median_from_data_stream.hpp"

TEST_CASE("test_295_example_1") {
    MedianFinder mf;
    mf.addNum(1);
    mf.addNum(2);
    REQUIRE(mf.findMedian() == 1.5);
    mf.addNum(3);
    REQUIRE(mf.findMedian() == 2.0);
}