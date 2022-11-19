#ifndef SLIDINGWINDOW_SLIDINGWINDOW_H
#define SLIDINGWINDOW_SLIDINGWINDOW_H

#include <deque>
#include <vector>

struct WindowElement {
    unsigned seqNum;
    bool sent;
    bool operator==(const WindowElement &rhs) const {
        return seqNum == rhs.seqNum && sent == rhs.sent;
    };
};



class SlidingWindow {
private:
    unsigned int windowSize{4};
    std::deque<WindowElement*> slidingWindow;
    unsigned int seqNumBits{3};
    unsigned int maxSeqNum{7};


public:
    void initializeSlidingWindow(unsigned int windowSize);
    SlidingWindow(unsigned int windowSize, unsigned int seqNumBits);

    SlidingWindow();

    virtual ~SlidingWindow();

    unsigned int getWindowSize() const;

    void setWindowSize(unsigned int windowSize);

    unsigned int getSeqNumBits() const;

    void setSeqNumBits(unsigned int seqNumBits);
    unsigned int windowContainsSeq(unsigned int seqNum);
    unsigned int move(unsigned int seqNum);
    unsigned sendNext();

    std::deque<WindowElement*> getSlidingWindow();

    void printSlidingWindow();

    WindowElement* getLast() const;

    WindowElement* getFirst() const;

    bool windowMatchesSet(std::vector<unsigned> v);
    bool containsSentSeqs();
};

#endif
