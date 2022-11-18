//
// Created by mbroughton on 11/11/22.
//

#include "../include/Sender.h"
#include <iostream>

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

void Sender::send(Receiver *r) {
    numOfFrames--;
    if (numOfFrames == 0) {
        std::cout << "All frames sent successfully!" << std::endl;
    }
}

void Sender::receiveAck(std::map<unsigned int, std::set<unsigned int>*> acknowledgement) {
    auto ack = acknowledgement.begin();
    unsigned int lastSeqNumAck = ack -> first;
    std::set<unsigned int> *frameBuffer = ack -> second;
    if ()
}
