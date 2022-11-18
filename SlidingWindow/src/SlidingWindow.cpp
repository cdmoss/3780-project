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
    delete this -> slidingWindow;
    this -> slidingWindow = nullptr;
}

unsigned int SlidingWindow::getWindowSize() const {
    return this -> windowSize;
}

void SlidingWindow::setWindowSize(unsigned int windowSize) {
    assert(windowSize <= pow(this -> seqNumBits, 2));
    this -> windowSize = windowSize;
    initializeSlidingWindow(windowSize);
}

unsigned int SlidingWindow::move(unsigned int seqNum) {
    assert(this -> slidingWindow != nullptr);
    /**
     * Check to ensure seqNum is in the slidingWindow
     */
    assert(std::find(this -> slidingWindow -> begin(), this -> slidingWindow -> end(), seqNum) != this -> slidingWindow -> end());

    unsigned int nextSeqNum;
    if (seqNum == this -> maxSeqNum) {
        nextSeqNum = 0;
    } else {
        nextSeqNum = seqNum + 1;
    }

    unsigned int movedCounter = 0;
    while (this -> slidingWindow -> front() != nextSeqNum) {
        movedCounter++;
        this -> slidingWindow -> pop_front();
        if (this -> getLastSeqNum() == this -> maxSeqNum) {
            this -> slidingWindow -> push_back(0);
        } else {
            this -> slidingWindow -> push_back(this -> getLastSeqNum() + 1);
        }
    }

    return movedCounter;
}

unsigned int SlidingWindow::getSeqNumBits() const {
    return this -> seqNumBits;
}

void SlidingWindow::setSeqNumBits(unsigned int seqNumBits) {
    assert(this -> windowSize <= pow(seqNumBits, 2));
    this -> seqNumBits = seqNumBits;
}

std::deque<unsigned int> *SlidingWindow::getSlidingWindow() {
    return this -> slidingWindow;
}

void SlidingWindow::initializeSlidingWindow(unsigned int windowSize) {
    if (this -> slidingWindow == nullptr) {
        this -> slidingWindow = new std::deque<unsigned int>;
    } else {
        this -> slidingWindow -> clear();
    }

    for (unsigned int i = 0; i < windowSize; i++) {
        this -> slidingWindow -> push_back(i);
    }
}

void SlidingWindow::printSlidingWindow(std::deque<unsigned int> *d) {
    assert(this -> slidingWindow != nullptr);
    std::cout << "\n";
    for (unsigned int & it : *d) {
        std::cout << ' ' << it;
    }
    std::cout << std::endl;
}

unsigned int SlidingWindow::getLastSeqNum() {
    assert(this -> slidingWindow != nullptr);
    return this -> slidingWindow -> back();
}

unsigned int SlidingWindow::getFirstSeqNum() {
    assert(this -> slidingWindow != nullptr);
    return this -> slidingWindow -> front();
}