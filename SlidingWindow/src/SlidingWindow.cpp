//
// Created by mbroughton on 11/11/22.
//

#include "../include/SlidingWindow.h"
#include <cassert>
#include <deque>
#include <cmath>
#include <iostream>
#include <algorithm>

SlidingWindow::SlidingWindow(int windowSize, int numOfFrames, int seqNumBits) {
    assert(windowSize <= pow(seqNumBits, 2));
    SlidingWindow::windowSize = windowSize;
    SlidingWindow::numOfFrames = numOfFrames;
    SlidingWindow::seqNumBits = seqNumBits;
    maxSeqNum = pow(seqNumBits, 2) - 1;

    SlidingWindow::slidingWindow = new std::deque<int>;
    for (int i = 0; i < pow(seqNumBits, 2); i++) {
        slidingWindow -> push_front(i);
    }
}

SlidingWindow::SlidingWindow() {
    SlidingWindow::slidingWindow = new std::deque<int>;
    for (int i = 0; i < pow(seqNumBits, 2); i++) {
        slidingWindow -> push_front(i);
    }
}

SlidingWindow::~SlidingWindow() {
    delete slidingWindow;
}

int SlidingWindow::getWindowSize() const {
    return windowSize;
}

void SlidingWindow::setWindowSize(int windowSize) {
    assert(windowSize <= pow(seqNumBits, 2));
    SlidingWindow::windowSize = windowSize;
}

void SlidingWindow::move(int seqNum) {
    /**
     * Check to ensure seqNum is in the slidingWindow
     */
    //assert(std::find((*slidingWindow).begin(), (*slidingWindow).end(), seqNum) != (*slidingWindow).end());
    assert(std::find(slidingWindow -> begin(), slidingWindow -> end(), seqNum) != slidingWindow -> end());

    while (slidingWindow -> front() != seqNum) {   std::deque<int>::iterator *it;
        int lastSeqNum = slidingWindow -> back();
        numOfFrames--;
        if (numOfFrames == 0) {
            std::cout << "All frames sent successfully!" << std::endl;
            break;
        } else {
            slidingWindow->pop_front();
            if (lastSeqNum == maxSeqNum) {
                slidingWindow -> push_back(0);
            } else {
                slidingWindow -> push_back(lastSeqNum + 1);
            }
        }
    }
}

int SlidingWindow::getSeqNumBits() const {
    return seqNumBits;
}

void SlidingWindow::setSeqNumBits(int seqNumBits) {
    assert(windowSize <= pow(seqNumBits, 2));
    SlidingWindow::seqNumBits = seqNumBits;
}

std::deque<int> *SlidingWindow::getSlidingWindow() const {
    return slidingWindow;
}

void SlidingWindow::setSlidingWindow(std::deque<int> *slidingWindow) {
    SlidingWindow::slidingWindow = slidingWindow;
}
