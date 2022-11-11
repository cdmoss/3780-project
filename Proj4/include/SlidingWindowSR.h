#ifndef _SLIDING_WINDOW
#define _SLIDING_WINDOW

#include <vector>

using namespace std;

typedef unsigned int uint;
typedef vector<unsigned int> uintvec;
typedef vector<bool> boolvec;

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
};

// class SRSender {
// private:
//     int winSize;
//     int seqSize;
//     int lastAck = -1;
//     int lastSent = -1;
//     uintvec unAckedSeqs;


// public:
//     SRSender(unsigned int _winSize, unsigned int _seqSize);
//     void setWinSize(unsigned int _winSize);
//     void setSeqSize(unsigned int _seqSize);
//     unsigned int send();
//     void receiveAck(unsigned int ackedSeq);
//     uintvec getUnackedSeqs();
// };

// class SRReceiver {
// private:
//     int lastAck = -1;
//     unsigned winSize;
//     uintvec outOfOrderSeqList;

// public:
//     // base constructor
//     SRReceiver(unsigned int _winSize);

//     // constructor allowing lastAck init
//     SRReceiver(unsigned int _winSize, int _lastAck);

//     // constructor allowing outOfOrderSeqList init
//     SRReceiver(unsigned int _winSize, uintvec initList);

//     // constructor allowing both fields init
//     SRReceiver(unsigned int _winSize, int _lastAck, uintvec initList);

//     // returns the ack appropriate for the seq received
//     unsigned int receive(unsigned int sentSeq);

//     uintvec getOutOfOrderSeqs();
// };

#endif
