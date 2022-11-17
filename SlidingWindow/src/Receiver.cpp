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
    delete frameBuffer;
    delete slidingWindow;
    frameBuffer = nullptr;
    slidingWindow = nullptr;
}

void Receiver::initializeFrameBuffer() {
    frameBuffer = new std::set<unsigned int>;
}

void Receiver::printFrameBuffer(std::set<unsigned int> *s) {
    std::cout << "\n";
    for (auto it = s -> begin(); it != s -> end(); ++it) {
        std::cout << ' ' << *it;
    }
    std::cout << std::endl;
}

SlidingWindow*  Receiver::getSlidingWindow() {
    return slidingWindow;
}

std::map<unsigned, std::set<unsigned int>*> Receiver::receive(unsigned int seqNum) {
    if (seqNum != slidingWindow -> getLastSeqNum()) {
        frameBuffer -> insert(seqNum);
    } else {
        slidingWindow -> move(seqNum);
        auto frameBufferFirstElement = frameBuffer -> begin();
        while (*frameBufferFirstElement == slidingWindow -> getLastSeqNum() && !frameBuffer -> empty()) {
            slidingWindow -> move(*frameBufferFirstElement);
            frameBuffer -> erase(frameBufferFirstElement);
        }
    }
    std::map<unsigned int, std::set<unsigned int>*> acknowledgement;
    acknowledgement.insert({slidingWindow -> getLastSeqNum(), frameBuffer});
    return acknowledgement;
}
