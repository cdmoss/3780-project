#ifndef _SLIDING_WINDOW
#define _SLIDING_WINDOW

#include <vector>

using namespace std;

typedef unsigned int uint;
typedef vector<unsigned int> uintvec;

class SlidingWindowSR {
private:
    uint winSize;
    uint maxSeqNum;

    uintvec stateVec;

    int lastSent = -1;
    int lastAck = -1;
    uint nrUnacked = 0;

public:
    SlidingWindowSR();
    SlidingWindowSR(uint _winSize, uint _seqNum);
    bool canSend();
    void setWinSize(uint size);
    uint getWinSize();
    void setMaxSeqNum(uint size);
    uint getMaxSeqNum();
    void setNrUnacked(uint nr);
    uint getNrUnacked();
    void ack(uint ackedSeq);
    uint send();
    void printStateVec();
};
#endif
