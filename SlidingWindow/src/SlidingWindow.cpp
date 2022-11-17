//
// Created by mbroughton on 11/11/22.
//

#include "../include/SlidingWindow.h"
#include <cassert>
#include <cmath>
#include <iostream>
#include <algorithm>

SlidingWindow::SlidingWindow(unsigned int windowSize, unsigned int seqNumBits) {
    assert(windowSize <= pow(seqNumBits, 2));
    SlidingWindow::windowSize = windowSize;
    SlidingWindow::seqNumBits = seqNumBits;
    maxSeqNum = pow(seqNumBits, 2) - 1;
    initializeSlidingWindow(windowSize);
}

SlidingWindow::SlidingWindow() {
    initializeSlidingWindow(windowSize);
}

SlidingWindow::~SlidingWindow() {
    delete slidingWindow;
    slidingWindow = nullptr;
}

unsigned int SlidingWindow::getWindowSize() const {
    return windowSize;
}

void SlidingWindow::setWindowSize(unsigned int windowSize) {
    assert(windowSize <= pow(seqNumBits, 2));
    SlidingWindow::windowSize = windowSize;
    initializeSlidingWindow(windowSize);
}

void SlidingWindow::move(unsigned int seqNum) {
    assert(slidingWindow != nullptr);
    /**
     * Check to ensure seqNum is in the slidingWindow
     */
    assert(std::find(slidingWindow -> begin(), slidingWindow -> end(), seqNum) != slidingWindow -> end());

    while (slidingWindow -> front() != seqNum) {
        unsigned int lastSeqNum = slidingWindow -> back();
        slidingWindow -> pop_front();
        if (lastSeqNum == maxSeqNum) {
            slidingWindow -> push_back(0);
        } else {
            slidingWindow -> push_back(lastSeqNum + 1);
        }
    }
}

unsigned int SlidingWindow::getSeqNumBits() const {
    return seqNumBits;
}

void SlidingWindow::setSeqNumBits(unsigned int seqNumBits) {
    assert(windowSize <= pow(seqNumBits, 2));
    SlidingWindow::seqNumBits = seqNumBits;
}

std::deque<unsigned int> *SlidingWindow::getSlidingWindow() {
    return slidingWindow;
}

void SlidingWindow::initializeSlidingWindow(unsigned int windowSize) {
    if (slidingWindow == nullptr) {
        slidingWindow = new std::deque<unsigned int>;
    } else {
        slidingWindow -> clear();
    }

    for (unsigned int i = 0; i < windowSize; i++) {
        slidingWindow -> push_back(i);
    }
}

void SlidingWindow::printSlidingWindow(std::deque<unsigned int> *d) {
    assert(slidingWindow != nullptr);
    std::cout << "\n";
    for (auto it = d -> begin(); it != d -> end(); ++it) {
        std::cout << ' ' << *it;
    }
    std::cout << std::endl;
}

unsigned int SlidingWindow::getLastSeqNum() {
    assert(slidingWindow != nullptr);
    return lastSeqNum;
}