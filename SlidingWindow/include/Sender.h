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

    Sender(unsigned int numOfFrames, SlidingWindow *slidingWindow);

    ~Sender();

    unsigned int getNumOfFrames() const;

    void setNumOfFrames(unsigned int numOfFrames);

    SlidingWindow *getSlidingWindow();

    std::pair<unsigned, std::set<unsigned int> *> send(Receiver *r);

    void receiveAck(std::pair<unsigned int, std::set<unsigned int> *> acknowledgement);
};

#endif
