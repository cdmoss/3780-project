//
// Created by mbroughton on 11/11/22.
//

#include "../include/Receiver.h"
#include <iostream>
#include <cassert>

Receiver::Receiver() {
    slidingWindow = new SlidingWindow();
    initializeFrameBuffer();
}

Receiver::Receiver(SlidingWindow* slidingWindow) {
    Receiver::slidingWindow = slidingWindow;
    initializeFrameBuffer();
}

std::set<unsigned int>* Receiver::getFrameBuffer() const {
    return frameBuffer;
}

Receiver::~Receiver() {
    delete this -> frameBuffer;
    delete this -> slidingWindow;
    this -> frameBuffer = nullptr;
    this -> slidingWindow = nullptr;
}

void Receiver::initializeFrameBuffer() {
    this -> frameBuffer = new std::set<unsigned int>;
}

void Receiver::printFrameBuffer(std::set<unsigned int> *s) {
    std::cout << "\n";
    for (unsigned int it : *s) {
        std::cout << ' ' << it;
    }
    std::cout << std::endl;
}

SlidingWindow*  Receiver::getSlidingWindow() {
    return this -> slidingWindow;
}

/**
* Receives a sequence number, returns the appropriate ack given the current state of frameBuffer - returned ack consists of the sequence number being acked and the out of order sequence set
* @param seqNum Tfull idk byhe sequence number received
*/
std::pair<unsigned int, std::set<unsigned int>*> Receiver::receive(unsigned int seqNum) {
    if (seqNum != slidingWindow -> getFirst()->seqNum) {
        // seqNum recevied is out of order: add it to frame buffer
        this -> frameBuffer -> insert(seqNum);
    } else {
        // seqNum recevied is in order: move window past it
        this -> slidingWindow -> move(seqNum);

        // erase every buffered out of order sequence that is now in order after receiving the new sequence 
        while (this -> getFirstFrameBufferElement() == this -> slidingWindow -> getFirst()->seqNum && !this -> frameBuffer -> empty()) {
            this -> slidingWindow -> move(this -> getFirstFrameBufferElement());
            this -> frameBuffer -> erase(this -> getFirstFrameBufferElement());
        }
    }

    // return first sequence number in sliding window + out of order sequence set 
    std::pair<unsigned int, std::set<unsigned int>*> acknowledgement;
    acknowledgement.first = this -> slidingWindow -> getFirst()->seqNum - 1;
    acknowledgement.second = this -> frameBuffer;
    return acknowledgement;
}

unsigned int Receiver::getFirstFrameBufferElement() const {
    assert(this -> frameBuffer != nullptr);
    return *(this -> frameBuffer -> begin());
}
