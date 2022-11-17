//
// Created by mbroughton on 11/11/22.
//

#include "../include/Receiver.h"
#include <set>
#include <map>

Receiver::Receiver() {
    slidingWindow = new SlidingWindow();
    initializeFrameBuffer();
}

Receiver::Receiver(SlidingWindow* slidingWindow) {
    Receiver::slidingWindow = slidingWindow;
    initializeFrameBuffer();
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

unsigned int Receiver::getNumOfFrames() const {
    return numOfFrames;
}

void Receiver::printFrameBuffer(std::set<unsigned int> *s) {
    std::cout << "\n";
    for (auto it = d -> begin(); it != d -> end(); ++it) {
        std::cout << ' ' << *it;
    }
    std::cout << std::endl;
}

SlidingWindow*  Receiver::getSlidingWindow() {
    return slidingWindow;
}

std::map<unsigned, std::set<unsigned int>> Receiver::receive(unsigned int seqNum) {
    if (seqNum != slidingWindow -> getLastSeqNum()) {
        frameBuffer -> insert(seqNum);
    } else {
        slidingWindow -> getSlidingWindow() -> move(seqNum);
        while (frameBuffer -> begin() == slidingWindow -> getLastSeqNum() && !frameBuffer -> empty()) {
            slidingWindow -> getSlidingWindow() -> move(frameBuffer -> begin());
            frameBuffer -> erase(frameBuffer -> begin());
        }
    }
    std::map<unsigned, std::set<unsigned int>> acknowledgement;
    acknowledgement.insert(slidingWindow -> getLastSeqNum(), frameBuffer);
    return acknowledgement;
}
