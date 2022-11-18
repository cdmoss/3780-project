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
    if (seqNum != slidingWindow -> getFirstSeqNum()) {
        this -> frameBuffer -> insert(seqNum);
    } else {
        this -> slidingWindow -> move(seqNum);
        while (this -> getFirstFrameBufferElement() == this -> slidingWindow -> getFirstSeqNum() && !this -> frameBuffer -> empty()) {
            this -> slidingWindow -> move(this -> getFirstFrameBufferElement());
            this -> frameBuffer -> erase(this -> getFirstFrameBufferElement());
        }
    }
    std::map<unsigned int, std::set<unsigned int>*> acknowledgement;
    acknowledgement.insert({this -> slidingWindow -> getFirstSeqNum() - 1, this -> frameBuffer});
    return acknowledgement;
}

unsigned int Receiver::getFirstFrameBufferElement() const {
    return *(this -> frameBuffer -> begin());
}
