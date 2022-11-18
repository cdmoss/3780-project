//
// Created by mbroughton on 11/11/22.
//

#ifndef SLIDINGWINDOW_SLIDINGWINDOW_H
#define SLIDINGWINDOW_SLIDINGWINDOW_H

#include <deque>

class SlidingWindow {
private:
    unsigned int windowSize{4};
    std::deque<unsigned int> *slidingWindow = nullptr;
    unsigned int seqNumBits{3};
    unsigned int maxSeqNum{7};

    void initializeSlidingWindow(unsigned int windowSize);

public:
    SlidingWindow(unsigned int windowSize, unsigned int seqNumBits);

    SlidingWindow();

    virtual ~SlidingWindow();

    unsigned int getWindowSize() const;

    void setWindowSize(unsigned int windowSize);

    unsigned int getSeqNumBits() const;

    void setSeqNumBits(unsigned int seqNumBits);

    unsigned int move(unsigned int seqNum);

    std::deque<unsigned int> *getSlidingWindow();

    void printSlidingWindow(std::deque<unsigned int> *d);

    unsigned int getLastSeqNum();

    unsigned int getFirstSeqNum();
};

#endif //SLIDINGWINDOW_SLIDINGWINDOW_H
