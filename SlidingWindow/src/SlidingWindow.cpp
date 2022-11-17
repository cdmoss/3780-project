//
// Created by mbroughton on 11/11/22.
//

#include "../include/SlidingWindow.h"
#include <cassert>
#include <deque>
#include <cmath>
#include <iostream>
#include <algorithm>

SlidingWindow::SlidingWindow(unsigned int windowSize, unsigned int numOfFrames, unsigned int seqNumBits) {
    assert(windowSize <= pow(seqNumBits, 2));
    SlidingWindow::windowSize = windowSize;
    SlidingWindow::numOfFrames = numOfFrames;
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
    /**
     * Check to ensure seqNum is in the slidingWindow
     */
    assert(std::find(slidingWindow -> begin(), slidingWindow -> end(), seqNum) != slidingWindow -> end());

    while (slidingWindow -> front() != seqNum) {
        unsigned int lastSeqNum = slidingWindow -> back();
        /*
        numOfFrames--;
        if (numOfFrames == 0) {
            std::cout << "All frames sent successfully!" << std::endl;
            break;
        }
         */
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

std::deque<unsigned int> *SlidingWindow::getSlidingWindow() const {
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
    std::cout << "\n";
    for (auto it = d -> begin(); it != d -> end(); ++it) {
        std::cout << ' ' << *it;
    }
    std::cout << std::endl;
}