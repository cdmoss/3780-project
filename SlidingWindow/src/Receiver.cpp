#include "../include/Receiver.h"
#include <iostream>
#include <cassert>

Receiver::Receiver() {
    slidingWindow = new SlidingWindow();
    initializeFrameBuffer();
}

Receiver::Receiver(SlidingWindow *slidingWindow) {
    Receiver::slidingWindow = slidingWindow;
    initializeFrameBuffer();
}

std::set<unsigned int> *Receiver::getFrameBuffer() const {
    return frameBuffer;
}

Receiver::~Receiver() {
    delete this->frameBuffer;
    delete this->slidingWindow;
    this->frameBuffer = nullptr;
    this->slidingWindow = nullptr;
}

void Receiver::initializeFrameBuffer() {
    this->frameBuffer = new std::set<unsigned int>;
}

void Receiver::printFrameBuffer(std::set<unsigned int> *s) {
    std::cout << "\n";
    for (unsigned int it: *s) {
        std::cout << ' ' << it;
    }
    std::cout << std::endl;
}

SlidingWindow *Receiver::getSlidingWindow() {
    return this->slidingWindow;
}

/**
* Receives a sequence number, returns the appropriate ack given the current state of frameBuffer - returned ack consists of the sequence number being acked and the out of order sequence set
* @param seqNum The sequence number received
*/
std::pair<unsigned int, std::set<unsigned int> *> Receiver::receive(unsigned int seqNum) {
    if (seqNum != slidingWindow->getFirstSeqNum()) {
        // seqNum received is out of order: add it to frame buffer
        this->frameBuffer->insert(seqNum);
    } else {
        // seqNum received is in order: move window past it
        this->slidingWindow->move(seqNum);

        // erase every buffered out of order sequence that is now in order after receiving the new sequence 
        while (this->getFirstFrameBufferElement() == this->slidingWindow->getFirstSeqNum() &&
               !this->frameBuffer->empty()) {
            this->slidingWindow->move(this->getFirstFrameBufferElement());
            this->frameBuffer->erase(this->getFirstFrameBufferElement());
        }
    }

    // return first sequence number in sliding window + out of order sequence set 
    std::pair<unsigned int, std::set<unsigned int> *> acknowledgement;
    if (this->slidingWindow->getFirstSeqNum() == 0) {
        acknowledgement.first = 7;
    } else {
        acknowledgement.first = this->slidingWindow->getFirstSeqNum() - 1;
    }
    acknowledgement.second = this->frameBuffer;
    return acknowledgement;
}

unsigned int Receiver::getFirstFrameBufferElement() const {
    assert(this->frameBuffer != nullptr && !this->frameBuffer->empty());
    return *(this->frameBuffer->begin());
}
