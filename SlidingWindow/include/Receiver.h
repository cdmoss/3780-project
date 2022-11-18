//
// Created by mbroughton on 11/11/22.
//

#ifndef SLIDINGWINDOW_RECEIVER_H
#define SLIDINGWINDOW_RECEIVER_H

#include "SlidingWindow.h"
#include <set>
#include <map>

class Receiver {
private:
    std::set<unsigned int> *frameBuffer = nullptr;
    void initializeFrameBuffer();
    SlidingWindow *slidingWindow;
public:
    Receiver();
    Receiver(SlidingWindow* slidingWindow);
    ~Receiver();
    std::set<unsigned int> *getFrameBuffer() const;
    void printFrameBuffer(std::set<unsigned int> *s);
    SlidingWindow  *getSlidingWindow();
    std::map<unsigned int, std::set<unsigned int>*> receive(unsigned int seqNum);
    unsigned int getFirstFrameBufferElement() const;
};

#endif //SLIDINGWINDOW_RECEIVER_H