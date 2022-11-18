//
// Created by mbroughton on 11/11/22.
//

#include "../include/Receiver.h"
#include <iostream>

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

std::map<unsigned, std::set<unsigned int>*> Receiver::receive(unsigned int seqNum) {
    if (seqNum != slidingWindow -> getLastSeqNum()) {
        this -> frameBuffer -> insert(seqNum);
    } else {
        this -> slidingWindow -> move(seqNum);
        auto frameBufferFirstElement = this -> frameBuffer -> begin();
        while (*frameBufferFirstElement == this -> slidingWindow -> getLastSeqNum() && !this -> frameBuffer -> empty()) {
            this -> slidingWindow -> move(*frameBufferFirstElement);
            this -> frameBuffer -> erase(frameBufferFirstElement);
        }
    }
    std::map<unsigned int, std::set<unsigned int>*> acknowledgement;
    acknowledgement.insert({this -> slidingWindow -> getLastSeqNum(), this -> frameBuffer});
    return acknowledgement;
}
