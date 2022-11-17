//
// Created by mbroughton on 11/11/22.
//

#ifndef SLIDINGWINDOW_RECEIVER_H
#define SLIDINGWINDOW_RECEIVER_H

#include "SlidingWindow.h"
#include <set>

class Receiver {
private:
    std::set<unsigned int> frameBuffer = nullptr;
    void initializeFrameBuffer();
    SlidingWindow *slidingWindow;
public:
    Receiver();
    Receiver(SlidingWindow* slidingWindow);
    ~Receiver();
    std::set<unsigned int> getFrameBuffer() const;
    void printFrameBuffer(std::set<unsigned int> *s);
    SlidingWindow  *getSlidingWindow();
    void receive();
};

#endif //SLIDINGWINDOW_RECEIVER_H