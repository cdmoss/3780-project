#include "../include/SlidingWindow.h"
#include <cassert>
#include <cmath>
#include <iostream>
#include <algorithm>

/**
* Constructor validates that max sequence num given num bits will not exceed window size,
* then sets windows size and calculates max sequence num from num bits and sets it, then initializes sliding window
* @param windowSize the maximum size of the sliding window
* @param seqNumBits the number of header bits used to store the sequence number
*/
SlidingWindow::SlidingWindow(unsigned int windowSize, unsigned int seqNumBits) {
    assert(windowSize <= pow(seqNumBits, 2));
    SlidingWindow::windowSize = windowSize;
    SlidingWindow::seqNumBits = seqNumBits;
    maxSeqNum = pow(seqNumBits, 2) - 1;
    initializeSlidingWindow(windowSize);
}

/**
 * Default constructor that uses default values for window size (4) and seqNumBits (7)
 */
SlidingWindow::SlidingWindow() {
    initializeSlidingWindow(windowSize);
}

SlidingWindow::~SlidingWindow() {
    delete this->slidingWindow;
    this->slidingWindow = nullptr;
}

unsigned int SlidingWindow::getWindowSize() const {
    return this->windowSize;
}

void SlidingWindow::setWindowSize(unsigned int windowSize) {
    assert(windowSize <= pow(this->seqNumBits, 2));
    this->windowSize = windowSize;
    initializeSlidingWindow(windowSize);
}

/**
 * Slides the window forward to the given sequence number
 * @param seqNum the seq number to slide the window to
 */
unsigned int SlidingWindow::move(unsigned int seqNum) {
    assert(this->slidingWindow != nullptr);
    /**
     * Check to ensure seqNum is in the slidingWindow
     */
    assert(std::find(this->slidingWindow->begin(), this->slidingWindow->end(), seqNum) != this->slidingWindow->end());

    // if given sequence number is the end of the window, wrap around to 0
    unsigned int nextSeqNum;
    if (seqNum == this->maxSeqNum) {
        nextSeqNum = 0;
    } else {
        nextSeqNum = seqNum + 1;
    }

    /*
    check each element in window starting at front.
    if element != seqNum, pop element and push the next in order sequence number on back, sliding the window forward
    */
    unsigned int movedCounter = 0;
    while (this->slidingWindow->front() != nextSeqNum) {
        movedCounter++;
        this->slidingWindow->pop_front();

        // if the last number in the window is the max seq num, push 0 on back to prepare for wrap around
        if (this->getLastSeqNum() == this->maxSeqNum) {
            this->slidingWindow->push_back(0);
        } else {
            this->slidingWindow->push_back(this->getLastSeqNum() + 1);
        }
    }

    return movedCounter;
}

unsigned int SlidingWindow::getSeqNumBits() const {
    return this->seqNumBits;
}

void SlidingWindow::setSeqNumBits(unsigned int seqNumBits) {
    assert(this->windowSize <= pow(seqNumBits, 2));
    this->seqNumBits = seqNumBits;
}

std::deque<unsigned int> *SlidingWindow::getSlidingWindow() {
    return this->slidingWindow;
}

/**
* Allocates new deque, fills it with ints from 0 - winSize - 1
*/
void SlidingWindow::initializeSlidingWindow(unsigned int windowSize) {
    if (this->slidingWindow == nullptr) {
        this->slidingWindow = new std::deque<unsigned int>;
    } else {
        this->slidingWindow->clear();
    }

    for (unsigned int i = 0; i < windowSize; i++) {
        this->slidingWindow->push_back(i);
    }
}

void SlidingWindow::printSlidingWindow() {
    assert(this->slidingWindow != nullptr);
    std::cout << "\n";
    for (unsigned int &it: *(this -> slidingWindow)) {
        std::cout << ' ' << it;
    }
    std::cout << std::endl;
}

unsigned int SlidingWindow::getLastSeqNum() {
    assert(this->slidingWindow != nullptr);
    return this->slidingWindow->back();
}

unsigned int SlidingWindow::getFirstSeqNum() {
    assert(this->slidingWindow != nullptr);
    return this->slidingWindow->front();
}