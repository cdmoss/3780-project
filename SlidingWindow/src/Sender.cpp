#include "../include/Sender.h"
#include <iostream>

Sender::Sender() { slidingWindow = new SlidingWindow(); }

Sender::Sender(unsigned int numOfFrames, SlidingWindow *slidingWindow) {
  Sender::slidingWindow = slidingWindow;
  Sender::numOfFrames = numOfFrames;
}

Sender::~Sender() {
  delete this->slidingWindow;
  this->slidingWindow = nullptr;
}

unsigned int Sender::getNumOfFrames() const { return this->numOfFrames; }

void Sender::setNumOfFrames(unsigned int numOfFrames) {
  this->numOfFrames = numOfFrames;
}

SlidingWindow *Sender::getSlidingWindow() { return this->slidingWindow; }

/**
 * Emulates sending a sequence number
 * @return the sequence number to be sent, or -1 if a seq can't be sent
 */
unsigned Sender::send() { return slidingWindow->sendNext(); }

/**
 * Emulates sending a sequence number to the receiver - returns ack from
 * receiver containing acked sequence number and out of order sequence set
 * @param r Receiver object receiving to send to
 * @param seqNum Sequence number to send
 */
unsigned Sender::sendMulti(unsigned amt) {
  unsigned seqToSend = -1;
  for (size_t i = 0; i < amt; i++) {
    seqToSend = slidingWindow->sendNext();
    if (seqToSend == -1) {
      return seqToSend;
    }
  }

  return seqToSend;
}

/**
 * Emulates sending a sequence number to the receiver - returns ack from
 * receiver containing acked sequence number
 * @param r Receiver object receiving to send to
 * @param seqNum Sequence number to send
 */
unsigned Sender::receiveAck(unsigned ackedSeq) {
    if (!slidingWindow->windowContainsSeq(ackedSeq)) {
        std::cout << "Sender: Faulty seq sent in received ack";
        return 0;
    }

    if (!slidingWindow->containsSentSeqs()) {
        std::cout << "Sender: Can't receive ack, not waiting on any seqs";
        return 0;
    }

    unsigned int framesReceived = 0;
    if (lastSeqNumAck != ackedSeq) {
        lastSeqNumAck = ackedSeq;
        framesReceived = slidingWindow->move(ackedSeq);
        numOfFrames -= framesReceived;
    }

    if (numOfFrames == 0) {
        std::cout << "All frames successfully sent!" << std::endl;
    }

  return framesReceived;
}

void Sender::resetSlidingWindow(unsigned winSize) {
    slidingWindow->initializeSlidingWindow(winSize);
}