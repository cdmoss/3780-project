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
    delete this -> slidingWindow;
    this -> slidingWindow = nullptr;
}

unsigned int Sender::getNumOfFrames() const {
    return this -> numOfFrames;
}

void Sender::setNumOfFrames(unsigned int numOfFrames) {
    this -> numOfFrames = numOfFrames;
}

SlidingWindow* Sender::getSlidingWindow() {
    return this -> slidingWindow;
}

std::map<unsigned, std::set<unsigned int>*> Sender::send(Receiver *r, unsigned int seqNum) {
    std::map<unsigned, std::set<unsigned int>*> acknowledgement = r ->receive(seqNum);
    return acknowledgement;
}

void Sender::receiveAck(std::map<unsigned int, std::set<unsigned int>*> acknowledgement) {
    auto ack = acknowledgement.begin();
    if (lastSeqNumAck != ack -> first) {
        lastSeqNumAck = ack -> first;
        unsigned int framesReceived = this -> slidingWindow ->move(lastSeqNumAck);
        numOfFrames -= framesReceived;
    }

    if (numOfFrames == 0) {
        std::cout << "All frames successfully sent!" << std::endl;
    }
}
