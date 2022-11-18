//
// Created by mbroughton on 11/11/22.
//

#ifndef SLIDINGWINDOW_SENDER_H
#define SLIDINGWINDOW_SENDER_H

#include "SlidingWindow.h"
#include "Receiver.h"
#include <set>

class Sender {
private:
    unsigned int numOfFrames{255};
    SlidingWindow *slidingWindow;
    int lastSeqNumAck = -1;
public:
    Sender();
    Sender(unsigned int numOfFrames, SlidingWindow* slidingWindow);
    ~Sender();
    unsigned int getNumOfFrames() const;
    void setNumOfFrames(unsigned int numOfFrames);
    SlidingWindow  *getSlidingWindow();
    std::map<unsigned, std::set<unsigned int>*> send(Receiver *r, unsigned int seqNum);
    void receiveAck(std::map<unsigned int, std::set<unsigned int>*> acknowledgement);
};
#endif //SLIDINGWINDOW_SENDER_H
