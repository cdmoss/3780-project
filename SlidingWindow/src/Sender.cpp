//
// Created by mbroughton on 11/11/22.
//

#include "../include/Sender.h"

Sender::Sender() {
    slidingWindow = new SlidingWindow();
}

Sender::Sender(unsigned int numOfFrames, SlidingWindow* slidingWindow) {
    Sender::slidingWindow = slidingWindow;
    Sender::numOfFrames = numOfFrames;
}

Sender::~Sender() {
    delete slidingWindow;
    slidingWindow = nullptr;
}

unsigned int Sender::getNumOfFrames() const {
    return numOfFrames;
}

void Sender::setNumOfFrames(unsigned int numOfFrames) {
    Sender::numOfFrames = numOfFrames;
}

SlidingWindow*  Sender::getSlidingWindow() {
    return slidingWindow;
}

void Sender::send(unsigned int seqNum) {

    /*
        numOfFrames--;
        if (numOfFrames == 0) {
            std::cout << "All frames sent successfully!" << std::endl;
            break;
        }
         */
}
