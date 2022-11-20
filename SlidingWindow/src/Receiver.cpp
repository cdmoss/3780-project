#include "../include/Receiver.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

Receiver::Receiver() { slidingWindow = new SlidingWindow(); }

Receiver::Receiver(SlidingWindow *slidingWindow) {
  Receiver::slidingWindow = slidingWindow;
}

std::vector<unsigned int> Receiver::getFrameBuffer() const {
  return frameBuffer;
}

Receiver::~Receiver() {
  delete slidingWindow;
  slidingWindow = nullptr;
}

void Receiver::printFrameBuffer() {
  std::cout << "\n";
  for (unsigned int it : frameBuffer) {
    std::cout << ' ' << it;
  }
  std::cout << std::endl;
}

SlidingWindow *Receiver::getSlidingWindow() { return this->slidingWindow; }

/**
 * Receives a sequence number, returns the appropriate ack given the current
 * state of frameBuffer - returned ack consists of the sequence number being
 * acked and the out of order sequence set
 * @param seqNum The sequence number received
 */
std::pair<unsigned int, std::vector<unsigned int>>
Receiver::receive(unsigned int seqNum) {
  std::cout << "seqNum: " << seqNum << std::endl;
  ;
  std::cout << "first in window: " << slidingWindow->getFirst()->seqNum
            << std::endl;
  ;
  if (seqNum != slidingWindow->getFirst()->seqNum) {
    // seqNum received is out of order: add it to frame buffer
    frameBuffer.push_back(seqNum);
    printFrameBuffer();
    // sort using custom comparator
    std::sort(frameBuffer.begin(), frameBuffer.end(), WraparoundComparator(4));
    std::reverse(frameBuffer.begin(), frameBuffer.end());
  } else {
    // seqNum received is in order: move window past it
    slidingWindow->move(seqNum);

    // if we have out of order frames, erase every buffered out of order
    // sequence that is now in order after receiving the new sequence
    if (!frameBuffer.empty()) {
      while (getFirstFrameBufferElement() ==
                 slidingWindow->getFirst()->seqNum &&
             !frameBuffer.empty()) {
        slidingWindow->move(getFirstFrameBufferElement());
        frameBuffer.erase(frameBuffer.begin());
      }
    }
  }

  // return first sequence number in sliding window + out of order sequence set
  std::pair<unsigned int, std::vector<unsigned int>> acknowledgement;
  if (slidingWindow->getFirst() == 0) {
    acknowledgement.first = 7;
  } else {
    acknowledgement.first = slidingWindow->getFirst()->seqNum - 1;
  }
  acknowledgement.second = frameBuffer;
  return acknowledgement;
}

unsigned int Receiver::getFirstFrameBufferElement() const {
  if (!frameBuffer.empty()) {
    return frameBuffer[0];
  } else {
    std::cout << "Nothing in frameBuffer" << std::endl;
    return -1;
  }
}
