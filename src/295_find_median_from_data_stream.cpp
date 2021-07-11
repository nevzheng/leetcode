#include <iostream>
#include <queue>
/*
 * We will use priority queues to find the median in constant time, at the cost of O(log n) insertion
 * To do this we will maintain a Max heap containing elements less than the median
 * and a min heap containing elements greater than the median.
 * We will maintain the following invariant
 *
 * Given:
 * loCount := len(maxHeap);
 * hiCount := len(minHeap);
 * hiCount <= loCount && loCount-hiCount <= 1
 *
 * To query the median we can get the two values closest to the median in the max and min heap
 * The exact value of the median will depend on the parity total number of elements
 * If the number of elements is even, and the invariant is maintain we can just return
 * the value a top the max heap. Otherwise we can return the average.
 *
 * Follow Ups:
 * If all integer numbers from the stream are in the range [0, 100], how would you optimize your solution?
 * We can switch our data type to uint8_t, which will save memory.
 * Instead of two heaps we could maintain a single array with indices from 0-100 that stores the count of elements
 * As integers stream in we can increment and decrement counts, moving a median pointer
 * This should achieve constant memory and insertion time.
 *
 * If 99% of all integer numbers from the stream are in the range [0, 100], how would you optimize your solution?
 * You could hybridize the approaches. Use the array for in bound elements and a min and max heap for out of bound elements
 * complexity would vary but it would be really close to the table.
 */

using MaxHeap = std::priority_queue<int>;
using MinHeap = std::priority_queue<int, std::vector<int>, std::greater<>>;

class MedianFinder {
public:
    MaxHeap lo;
    MinHeap hi;
    /** initialize your data structure here. */
    MedianFinder() = default;

    void addNum(int num) {
        // Push into the correct heap
        num <= findMedian() ? lo.push(num) : hi.push(num);

        if (lo.size() > hi.size() && lo.size() - hi.size() > 1) {
            hi.push(lo.top());
            lo.pop();
        } else if (hi.size() > lo.size()) {
            lo.push(hi.top());
            hi.pop();
        }
    }

    double findMedian() const {
        if (lo.empty() && hi.empty()) {// Both Empty, return 0
            return 0;
        } else if (lo.size() == hi.size()) {// Even Parity
            return (lo.top() + hi.top()) / 2.;
        } else {// Else, lo.top() is median, guaranteed by invariant
            return lo.top();
        }
    }
};

int main() {
    MedianFinder mf;
    mf.addNum(1);
    mf.addNum(2);
    std::cout << mf.findMedian() << '\n';
    mf.addNum(3);
    std::cout << mf.findMedian() << '\n';

    return 0;
}
