#include "../include/SlidingWindow.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>

/**
 * Constructor validates that max sequence num given num bits will not exceed
 * window size, then sets windows size and calculates max sequence num from num
 * bits and sets it, then initializes sliding window
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
 * Default constructor that uses default values for window size (4) and
 * seqNumBits (7)
 */
SlidingWindow::SlidingWindow() { initializeSlidingWindow(windowSize); }

SlidingWindow::~SlidingWindow() {
  for (int i = 0; i < slidingWindow.size(); ++i) {
    delete slidingWindow[i];
  }

  slidingWindow.clear();
}

unsigned int SlidingWindow::getWindowSize() const { return this->windowSize; }

void SlidingWindow::setWindowSize(unsigned int windowSize) {
  assert(windowSize <= pow(this->seqNumBits, 2));
  this->windowSize = windowSize;
  initializeSlidingWindow(windowSize);
}

unsigned int SlidingWindow::windowContainsSeq(unsigned int seqNum) {
    for (auto el : slidingWindow) {
        if (el->seqNum == seqNum) {
            return true;
            break;
        }
    }

    return false;
}

/**
 * Slides the window forward to the given sequence number that is 1 past the given sequence number
 * @param seqNum the seq number to slide the window to
 */
unsigned int SlidingWindow::move(unsigned int seqNum) {
  if (!windowContainsSeq(seqNum)) {
    std::cout << "SlidingWindow: Can't move seqNum outside of window";
    return 0;
  }

  // if given sequence number is the end of the window, wrap around to 0
  unsigned int nextSeqNum;
  if (seqNum == maxSeqNum) {
    nextSeqNum = 0;
  } else {
    nextSeqNum = seqNum + 1;
  }

  /*
  check each element in window starting at front.
  if element != seqNum, pop element and push the next in order sequence number
  on back, sliding the window forward
  */
  unsigned int movedCounter = 0;
  while (slidingWindow.front()->seqNum != nextSeqNum) {
    movedCounter++;
    delete slidingWindow.front();
    slidingWindow.pop_front();
    // if the last number in the window is the max seq num, push 0 on back to
    // prepare for wrap around

    unsigned lastSeqInWindow = getLast()->seqNum;

    if (lastSeqInWindow == maxSeqNum) {
      slidingWindow.push_back(new WindowElement{0, false});
    } else {
      slidingWindow.push_back(new WindowElement{lastSeqInWindow + 1, false});
    }
  }

  return movedCounter;
}

unsigned SlidingWindow::sendNext() {
  for (auto el : slidingWindow) {
    if (!el->sent) {
      el->sent = true;
      return el->seqNum;
    }
  }

  return -1;
}

unsigned int SlidingWindow::getSeqNumBits() const { return this->seqNumBits; }

void SlidingWindow::setSeqNumBits(unsigned int seqNumBits) {
  assert(this->windowSize <= pow(seqNumBits, 2));
  this->seqNumBits = seqNumBits;
}

std::deque<WindowElement *> SlidingWindow::getSlidingWindow() {
  return slidingWindow;
}

/**
 * Allocates new deque, fills it with ints from 0 - winSize - 1
 */
void SlidingWindow::initializeSlidingWindow(unsigned int windowSize) {
  for (int i = 0; i < slidingWindow.size(); ++i) {
    delete slidingWindow[i];
  }

  slidingWindow.clear();

  for (unsigned int i = 0; i < windowSize; i++) {
    slidingWindow.push_back(new WindowElement{i, false});
  }
}

// void SlidingWindow::printSlidingWindow(std::deque<unsigned int> *d) {
//   assert(this->slidingWindow != nullptr);
//   std::cout << "\n";
//   for (unsigned int &it : *d) {
//     std::cout << ' ' << it;
//   }
//   std::cout << std::endl;
// }

WindowElement *SlidingWindow::getLast() const {
  assert(slidingWindow.size() != 0);
  return slidingWindow.back();
}

WindowElement *SlidingWindow::getFirst() const {
  assert(slidingWindow.size() != 0);
  return this->slidingWindow.front();
}

void SlidingWindow::printSlidingWindow() {
    for (auto el: slidingWindow) {
        std::cout << "{ seqNum: " << el->seqNum << ", set: " << el->sent << " }";
    }
}

bool SlidingWindow::windowMatchesSet(std::vector<unsigned int> v) {
    for (auto i : v) {
        if (v[i] != slidingWindow[i]->seqNum) {
      return false;
        }
    }

    return true;
}

bool SlidingWindow::containsSentSeqs() {
    for (auto el : slidingWindow) {
        if (el->sent) {
            return true;
        }
    }

    return false;
}