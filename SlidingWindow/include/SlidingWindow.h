//
// Created by mbroughton on 11/11/22.
//

#ifndef SLIDINGWINDOW_SLIDINGWINDOW_H
#define SLIDINGWINDOW_SLIDINGWINDOW_H

#include <deque>

class SlidingWindow {
private:
    int windowSize{4};
    std::deque<int> *slidingWindow;

private:
    int numOfFrames{255};
    int seqNumBits{3};
    int maxSeqNum{7};

public:
    SlidingWindow(int windowSize, int numOfFrames, int seqNumBits);

    SlidingWindow();

    virtual ~SlidingWindow();

    int getWindowSize() const;

    void setWindowSize(int windowSize);

    int getSeqNumBits() const;

    void setSeqNumBits(int seqNumBits);

    void move(int seqNum);

    std::deque<int> *getSlidingWindow() const;

    void setSlidingWindow(std::deque<int> *slidingWindow);
};

#endif //SLIDINGWINDOW_SLIDINGWINDOW_H
