#ifndef _SLIDING_WINDOW
#define _SLIDING_WINDOW

#include <vector>

using namespace std;

typedef unsigned int uint;
typedef vector<unsigned int> uintvec;

/**
* This is the main class that provides all members for maintaining the selective repeat sliding window communication between a sender and a receiver
*/
class SlidingWindowSR {
private:
    /**
    * The max size of the sliding window
    */
    uint winSize;
    /**
     * The max sequence number that can be used
     */
    uint maxSeqNum;
    /**
     * An int vector that keeps track of the state each sequence number in the usable range of sequence numbers using the following convention:
     * 0: unsent
     * 1: sent, but unacknowledged
     * 2: unacknowledged
     */
    uintvec stateVec;

    /**
     * The last sequence number sent
     */
    int lastSent = -1;
    /**
     * The last sequence number acked
     */
    int lastAck = -1;

public:
    SlidingWindowSR();
    /**
     * Constructor that sets the window size and max sequence number
     */
    SlidingWindowSR(uint _winSize, uint _seqNum);
    /**
     * Returns true if sender is able to send a new sequence number, else returns false
     */
    bool canSend();
    /**
     * Sets the window size
     */
    void setWinSize(uint size);
    /**
     * Gets the window size
     */
    uint getWinSize();
    /**
     * Sets the max sequence number
     */
    void setMaxSeqNum(uint size);
    /**
     * Get max sequence number
     */
    uint getMaxSeqNum();
    /**
     * Get max sequence number
     */
    uint getNrUnacked();
    /**
     * Calculates the sequence number that should be sent next, or returns -1 if no sequence number should be sent, 
     */
    uint send();
    /**
     * Recieves a given acked sequence number - updates the internal state of the sender
     */
    void receiveAck(uint ackedSeq);
    /**
     * Prints out the current state of the sequence number range vector
     */
    void printStateVec();
};
#endif
