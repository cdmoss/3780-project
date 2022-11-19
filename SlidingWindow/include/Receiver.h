#ifndef SLIDINGWINDOW_RECEIVER_H
#define SLIDINGWINDOW_RECEIVER_H

#include "SlidingWindow.h"
#include <vector>
#include <utility>

/**
* This class provides a Receiver for a selective repeat protocol communciation channel.
*/
class Receiver {

private:
    /**
    * A comparator that takes into account window wraparounds in its ordering of sequence numbers
    */
    class WraparoundComparator {
    private:
      unsigned winSize = 0;

    public:
      WraparoundComparator(unsigned _winSize) { winSize = _winSize; }

      bool operator()(unsigned int a, unsigned int b) {
        if (a - b > winSize) {
          // b is wrapping around, so its greater than a
          return false;
        } else if (b - a > winSize) {
          return true;
        }

        return b > a;
      }
    };

    std::vector<unsigned int> frameBuffer;

    void initializeFrameBuffer();

    SlidingWindow *slidingWindow;
public:
    Receiver();

    Receiver(SlidingWindow *slidingWindow);

    ~Receiver();

    std::vector<unsigned int> getFrameBuffer() const;

    void printFrameBuffer();

    SlidingWindow *getSlidingWindow();

    std::pair<unsigned int, std::vector<unsigned int>> receive(unsigned int seqNum);

    unsigned int getFirstFrameBufferElement() const;
};

#endif