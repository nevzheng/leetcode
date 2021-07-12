//
// Created by Nevin Zheng on 7/12/21.
//

#pragma once

#include <queue>


using MaxHeap = std::priority_queue<int>;
using MinHeap = std::priority_queue<int, std::vector<int>, std::greater<>>;

class MedianFinder {
public:
    MaxHeap lo;
    MinHeap hi;
    /** initialize your data structure here. */
    MedianFinder() = default;

    void addNum(int num);
    double findMedian() const;
};
